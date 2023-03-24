//
//  ContentView.swift
//  Homework1
//
//  Created by Tyler Fichiera on 3/6/23.
//

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
                NavigationLink("Am I At Risk?") {
                    RiskView(dataViewModel: dataViewModel)
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
