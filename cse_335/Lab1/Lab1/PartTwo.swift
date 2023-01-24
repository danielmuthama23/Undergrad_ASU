//
//  PartTwo.swift
//  Lab1
//
//  Created by Tyler Fichiera on 1/23/23.
//

import SwiftUI

struct PartTwo: View {
    @State var height: Double = 0
    @State var weight: Double = 0
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
                    Slider(value: $height, in: 1...100, step: 0.001, onEditingChanged: { _ in
                        self.calculateBMI()
                    })
                }
                Text("\(height)")
                Spacer()
                
                HStack {
                    Text("Weight (lbs)")
                    Spacer()
                    Slider(value: $weight, in: 1...500, step: 0.001, onEditingChanged: { _ in
                        self.calculateBMI()
                    })
                }
                Text("\(weight)")
                Spacer()
                
                HStack {
                    Text("BMI:\t\t\t\(bmiStr)")
                    Spacer()
                }
                Spacer()
            }
            
            Text(bmiMsg).foregroundColor(bmiMsgColor)
            Spacer()
            Spacer()
        }
        .padding()
    }
    
    func calculateBMI() {
        // don't calculate if the weight or height is 0
        if weight == 0 || height == 0 {
            return
        }

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
}

struct PartTwo_Previews: PreviewProvider {
    static var previews: some View {
        PartTwo()
    }
}
