//
//  HealthView.swift
//  Homework2
//
//  Created by Tyler Fichiera on 4/25/23.
//

import SwiftUI
import Charts

struct HealthView: View {
    @ObservedObject var dataViewModel: HealthDataViewModel
    
    // by default have the date seletion start 7 days prior to the current day
    @State private var startDateInput: Date = Calendar.current.date(byAdding: .day, value: -7, to: Date())!
    @State private var endDateInput: Date = Date()
    
    @State private var healthInputsInRange: [HealthInput] = []
    
    let sectionHeight: CGFloat? = 250
    
    let dateFormatter: DateFormatter = {
        let formatter = DateFormatter()
        formatter.dateStyle = .medium
        formatter.timeStyle = .none
        formatter.dateFormat = "EEEE, MMMM d, yyyy"
        return formatter
    }()
    
    var body: some View {
        List {
            Section {
                DatePicker("From", selection: $startDateInput, displayedComponents: .date)
                DatePicker("To", selection: $endDateInput, displayedComponents: .date)
            } header: {
                Text("Select Date Range")
            }
            
            Section {
                inputsList
            } header: {
                Text("Health Inputs")
            }
            
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
        .onChange(of: [startDateInput, endDateInput]) { _ in
            // update the health to be shown
            healthInputsInRange = dataViewModel.getHealthInputsInRange(from: startDateInput, to: endDateInput)
        }
        .onAppear(perform: {
            healthInputsInRange = dataViewModel.getHealthInputsInRange(from: startDateInput, to: endDateInput)
        })
    }
    
    var inputsList: some View {
        VStack {
            List {
                ForEach(healthInputsInRange.reversed()) { healthInput in
                    VStack(alignment: .leading) {
                        Text("\(healthInput.date, formatter: dateFormatter)").fontWeight(.bold)
                        Text("Systolic BP: \(healthInput.systolicBp, specifier: "%.0f")")
                        Text("Diastolic BP: \(healthInput.diastolicBp, specifier: "%.0f")")
                        Text("Weight: \(healthInput.weight, specifier: "%.1f")")
                        Text("Morning Sugar Level: \(healthInput.sugarLevel, specifier: "%.1f")")
                        Text("Symptoms: \(healthInput.symptoms)")
                    }
                }
            }
            .listStyle(PlainListStyle())
            
            Text("Total Health Inputs In Range: \(healthInputsInRange.count)")
                .foregroundColor(.secondary)
                .font(.caption)
                .padding(.vertical, 5)
        }
        .frame(height: sectionHeight)
    }
    
    var bloodPressureChart: some View {
        Chart(healthInputsInRange) { input in
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
            AxisMarks(values: .automatic(desiredCount: 4, roundLowerBound: true)) { value in
                if let _ = value.as(Date.self) {
                    AxisValueLabel(format: .dateTime.month().day())
                }
                AxisGridLine()
                AxisTick()
             }
         }
        .chartYAxis(.automatic)
        .chartLegend(.automatic)
        .frame(height: sectionHeight)
    }
    
    var weightChart: some View {
        Chart(healthInputsInRange) { input in
            LineMark(
                x: .value("Date", input.date),
                y: .value("Weight", input.weight)
            )
            .interpolationMethod(.cardinal)
            .symbol(Circle())
        }
        .chartXAxis {
            AxisMarks(values: .automatic(desiredCount: 4, roundLowerBound: true)) { value in
                if let _ = value.as(Date.self) {
                    AxisValueLabel(format: .dateTime.month().day())
                }
                AxisGridLine()
                AxisTick()
             }
         }
        .chartYAxis(.automatic)
        .frame(height: sectionHeight)
    }
    
    var sugarLevelChart: some View {
        Chart(healthInputsInRange) { input in
            LineMark(
                x: .value("Date", input.date),
                y: .value("Sugar Level", input.sugarLevel)
            )
            .interpolationMethod(.cardinal)
            .symbol(Circle())
        }
        .chartXAxis {
            AxisMarks(values: .automatic(desiredCount: 4, roundLowerBound: true)) { value in
                if let _ = value.as(Date.self) {
                    AxisValueLabel(format: .dateTime.month().day())
                }
                AxisGridLine()
                AxisTick()
             }
         }
        .chartYAxis(.automatic)
        .frame(height: sectionHeight)
    }
}

struct HealthView_Previews: PreviewProvider {
    static var previews: some View {
        HealthView(dataViewModel: HealthDataViewModel())
    }
}
