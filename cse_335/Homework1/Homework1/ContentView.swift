//
//  ContentView.swift
//  Homework1
//
//  Created by Tyler Fichiera on 3/6/23.
//

import SwiftUI

struct ContentView: View {
    var body: some View {
        NavigationView {
            VStack {
                Spacer()
                NavigationLink("Enter Data") {
                    DataView()
                }
                Spacer()
                NavigationLink("View My Health") {}
                Spacer()
                NavigationLink("Am I At Risk?") {}
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
