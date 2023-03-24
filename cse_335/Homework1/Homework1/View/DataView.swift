//
//  DataView.swift
//  Homework1
//
//  Created by Tyler Fichiera on 3/6/23.
//

import SwiftUI

struct DataView: View {
    @ObservedObject var dataViewModel: HealthDataViewModel
    
    @State private var dateInput: Date = Date()
    @State private var systolicBpInputStr = ""
    @State private var diastolicBpInputStr = ""
    @State private var weightInputStr = ""
    @State private var sugarLevelInputStr = ""
    @State private var symptomsInputStr: String = ""
    
    @State private var showSuccessAlert = false
    @State private var showErrorAlert = false
    
    // used to bounce back to homescreen on success
    @Environment(\.dismiss) private var dismiss

    var body: some View {
        Form {
            Section(header: Text("Date")) {
                DatePicker("Enter the date", selection: $dateInput, displayedComponents: .date)
            }
            
            Section(header: Text("Blood Pressure")) {
                TextField("Systolic blood pressure", text: $systolicBpInputStr)
                    .keyboardType(.decimalPad)
                TextField("Diastolic blood pressure", text: $diastolicBpInputStr)
                    .keyboardType(.decimalPad)
            }
            
            Section(header: Text("Weight")) {
                TextField("Weight in pounds", text: $weightInputStr)
                    .keyboardType(.decimalPad)
            }
            
            Section(header: Text("Morning sugar level")) {
                TextField("Sugar level", text: $sugarLevelInputStr)
                    .keyboardType(.decimalPad)
            }
            
            Section(header: Text("Symptoms")) {
                TextEditor(text: $symptomsInputStr)
                    .frame(height: 100)
                    .cornerRadius(5.0)
            }
            
            Section(footer: Text("Sample data for the past 7 days has been automatically added for convenience. You may override it by saving new data.")) {
                Button(action: {
                    if let systolicBp = Double(systolicBpInputStr),
                       let diastolicBp = Double(diastolicBpInputStr),
                       let weight = Double(weightInputStr),
                       let sugarLevel = Double(sugarLevelInputStr)
                    {
                        // create new input object
                        let dataInput = HealthInput(date: dateInput, systolicBp: systolicBp, diastolicBp: diastolicBp, weight: weight, sugarLevel: sugarLevel, symptoms: symptomsInputStr)
                        // update the dictionary
                        dataViewModel.addOrUpdateHealthInput(dataInput)
                        
                        showSuccessAlert = true
                    } else {
                        showErrorAlert = true
                    }
                }) {
                    Text("Save data")
                }
            }
        }
        .alert("Success", isPresented: $showSuccessAlert, actions: {
            Button("Ok", role: .cancel) {
                showSuccessAlert = false
                dismiss() // go back to home screen
            }
        }, message: {
            Text("Your health data has been successfully saved!")
        })
        .alert("Error", isPresented: $showErrorAlert, actions: {
            Button("Ok", role: .cancel) {
                showErrorAlert = false
            }
        }, message: {
            Text("Please check your inputs and try again.")
        })
    }
}

struct DataView_Previews: PreviewProvider {
    static var previews: some View {
        DataView(dataViewModel: HealthDataViewModel())
    }
}
