//
//  ContentView.swift
//  Lab5
//
//  Created by Tyler Fichiera on 2/28/23.
//

import SwiftUI

struct ContentView: View {
    @ObservedObject var cityViewModel = CityViewModel()
    
    @State var showAddAlert = false
    @State var showDeleteAlert = false
    
    @State var newCityName = String()
    
    @State var deleteCityName = String()
    
    var body: some View {
        NavigationView {
            List {
                ForEach(cityViewModel.cities, id: \.id) { city in
                    NavigationLink(destination: CityDetailView(cityName: city.name, cityImage: city.image)) {
                        HStack {
                            Image(city.image)
                                .resizable()
                                .scaledToFit()
                                .frame(height: 50)
                                .cornerRadius(10)
                            Text(city.name)
                        }
                    }
                }
            }.navigationTitle("My Favorite Cities")
                .navigationBarTitleDisplayMode(.inline)
                .toolbar {
                    ToolbarItem(placement: .navigationBarLeading) {
                        Button {
                            showDeleteAlert = true
                        } label: {
                            Image(systemName: "trash")
                        }
                    }
                    
                    ToolbarItem(placement: .navigationBarTrailing) {
                        Button {
                            showAddAlert = true
                        } label: {
                            Image(systemName: "plus")
                        }
                    }
                }
                .alert("Add City", isPresented: $showAddAlert, actions: {
                    TextField("Name", text: $newCityName)
                    
                    Button("Add") {
                        let newCity = City(name: newCityName)
                        cityViewModel.add(city: newCity)
                        
                        newCityName = String()
                        showAddAlert = false
                    }
                    Button("Cancel", role: .cancel) {
                        newCityName = String()
                        showAddAlert = false
                    }
                }, message: {
                    Text("Please enter details below to add city")
                })
                .alert("Delete City", isPresented: $showDeleteAlert, actions: {
                    TextField("Name", text: $deleteCityName)
                    
                    Button("Delete") {
                        // TODO: maybe add alert that says a city w/ that name could not be found
                        cityViewModel.remove(cityName: deleteCityName)
                        
                        deleteCityName = String()
                        showDeleteAlert = false
                    }
                    Button("Cancel", role: .cancel) {
                        deleteCityName = String()
                        showDeleteAlert = false
                    }
                }, message: {
                    Text("Please enter details below to delete city")
                })
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
