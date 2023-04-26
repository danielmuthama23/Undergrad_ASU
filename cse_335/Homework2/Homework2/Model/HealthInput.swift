//
//  HealthInput.swift
//  Homework2
//
//  Created by Tyler Fichiera on 4/25/23.
//

import Foundation
import CoreData

@objc(HealthInput)
public class HealthInput: NSManagedObject {

}

extension HealthInput {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<HealthInput> {
        return NSFetchRequest<HealthInput>(entityName: "HealthInput")
    }

    @NSManaged public var id: UUID
    @NSManaged public var date: Date
    @NSManaged public var systolicBp: Double
    @NSManaged public var diastolicBp: Double
    @NSManaged public var weight: Double
    @NSManaged public var sugarLevel: Double
    @NSManaged public var symptoms: String

}

extension HealthInput : Identifiable {

}
