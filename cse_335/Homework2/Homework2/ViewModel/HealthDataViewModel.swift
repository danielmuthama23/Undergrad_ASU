//
//  HealthDataViewModel.swift
//  Homework2
//
//  Created by Tyler Fichiera on 4/25/23.
//

import Foundation
import CoreData

let LOAD_SAMPLE_DATA = true

public class HealthDataViewModel: ObservableObject {
    @Published private var healthInputDictionary: [Date: HealthInput] = [:]
    
    private let calendar = Calendar.current
    private let now = Date()
    
    private let persistentContainer: NSPersistentContainer
    
    init() {
        persistentContainer = NSPersistentContainer(name: "AppData")
        persistentContainer.loadPersistentStores { (description, error) in
            if let error = error{
                fatalError("Trouble loading data \(error.localizedDescription)")
            }
        }
        
        let healthInputsList = loadHealthInputs()
        
        // load sample data if there is no data already stored
        if LOAD_SAMPLE_DATA && healthInputsList.isEmpty {
            // load for the past month
            for i in 0..<31 {
                let date = calendar.date(byAdding: .day, value: -i, to: now)!
                let _ = newHealthInput(
                    date: date,
                    systolicBp: Double.random(in: 90...120),
                    diastolicBp: Double.random(in: 60...80),
                    weight: Double.random(in: 80...200),
                    sugarLevel: Double.random(in: 50...110),
                    symptoms: ["None", "Headache", "Fatigue", "Nausea"].randomElement()!
                )
            }
        }
    }
    
    private func loadHealthInputs() -> [HealthInput] {
        let fetchRequest: NSFetchRequest<HealthInput> = HealthInput.fetchRequest()
        do {
            let healthInputs = try persistentContainer.viewContext.fetch(fetchRequest)
            for input in healthInputs {
                addHealthInputToDictionary(input)
            }
            return healthInputs
        }catch{
            return []
        }
    }
    
    func newHealthInput(date: Date, systolicBp: Double, diastolicBp: Double, weight: Double, sugarLevel: Double, symptoms: String) -> HealthInput {
        let healthInput = HealthInput(context: persistentContainer.viewContext)
        healthInput.id = UUID()
        healthInput.date = removeTime(from: date)
        healthInput.systolicBp = systolicBp
        healthInput.diastolicBp = diastolicBp
        healthInput.weight = weight
        healthInput.sugarLevel = sugarLevel
        healthInput.symptoms = symptoms
        
        do {
            try persistentContainer.viewContext.save()
            addHealthInputToDictionary(healthInput)
        } catch {
            print("failed to save \(error)")
        }
        
        return healthInput
    }

    private func addHealthInputToDictionary(_ healthInput: HealthInput) {
        let healthInput = healthInput // make non-constant
        healthInput.date = removeTime(from: healthInput.date)
        healthInputDictionary[healthInput.date] = healthInput
    }
    
    func getHealthInputByDate(_ date: Date) -> HealthInput? {
        var date = date // make non-constant
        date = removeTime(from: date)
        return healthInputDictionary[date]
    }
    
    func getHealthInputsInRange(from startDate: Date, to endDate: Date) -> [HealthInput] {
        let startDateWithoutTime = removeTime(from: startDate)
        let endDateWithoutTime = removeTime(from: endDate)
        
        var healthInputsInRange: [HealthInput] = []
        var currentDate = startDateWithoutTime
        
        while currentDate <= endDateWithoutTime {
            if let healthInput = getHealthInputByDate(currentDate) {
                healthInputsInRange.append(healthInput)
            }
            
            currentDate = removeTime(from: calendar.date(byAdding: .day, value: 1, to: currentDate)!)
        }
        
        return healthInputsInRange.sorted(by: { $0.date < $1.date })
    }
    
    private func removeTime(from date: Date) -> Date {
        let components = calendar.dateComponents([.year, .month, .day], from: date)
        return calendar.date(from: components)!
    }
}
