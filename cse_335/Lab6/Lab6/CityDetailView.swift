//
//  CityDetailView.swift
//  Lab6
//
//  Created by Tyler Fichiera on 3/30/23.
//

import SwiftUI

struct CityDetailView: View {
    @State var cityName: String
    @State var cityImage: Data
    @State var cityDescription: String

    var body: some View {
        VStack {
            Spacer()
            Text(cityName)
                .fontWeight(.bold)
            Spacer()

            Image(uiImage: UIImage(data: cityImage) ?? UIImage())
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
        CityDetailView(cityName: "Phoenix, Arizona", cityImage: Data(), cityDescription: "Small Description Here")
    }
}
