//
//  ApiModels.swift
//  Lab7
//
//  Created by Tyler Fichiera on 4/2/23.
//

import Foundation

struct EarthquakeList: Decodable {
    let earthquakes: [Earthquake]
}

struct Earthquake: Decodable {
    let datetime: String
    let depth: Double
    let lng: Double
    let src: String
    let eqid: String
    let magnitude: Double
    let lat: Double
}
