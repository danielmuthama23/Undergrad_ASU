//
//  HealthInput.swift
//  Homework1
//
//  Created by Tyler Fichiera on 3/21/23.
//

import Foundation

struct HealthInput: Identifiable {
    var id = UUID()
    var date: Date
    var systolicBp: Double
    var diastolicBp: Double
    var weight: Double
    var sugarLevel: Double
    var symptoms: String
}
