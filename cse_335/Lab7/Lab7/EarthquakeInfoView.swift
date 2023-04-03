//
//  EarthquakeInfoView.swift
//  Lab7
//
//  Created by Tyler Fichiera on 4/2/23.
//

import SwiftUI
import MapKit

let API_USERNAME = "tfich"

struct EarthquakeInfoView: View {
    @State var cityName: String
    
    @State private var errorMessage: String? = nil
    @State private var eartquakeList: EarthquakeList? = nil
    
    var body: some View {
        VStack {
            if errorMessage != nil {
                Text(errorMessage!)
            } else if eartquakeList != nil {
                List {
                    Section(header: Text("Earthquakes")) {
                        ForEach(eartquakeList!.earthquakes.prefix(10), id: \.eqid) { quake in
                            VStack(alignment: .leading) {
                                Text("\(convertDate(quake.datetime))").bold()
                                Text("Magnitude: \(quake.magnitude)")
                            }
                        }
                    }
                }
            } else {
                Text("Loading")
                ProgressView()
            }
        }.onAppear(perform: {
            forwardGeocoding(addressStr: cityName)
        })
        .onDisappear(perform: {
            // reset variables
            cityName = String()
            errorMessage = nil
            eartquakeList = nil
        })
    }
    
    private func forwardGeocoding(addressStr: String) {
        let addressString = addressStr
        CLGeocoder().geocodeAddressString(addressString, completionHandler: {(placemarks, error) in
            if error != nil {
                errorMessage = "Unable to get coords for that city name"
                print("Geocode failed: \(error!.localizedDescription)")
            } else if placemarks!.count > 0 {
                let placemark = placemarks![0]
                let location = placemark.location
                let coords = location!.coordinate
                
                DispatchQueue.main.async {
                    getEarthquakes(lat: coords.latitude, lon: coords.longitude)
                }
            }
        })
    }
    
    private func getEarthquakes(lat: Double, lon: Double) {
        // calculate the directions based on lat and lon
        let north = lat + 10
        let south = lat - 10
        let east = lon - 10
        let west = lon + 10
        
        // build url with params
        let urlStr = "http://api.geonames.org/earthquakesJSON?north=\(north)&south=\(south)&east=\(east)&west=\(west)&username=\(API_USERNAME)"
        
        let url = URL(string: urlStr)!
        
        let urlSession = URLSession.shared
        
        // call the API, data will contain the JSON results
        let jsonQuery = urlSession.dataTask(with: url, completionHandler: { data, response, error -> Void in
            if (error != nil) {
                errorMessage = error!.localizedDescription
                print(error!.localizedDescription)
            }
            var err: NSError?
            
            // use JSON decoder to decode news items from data to the news structure defined in the data model
            let decoder = JSONDecoder()
            let jsonResult = try! decoder.decode(EarthquakeList.self, from: data!)
        
            if (err != nil) {
                print("JSON Error \(err!.localizedDescription)")
            }
            
            // set earthquake list based on the json result
            eartquakeList = jsonResult
        })
        
        jsonQuery.resume()
    }
    
    private func convertDate(_ datetime: String) -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "yyyy-MM-dd HH:mm:ss"
        let date = dateFormatter.date(from: datetime)

        dateFormatter.dateFormat = "EEEE, MMM d, yyyy 'at' h:mm a"
        return dateFormatter.string(from: date!)
    }
}

struct EarthquakeInfoView_Previews: PreviewProvider {
    static var previews: some View {
        EarthquakeInfoView(cityName: "Tempe, AZ")
    }
}
