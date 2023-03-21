//
//  CityDetailView.swift
//  Lab4
//
//  Created by Tyler Fichiera on 2/28/23.
//

import SwiftUI
import MapKit

struct Location: Identifiable {
    let id = UUID()
    let name: String
    let coordinate: CLLocationCoordinate2D
}

struct CityDetailView: View {
    @State var cityName: String
    @State var cityImage: String

    // state property that represents the current map region
    @State private var region = MKCoordinateRegion(
        center: CLLocationCoordinate2D(latitude: 33.4255, longitude: -111.9400),
        span: MKCoordinateSpan(latitudeDelta: 0.2, longitudeDelta: 0.2)
    )
    
    @State private var markers: [Location] = []
    @State private var searchText = ""
   
    var body: some View {
        Text(cityName).fontWeight(.bold)
        Text("\(region.center.latitude),\(region.center.longitude)")

        ZStack(alignment: .bottom) {
            Map(coordinateRegion: $region, interactionModes: .all, annotationItems: markers) { location in
                MapAnnotation(coordinate: location.coordinate) {
                    Image(systemName: "pin.circle.fill").foregroundColor(.red)
                    Text(location.name)
                }
            }
        }
        .ignoresSafeArea()
        .onAppear(perform: {
            // get the city location immediately
            forwardGeocoding(addressStr: cityName)
        })
        
        searchBar
    }
    
    
    private var searchBar: some View {
        HStack {
            Button {
                let searchRequest = MKLocalSearch.Request()
                searchRequest.naturalLanguageQuery = searchText
                searchRequest.region = region
                
                MKLocalSearch(request: searchRequest).start { response, error in
                    guard let response = response else {
                        print("Error: \(error?.localizedDescription ?? "Unknown error").")
                        return
                    }
                    region = response.boundingRegion
                    markers = response.mapItems.map { item in
                        Location(
                            
                            name: item.name ?? "",
                            coordinate: item.placemark.coordinate
                        )
                    }
                }
            } label: {
                Image(systemName: "location.magnifyingglass")
                    .resizable()
                    .foregroundColor(.accentColor)
                    .frame(width: 24, height: 24)
                    .padding(.trailing, 12)
            }
            TextField("Search ex. Raising Canes", text: $searchText)
        }
        .padding()
        .background {
            RoundedRectangle(cornerRadius: 8)
                .foregroundColor(.white)
        }
        .padding()
    }
    
    func forwardGeocoding(addressStr: String) {
        let addressString = addressStr
        CLGeocoder().geocodeAddressString(addressString, completionHandler: {(placemarks, error) in
            if error != nil {
                print("Geocode failed: \(error!.localizedDescription)")
            } else if placemarks!.count > 0 {
                let placemark = placemarks![0]
                let location = placemark.location
                let coords = location!.coordinate
                
                DispatchQueue.main.async
                    {
                        self.region.center = coords
                        self.markers.append(Location(name: self.cityName, coordinate: coords))
                    }
            }
        })
    }
}

struct CityDetailView_Previews: PreviewProvider {
    static var previews: some View {
        CityDetailView(cityName: "Phoenix, Arizona", cityImage: "sample-city")
    }
}
