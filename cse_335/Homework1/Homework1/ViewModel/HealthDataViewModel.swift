//
//  HealthDataViewModel.swift
//  Homework1
//
//  Created by Tyler Fichiera on 3/21/23.
//

import Foundation

enum RiskAssessment {
    case risk
    case notRisk
    case cantDetermine
}

public class HealthDataViewModel: ObservableObject {
    @Published private var healthInputDictionary: [Date: HealthInput] = [:]
    
    private let calendar = Calendar.current
    private let now = Date()
    
    init() {
        // fill in sample data for now
        for i in 0..<7 {
            let date = calendar.date(byAdding: .day, value: -i, to: now)!
            let healthInput = HealthInput(
                date: date,
                systolicBp: Double.random(in: 90...120),
                diastolicBp: Double.random(in: 60...80),
                weight: Double.random(in: 80...200),
                sugarLevel: Double.random(in: 50...110),
                symptoms: ["None", "Headache", "Fatigue", "Nausea"].randomElement()!
            )
            addOrUpdateHealthInput(healthInput)
        }
    }

    func addOrUpdateHealthInput(_ healthInput: HealthInput) {
        var healthInput = healthInput // make non-constant
        healthInput.date = removeTime(from: healthInput.date)
        healthInputDictionary[healthInput.date] = healthInput
    }
    
    func getHealthInputByDate(_ date: Date) -> HealthInput? {
        var date = date // make non-constant
        date = removeTime(from: date)
        return healthInputDictionary[date]
    }
    
    func getPastSevenDays() -> [HealthInput] {
        var pastSevenDays: [HealthInput] = []
        
        for i in 0..<7 {
            let date = calendar.date(byAdding: .day, value: -i, to: now)!
            if let info = getHealthInputByDate(date) {
                pastSevenDays.append(info)
            }
        }
        return Array(pastSevenDays.sorted(by: { $0.date < $1.date }))
    }
    
    // If the average weight of last four days of the week is higher than
    // the average weight of the first three days of the week
    func getWeightRisk() -> RiskAssessment {
        let pastSevenDays = getPastSevenDays()
        
        if pastSevenDays.count < 7 {
            return RiskAssessment.cantDetermine
        }
        
        var sumFirstThree = 0.0
        var sumLastFour = 0.0
        
        for (index, day) in pastSevenDays.enumerated() {
            if (0...2).contains(index) {
                sumFirstThree += day.weight
            } else {
                sumLastFour += day.weight
            }
        }
        
        return (sumFirstThree / 3) < (sumLastFour / 4) ? RiskAssessment.risk : RiskAssessment.notRisk
    }
    
    // If the current sugar level is 10% higher than the previous day
    func getSugarRisk() -> RiskAssessment {
        let yesterday = calendar.date(byAdding: .day, value: -1, to: now)!
        
        let todayHealth = getHealthInputByDate(now)
        let yesterdayHealth = getHealthInputByDate(yesterday)
        
        if todayHealth == nil || yesterdayHealth == nil {
            return RiskAssessment.cantDetermine
        }
        
        return todayHealth!.sugarLevel >= yesterdayHealth!.sugarLevel * 1.1 ?
            RiskAssessment.risk : RiskAssessment.notRisk
    }
    
    // If the current blood pressure (systolic, diastolic, or both)
    // level is 10% higher than the previous day
    func getBloodPressureRisk() -> RiskAssessment {
        let yesterday = calendar.date(byAdding: .day, value: -1, to: now)!
        
        let todayHealth = getHealthInputByDate(now)
        let yesterdayHealth = getHealthInputByDate(yesterday)
        
        if todayHealth == nil || yesterdayHealth == nil {
            return RiskAssessment.cantDetermine
        }
        
        let type1 = todayHealth!.diastolicBp >= yesterdayHealth!.diastolicBp * 1.1
        let type2 = todayHealth!.systolicBp >= yesterdayHealth!.systolicBp * 1.1
        
        return type1 || type2 ? RiskAssessment.risk : RiskAssessment.notRisk
    }
    
    private func removeTime(from date: Date) -> Date {
        let components = calendar.dateComponents([.year, .month, .day], from: date)
        return calendar.date(from: components)!
    }
}
