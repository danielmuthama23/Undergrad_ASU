//
//  ContentView.swift
//  2_SwiftUI
//
//  Created by Tyler Fichiera on 1/18/23.
//

import SwiftUI

struct ContentView: View {
    @State var firstName: String = ""
    @State var lastName: String = ""
    @State var greeting: String = ""
    
    var body: some View {
        VStack {
            Text("Lecture Activity 1").bold()
            Spacer()

            HStack {
                Text("First name")
                Spacer()
                Spacer()
                TextField("first", text: $firstName)
            }
            HStack {
                Text("Last name")
                Spacer()
                Spacer()
                TextField("last", text: $lastName)
            }
            Spacer()
            
            Button("Greeting") {
                self.greeting = "\(firstName) \(lastName) Welcome to CSE 335"
            }
            Spacer()

            Text(greeting)
        }
        .padding()
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
