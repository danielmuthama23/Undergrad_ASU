//
//  MoonView.swift
//  Lab2
//
//  Created by Tyler Fichiera on 2/5/23.
//

import SwiftUI

struct MoonView: View {
    @Environment(\.dismiss) var dismiss
    
    var weightFromEarth: Double
    @Binding var comingFromMessage: String
    @State var popBack = false;

    var body: some View {
        let weightOnMoon = weightFromEarth / 9.81 * 1.622
        
        VStack {
            Spacer()
            Text("You are on the moon")
            
            Group {
                Spacer()
                Text("Your weight on earth is: \(weightFromEarth)")
                
                Spacer()
                Text("Your weight on moon is: \(weightOnMoon)")
                
                Spacer()
                Text("I feel much lighter!")
                
                Spacer()
                Text(comingFromMessage.contains("moon") ? "" : comingFromMessage)
            }
            
            Spacer()
            Image("moon")
                .resizable()
                .frame(width: 175, height:175)
            
            Spacer()
            Button("Go back to earth") {
                comingFromMessage = "Coming from the moon!"
                dismiss()
            }
            
            Spacer()
            NavigationLink("Go to Jupiter") {
                JupiterView(weightFromEarth: weightFromEarth, weightFromMoon: weightOnMoon, comingFromMessage: $comingFromMessage, shouldPopBack: $popBack)
            }
        }
        .navigationTitle("Moon")
        .navigationBarTitleDisplayMode(.inline)
        .onChange(of: popBack) { data in
            popBack = false
            dismiss()
        }
    }
}

struct MoonView_Previews: PreviewProvider {
    static var previews: some View {
        MoonView(weightFromEarth: 0, comingFromMessage: .constant(""))
    }
}
