//
//  MovieDictionary.swift
//  Lab3
//
//  Created by Tyler Fichiera on 2/22/23.
//

import Foundation

class Movie {
    var title: String
    var genre: String
    var ticketSale: Float
    
    init(title: String, genre: String, ticketSale: Float) {
        self.title = title
        self.genre = genre
        self.ticketSale = ticketSale
    }
}

class MovieDictionary: ObservableObject {
    // main dictionary
    @Published var movies: [String:Movie] = [String:Movie] ()
    
    private var currentIndex: Int = 0
    
    init() {
        // add a few default movies
        self.add(title: "Grown Ups", genre: "Comedy", ticketSale: 10.50)
        self.add(title: "Superman", genre: "Action", ticketSale: 12.75)
    }
    
    func add(title: String, genre: String, ticketSale: Float) {
        let m = Movie(title: title, genre: genre, ticketSale: ticketSale)
        movies[title] = m
    }
    
    func delete(title: String) {
        movies[title] = nil
    }
    
    func search(title:String) -> Movie? {
        for (t, _) in movies {
            if title == t {
                return movies[t]
            }
        }
        return nil
    }
    
    func edit(title: String, genre: String, ticketSale: Float) -> Movie? {
        let foundMovie = search(title: title)
        if foundMovie == nil {
            return nil
        }
        let newMovie = Movie(title: title, genre: genre, ticketSale: ticketSale)
        movies[title] = newMovie
        return newMovie
    }
    
    // handle the prev/next buttons here
    func prev() -> Movie? {
        let moviesArray = Array(movies.values)
        
        if currentIndex > 0 {
            currentIndex  = currentIndex - 1
            return moviesArray[currentIndex]
        }
        return nil
    }
    
    func next() -> Movie? {
        let moviesArray = Array(movies.values)
        
        if currentIndex < moviesArray.count - 1 {
            currentIndex  = currentIndex + 1
            return moviesArray[currentIndex]
        }
        return nil
    }
    
    func getCurrentMovie() -> Movie? {
        let moviesArray = Array(movies.values)
        
        if currentIndex < moviesArray.count {
            return moviesArray[currentIndex]
        }
        return nil
    }
    
    // used to reset to the beginning in case the order is messed up
    func setToBeginning() -> Movie? {
        currentIndex = 0

        let moviesArray = Array(movies.values)
        
        if currentIndex < moviesArray.count {
            return moviesArray[currentIndex]
        }
        return nil
    }
}
