//
//  ContentView.swift
//  Lab6
//
//  Created by Tyler Fichiera on 3/30/23.
//

import SwiftUI

struct ContentView: View {
    @ObservedObject var cityViewModel = CityViewModel()
    
    @State var showAddAlert = false
    @State var showDeleteAlert = false
    @State private var showPhotoLibrary = false
    
    @State var newCityName = String()
    @State var newCityDescription = String()
    @State var newCityImage = UIImage()
    
    @State var deleteCityName = String()
    
    var body: some View {
        NavigationView {
            List {
                ForEach(cityViewModel.cities, id: \.id) { city in
                    if city.name != nil {
                        NavigationLink(destination: CityDetailView(cityName: city.name!, cityImage: city.image!, cityDescription: city.descrip!)) {
                            HStack {
                                Image(uiImage: UIImage(data:(city.image ?? Data())) ?? UIImage())
                                    .resizable()
                                    .scaledToFit()
                                    .frame(height: 50)
                                    .cornerRadius(10)
                                Text(city.name!)
                            }
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
                .sheet(isPresented: $showPhotoLibrary) {
                    ImagePicker(sourceType: .photoLibrary, selectedImage: $newCityImage, onImagePicked: {
                        print("Image picked!")
                        let _ = cityViewModel.saveCity(name: newCityName, description: newCityDescription, image: newCityImage.pngData() ?? Data())
                        newCityName = String()
                        newCityDescription = String()
                        newCityImage = UIImage()
                    })
                }
                .alert("Add City", isPresented: $showAddAlert, actions: {
                    TextField("Name", text: $newCityName)
                    TextField("Description", text: $newCityDescription)
                    
                    Button("Choose Image") {
                        if newCityName != "" && newCityDescription != "" {
                            showPhotoLibrary = true
                        } else {
                            newCityName = String()
                            newCityDescription = String()
                        }
                        
                        showAddAlert = false
                    }
                    Button("Cancel", role: .cancel) {
                        newCityName = String()
                        newCityDescription = String()
                        showAddAlert = false
                    }
                }, message: {
                    Text("Please enter details below to add city")
                })
                .alert("Delete City", isPresented: $showDeleteAlert, actions: {
                    TextField("Name", text: $deleteCityName)
                    
                    Button("Delete") {
                        // TODO: maybe add alert that says a city w/ that name could not be found
                        cityViewModel.deleteCity(name: deleteCityName)
                        
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
