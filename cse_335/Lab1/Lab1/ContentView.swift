//
//  ContentView.swift
//  Lab1
//
//  Created by Tyler Fichiera on 1/23/23.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        NavigationView {
            VStack {
                Label("Lab 1 - CSE 335", systemImage: "")
                Label("Tyler Fichiera", systemImage: "")
                Label("BMI Calculation App",  systemImage: "")
                Spacer()

                NavigationLink(destination: PartOne()) {
                    Text("Part 1")
                }.buttonStyle(PlainButtonStyle())
                Spacer()

                NavigationLink(destination: PartTwo()) {
                    Text("Part 2")
                }.buttonStyle(PlainButtonStyle())
                Spacer()
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
