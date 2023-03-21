//
//  CityViewModel.swift
//  Lab4
//
//  Created by Tyler Fichiera on 2/28/23.
//

import Foundation

public class CityViewModel: ObservableObject {
    @Published var cities = [
        City(name: "Phoenix, Arizona"),
        City(name: "Tempe, Arizona"),
        City(name: "Glendale, Arizona"),
        City(name: "Los Angeles, California"),
        City(name: "San Diego, California")
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
