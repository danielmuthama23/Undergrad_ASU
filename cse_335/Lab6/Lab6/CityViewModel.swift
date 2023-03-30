//
//  CityViewModel.swift
//  Lab6
//
//  Created by Tyler Fichiera on 3/30/23.
//

import Foundation
import CoreData
import SwiftUI

public class CityViewModel: ObservableObject {
//    @Published var cities = [
//        City(name: "Phoenix, Arizona", description: "Beautiful desert and home to the Phoenix Suns"),
//        City(name: "Tempe, Arizona", description: "The home of Arizona State University"),
//        City(name: "Glendale, Arizona", description: "In the middle of no where and home to the Arizona Cardinals"),
//        City(name: "Los Angeles, California", description: "The most populous city in all of California"),
//        City(name: "San Diego, California", description: "Beautiful beaches with a lot of family attractions")
//    ]
    @Published var cities: [City] = [City]()
    
    let persistentContainer: NSPersistentContainer
    
    init() {
        persistentContainer = NSPersistentContainer(name: "cities")
        persistentContainer.loadPersistentStores { (description, error) in
            if let error = error{
                fatalError("Trouble loading data \(error.localizedDescription)")
            }
        }
        
        cities = getCities()
    }
    
    private func getCities() -> [City] {
        let fetchRequest: NSFetchRequest<City> = City.fetchRequest()
        do {
            let x = try persistentContainer.viewContext.fetch(fetchRequest)
            return x
        }catch{
            return []
        }
    }
    
    func saveCity(name: String, description: String, image: Data) -> City {
        let city = City(context: persistentContainer.viewContext)
        city.id = UUID()
        city.name = name
        city.descrip = description
        city.image = image
        
        do {
            try persistentContainer.viewContext.save()
            cities = getCities()
        } catch {
            print("failed to save \(error)")
        }
        
        return city
    }
    
    func deleteCity(name: String) {
        let index = cityIndexByName(name: name)
        if index == -1 {
            return
        }
        
        let city = cities[index]
        
        persistentContainer.viewContext.delete(city)
        do {
            try persistentContainer.viewContext.save()
        } catch{
            print("failed to save \(error)")
        }
    }
    
    private func cityIndexByName(name: String) -> Int {
        for (index, city) in cities.enumerated() {
            if city.name == name {
                return index
            }
        }
        return -1
    }
}
