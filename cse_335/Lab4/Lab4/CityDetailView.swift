//
//  CityDetailView.swift
//  Lab4
//
//  Created by Tyler Fichiera on 2/28/23.
//

import SwiftUI

struct CityDetailView: View {
    @State var cityName: String
    @State var cityImage: String
    @State var cityDescription: String

    var body: some View {
        VStack {
            Spacer()
            Text(cityName)
                .fontWeight(.bold)
            Spacer()

            Image(cityImage)
                .resizable()
                .scaledToFit()
                .frame(height: 200)
                .cornerRadius(10)

            Spacer()
            Text(cityDescription)
            Spacer()
        }
    }
}

struct CityDetailView_Previews: PreviewProvider {
    static var previews: some View {
        CityDetailView(cityName: "Phoenix, Arizona", cityImage: "sample-city", cityDescription: "Small Description Here")
    }
}
