//
//  HealthView.swift
//  Homework1
//
//  Created by Tyler Fichiera on 3/21/23.
//

import SwiftUI
import Charts

struct HealthView: View {
    @ObservedObject var dataViewModel: HealthDataViewModel
    
    let chartsHeight: CGFloat? = 250
    
    var body: some View {
        List {
            Section {
                bloodPressureChart
            } header: {
                Text("Blood Pressure")
            }
            
            Section {
                weightChart
            } header: {
                Text("Weight")
            }
            
            Section {
                sugarLevelChart
            } header: {
                Text("Morning Sugar Level")
            }
        }
    }
    
    var bloodPressureChart: some View {
        Chart(dataViewModel.getPastSevenDays()) { input in
            LineMark(
                x: .value("Date", input.date),
                y: .value("BP", input.systolicBp)
            )
            .interpolationMethod(.cardinal)
            .foregroundStyle(by: .value("Type", "Systolic"))
            .symbol(by: .value("Type", "Systolic"))
            
            LineMark(
                x: .value("Date", input.date),
                y: .value("BP", input.diastolicBp)
            )
            .interpolationMethod(.cardinal)
            .foregroundStyle(by: .value("Type", "Diastolic"))
            .symbol(by: .value("Type", "Diastolic"))
        }
        .chartXAxis {
            AxisMarks(values: .automatic(desiredCount: 7, roundLowerBound: true)) { value in
                if let _ = value.as(Date.self) {
                    AxisValueLabel(format: .dateTime.month().day())
                }
                AxisGridLine()
                AxisTick()
             }
         }
        .chartYAxis(.automatic)
        .chartLegend(.automatic)
        .frame(height: chartsHeight)
    }
    
    var weightChart: some View {
        Chart(dataViewModel.getPastSevenDays()) { input in
            LineMark(
                x: .value("Date", input.date),
                y: .value("Weight", input.weight)
            )
            .interpolationMethod(.cardinal)
            .symbol(Circle())
        }
        .chartXAxis {
            AxisMarks(values: .automatic(desiredCount: 7, roundLowerBound: true)) { value in
                if let _ = value.as(Date.self) {
                    AxisValueLabel(format: .dateTime.month().day())
                }
                AxisGridLine()
                AxisTick()
             }
         }
        .chartYAxis(.automatic)
        .frame(height: chartsHeight)
    }
    
    var sugarLevelChart: some View {
        Chart(dataViewModel.getPastSevenDays()) { input in
            LineMark(
                x: .value("Date", input.date),
                y: .value("Sugar Level", input.sugarLevel)
            )
            .interpolationMethod(.cardinal)
            .symbol(Circle())
        }
        .chartXAxis {
            AxisMarks(values: .automatic(desiredCount: 7, roundLowerBound: true)) { value in
                if let _ = value.as(Date.self) {
                    AxisValueLabel(format: .dateTime.month().day())
                }
                AxisGridLine()
                AxisTick()
             }
         }
        .chartYAxis(.automatic)
        .frame(height: chartsHeight)
    }
}

struct HealthView_Previews: PreviewProvider {
    static var previews: some View {
        HealthView(dataViewModel: HealthDataViewModel())
    }
}
