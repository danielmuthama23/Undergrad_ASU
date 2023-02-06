//
//  ContentView.swift
//  Lab2
//
//  Created by Tyler Fichiera on 2/5/23.
//

import SwiftUI

struct ContentView: View {
    @State var earthWeightStr = ""
    @State var comingFromMessage = ""
    @State var isActiveRoot = false
    
    var body: some View {
        NavigationView {
            VStack {
                Group {  
                    Spacer()
                    Text("Welcome to Space Walk App")
                    
                    Spacer()
                    Text("You are on earth now")
                    
                    Spacer()
                    Text(comingFromMessage)
                }
                
                Spacer()
                HStack {
                    Spacer()
                    Text("Enter your weight:")
                    Spacer()
                    TextField("", text:$earthWeightStr).textFieldStyle(.roundedBorder).keyboardType(.decimalPad)
                    Spacer()
                }
                
                Spacer()
                Image("earth")
                    .resizable()
                    .frame(width: 175, height:175)
                
                Spacer()
                let weightFromEarth = Double(earthWeightStr) != nil ? Double(earthWeightStr)! : 0
                NavigationLink("Go to Moon") {
                    MoonView(weightFromEarth: weightFromEarth, comingFromMessage: $comingFromMessage)
                }
                .navigationTitle("Earth")
                .navigationBarTitleDisplayMode(.inline)
                            
                Spacer()
            }
        }.navigationViewStyle(.stack)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
