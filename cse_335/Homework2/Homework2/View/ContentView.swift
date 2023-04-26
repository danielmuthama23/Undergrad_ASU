//
//  ContentView.swift
//  Homework2
//
//  Created by Tyler Fichiera on 4/25/23.
//

import SwiftUI
import CoreData

import SwiftUI

struct ContentView: View {
    @ObservedObject var dataViewModel = HealthDataViewModel()
    
    var body: some View {
        NavigationView {
            VStack {
                Spacer()
                NavigationLink("Enter Data") {
                    DataView(dataViewModel: dataViewModel)
                }
                Spacer()
                NavigationLink("View My Health") {
                    HealthView(dataViewModel: dataViewModel)
                }
                Spacer()
            }
            .padding()
            .navigationBarTitleDisplayMode(.inline)
            .navigationTitle("Personal Health Monitoring System")
        }.navigationViewStyle(.stack)
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
