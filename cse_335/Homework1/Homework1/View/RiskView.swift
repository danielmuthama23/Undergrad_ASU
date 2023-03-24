//
//  RiskView.swift
//  Homework1
//
//  Created by Tyler Fichiera on 3/21/23.
//

import SwiftUI

struct RiskView: View {
    @ObservedObject var dataViewModel: HealthDataViewModel
    
    @State private var riskImage = ""
    @State private var imageColor = Color.black
    @State private var riskText = ""
    
    var body: some View {
        List {
            Section {
                HStack {
                    Spacer()
                    VStack {
                        Spacer()
                        Image(systemName: riskImage)
                            .resizable()
                            .frame(width: 100, height: 100)
                            .foregroundColor(imageColor)
                        Spacer()
                        Text(riskText)
                            .multilineTextAlignment(.center)
                        Spacer()
                    }
                    Spacer()
                }
            }
        }.onAppear(perform: {
            riskText = ""
            
            let bpRisk = dataViewModel.getBloodPressureRisk()
            let weightRisk = dataViewModel.getWeightRisk()
            let sugarRisk = dataViewModel.getSugarRisk()
            
            // check to make sure there is info for past 7 days
            if bpRisk == .cantDetermine ||
                weightRisk == .cantDetermine ||
                sugarRisk == .cantDetermine
            {
                riskImage = "questionmark.app.fill"
                imageColor = Color.gray.opacity(0.25)
                riskText = "Unable to determine risk. Please make data for the past seven days."
                return
            }
            
            // check for risks and build text field
            var messages: [String] = []
            if bpRisk == .risk {
                messages.append("Your blood pressure is high!")
            }
            if weightRisk == .risk {
                messages.append("You are gaining weight!")
            }
            if sugarRisk == .risk {
                messages.append("Your sugar level is high!")
            }
            
            if messages.count > 0 {
                riskImage = "exclamationmark.triangle"
                imageColor = Color.yellow
                riskText = messages.joined(separator: "\n")
            } else {
                riskImage = "face.smiling"
                imageColor = Color.green
                riskText = "You are in good health, keep up the good work"
            }
        })
    }
}

struct RiskView_Previews: PreviewProvider {
    static var previews: some View {
        RiskView(dataViewModel: HealthDataViewModel())
    }
}
