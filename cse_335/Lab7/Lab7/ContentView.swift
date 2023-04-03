//
//  ContentView.swift
//  Lab7
//
//  Created by Tyler Fichiera on 4/2/23.
//

import SwiftUI

struct ContentView: View {
    @State private var cityNameInput = ""
    
    var body: some View {
        NavigationStack {
            VStack {
                Text("Lab 7 - Earthquake Info")
                Spacer()
                TextField("Enter City Name", text: $cityNameInput)
                    .padding()
                    .background(Color.gray.opacity(0.2))
                    .cornerRadius(10)
                    .padding(.horizontal, 20)
                
                
                NavigationLink(destination: EarthquakeInfoView(cityName: cityNameInput)) {
                    Text("Get Earthquakes")
                }
                .padding()
                .background(Color.blue)
                .foregroundColor(.white)
                .cornerRadius(10)
                .padding(.horizontal, 20)
                .disabled(cityNameInput == "") // no click unless city has been entered
                
                Spacer()
            }
            .padding()
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
