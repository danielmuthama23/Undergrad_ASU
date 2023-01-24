//
//  PartOne.swift
//  Lab1
//
//  Created by Tyler Fichiera on 1/23/23.
//

import SwiftUI

struct PartOne: View {
    @State var heightStr: String = ""
    @State var weightStr: String = ""
    @State var bmiStr: String = ""
    @State var bmiMsg: String = ""
    @State var bmiMsgColor: SwiftUI.Color?
    
    var body: some View {
        VStack {
            Text("BMI Calculator")
                .bold()
                .foregroundColor(.blue)
            Spacer()
            
            Group {
                HStack {
                    Text("Height (inches)")
                    Spacer()
                    TextField("71", text: $heightStr)
                }
                Spacer()
                
                HStack {
                    Text("Weight (lbs)")
                    Spacer()
                    TextField("162", text: $weightStr)
                }
                Spacer()
                
                HStack {
                    Text("BMI:\t\t\t\(bmiStr)")
                    Spacer()
                }
                Spacer()
            }
            
            Text(bmiMsg).foregroundColor(bmiMsgColor)
            Spacer()

            Button("Calculate BMI") {
                // convert str inputs to ints
                let height = Double(heightStr)!
                let weight = Double(weightStr)!
                
                // BMI = (weight in pounds/(height in inches)* (height in inches))*703
                let bmi = weight / (height * height) * 703
                bmiStr = String(bmi)
                
                switch bmi {
                case 0..<18:
                    bmiMsg = "You are underweight"
                    bmiMsgColor = .blue
                case 18..<25:
                    bmiMsg = "You are normal"
                    bmiMsgColor = .green
                case 25..<30:
                    bmiMsg = "You are pre-obese"
                    bmiMsgColor = .purple
                case 30...:
                    bmiMsg = "You are obese"
                    bmiMsgColor = .red
                default:
                    bmiMsg = "incorrect calculation of bmi"
                    bmiMsgColor = nil
                }
            }
            Spacer()
        }
        .padding()
    }
}

struct PartOne_Previews: PreviewProvider {
    static var previews: some View {
        PartOne()
    }
}
