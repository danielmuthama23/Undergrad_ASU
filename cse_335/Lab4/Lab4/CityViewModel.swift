//
//  CityViewModel.swift
//  Lab4
//
//  Created by Tyler Fichiera on 2/28/23.
//

import Foundation

public class CityViewModel: ObservableObject {
    @Published var cities = [
        City(name: "Phoenix, Arizona", description: "Beautiful desert and home to the Phoenix Suns"),
        City(name: "Tempe, Arizona", description: "The home of Arizona State University"),
        City(name: "Glendale, Arizona", description: "In the middle of no where and home to the Arizona Cardinals"),
        City(name: "Los Angeles, California", description: "The most populous city in all of California"),
        City(name: "San Diego, California", description: "Beautiful beaches with a lot of family attractions")
    ]
    
    func cityIndexByName(name: String) -> Int {
        for (index, city) in cities.enumerated() {
            if city.name == name {
                return index
            }
        }
        return -1
    }
    
    func add(city: City) {
        cities.append(city)
    }
    
    func remove(cityName: String) {
        let index = cityIndexByName(name: cityName)
        if index > -1 {
            cities.remove(at: index)
        }
    }
}
