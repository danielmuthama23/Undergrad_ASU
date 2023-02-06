//
//  JupiterView.swift
//  Lab2
//
//  Created by Tyler Fichiera on 2/5/23.
//

import SwiftUI

struct JupiterView: View {
    @Environment(\.dismiss) var dismiss
    
    var weightFromEarth: Double
    var weightFromMoon: Double
    @Binding var comingFromMessage: String
    @Binding var shouldPopBack: Bool
    
    var body: some View {
        let weightOnJupiter = (weightFromEarth / 9.81) * 24.79
        
        VStack {
            Spacer()
            Text("You are on jupiter")
            
            Group {
                Spacer()
                Text("Your weight on earth is: \(weightFromEarth)")
                
                Spacer()
                Text("Your weight on moon is: \(weightFromMoon)")
                
                Spacer()
                Text("Your weight on jupiter is: \(weightOnJupiter)")
                
                Spacer()
                Text("I feel heavier!")
            }
            
            Spacer()
            Image("jupiter")
                .resizable()
                .frame(width: 200, height:175)
            
            Spacer()
            Button("Go back to moon") {
                comingFromMessage = "Coming from jupiter!"
                dismiss()
            }
            
            Spacer()
            Button("Go back to earth") {
                comingFromMessage = "Coming from jupiter!"
                shouldPopBack = true
                dismiss()
            }
        }
        .navigationTitle("Jupiter")
        .navigationBarTitleDisplayMode(.inline)
    }
}

struct JupiterView_Previews: PreviewProvider {
    static var previews: some View {
        JupiterView(weightFromEarth: 0, weightFromMoon: 0, comingFromMessage: .constant(""), shouldPopBack: .constant(false))
    }
}
