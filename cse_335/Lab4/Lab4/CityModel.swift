//
//  CityModel.swift
//  Lab4
//
//  Created by Tyler Fichiera on 2/28/23.
//

import Foundation

struct City: Identifiable {
    var id = UUID()
    var name = String()
    var image = String("sample-city") // same for all cities
    var description = String()
}
