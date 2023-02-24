//
//  ContentView.swift
//  Lab3
//
//  Created by Tyler Fichiera on 2/22/23.
//

import SwiftUI

struct ContentView: View {
    @State var movieDict: MovieDictionary = MovieDictionary()
    @State var displayMsg: String = ""
    
    @State var movieTitle: String = ""
    @State var movieGenre: String = ""
    @State var movieTicketSale: String = ""
    
    var body: some View {
        NavigationView {
            VStack {
                Header(movieDict: movieDict, displayMsg: $displayMsg, movieTitle: $movieTitle, movieGenre: $movieGenre, movieTicketSale: $movieTicketSale)
                Spacer()
                Main(movieDict: movieDict, displayMsg: $displayMsg, movieTitle: $movieTitle, movieGenre: $movieGenre, movieTicketSale: $movieTicketSale)
                Spacer()
                Footer(movieDict: movieDict, displayMsg: $displayMsg, movieTitle: $movieTitle, movieGenre: $movieGenre, movieTicketSale: $movieTicketSale)
            }
            .padding()
            .navigationBarTitleDisplayMode(.inline)
            .navigationTitle("My Favorite Movie App")
        }.onAppear(perform: {
            // this sets the default info while loading the page
            let m  = movieDict.getCurrentMovie()
            if m != nil {
                movieTitle = m!.title
                movieGenre = m!.genre
                movieTicketSale = "\(m!.ticketSale)"
            }
        })
    }
}

struct Header: View {
    @ObservedObject var movieDict: MovieDictionary
    @Binding var displayMsg: String
    
    @Binding var movieTitle: String
    @Binding var movieGenre: String
    @Binding var movieTicketSale: String
    
    @State var showDeleteAlert = false
    @State var showAddAlert = false
    
    @State var deleteMovieName: String = ""
    
    @State var addMovieName: String = ""
    @State var addMovieGenre: String = ""
    @State var addMovieTicketSaleText: String = ""
    
    var body: some View {
        Text("")
            .toolbar {
                ToolbarItem(placement: .navigationBarLeading) {
                    Button(action: {
                        showDeleteAlert = true
                    }, label: {
                        Image(systemName: "trash")
                    })
                }
                ToolbarItem(placement: .navigationBarTrailing) {
                    Button(action: {
                        showAddAlert = true
                    }, label: {
                        Image(systemName: "plus.app")
                    })
                }
            }
            .alert("Delete Movie", isPresented: $showDeleteAlert, actions: {
                TextField("Enter Movie Name", text: $deleteMovieName)

                Button("Delete", action: {
                    movieDict.delete(title: deleteMovieName)
                    displayMsg = "Movie deleted if title exists"
                    // changes the screen if you delete the item already being shown
                    if deleteMovieName == movieTitle {
                        let m = movieDict.setToBeginning()
                        if m != nil {
                            movieTitle = m!.title
                            movieGenre = m!.genre
                            movieTicketSale = "\(m!.ticketSale)"
                        } else {
                            movieTitle = ""
                            movieGenre = ""
                            movieTicketSale = ""
                        }
                    }
                    deleteMovieName = ""
                })
                Button("Cancel", role: .cancel, action: {
                    showDeleteAlert = false
                    deleteMovieName = ""
                })
            }, message: {
                Text("Please enter movie title to delete the record.")
            })
            .alert("Add Movie", isPresented: $showAddAlert, actions: {
                TextField("Movie Name", text: $addMovieName)
                TextField("Movie Genre", text: $addMovieGenre)
                TextField("Ticket Sale", text: $addMovieTicketSaleText)

                Button("Add", action: {
                    movieDict.add(title: addMovieName, genre: addMovieGenre, ticketSale: Float(addMovieTicketSaleText) ?? 0)
                    displayMsg = "Movie has been successfully added"
                    addMovieName = ""
                    addMovieGenre = ""
                    addMovieTicketSaleText = ""
                })
                Button("Cancel", role: .cancel, action: {
                    showAddAlert = false
                    addMovieName = ""
                    addMovieGenre = ""
                    addMovieTicketSaleText = ""
                })
            }, message: {
                Text("Please enter movie title details to add record.")
            })
    }
}

struct Main: View {
    @ObservedObject var movieDict: MovieDictionary
    @Binding var displayMsg: String
    
    @Binding var movieTitle: String
    @Binding var movieGenre: String
    @Binding var movieTicketSale: String
    
    @State var saveDisabled: Bool = true
    
    var body: some View {
        VStack {
            Spacer()
            Spacer()
            HStack {
                Text("Title:").foregroundColor(.blue)
                Text(movieTitle).textFieldStyle(.roundedBorder)
            }
            HStack {
                Text("Genre:").foregroundColor(.blue)
                TextField("", text: $movieGenre, onEditingChanged: { _ in
                    saveDisabled = false
                }).textFieldStyle(.roundedBorder)
            }
            HStack {
                Text("Ticket Sale:").foregroundColor(.blue)
                TextField("", text: $movieTicketSale, onEditingChanged: { _ in
                    saveDisabled = false
                }).textFieldStyle(.roundedBorder)
            }
            
            Spacer()
            Button("Save Edit") {
                let m = movieDict.edit(title: movieTitle, genre: movieGenre, ticketSale: Float(movieTicketSale) ?? 0)
                movieTitle = m!.title
                movieGenre = m!.genre
                movieTicketSale = "\(m!.ticketSale)"
                displayMsg = "Movie has been edited"
            }
            .disabled(saveDisabled)

            Spacer()
            Text(displayMsg)

            Spacer()
        }
        .padding()
    }
    
    func setMovie() {
        print("here")
    }
}

struct Footer: View {
    @ObservedObject var movieDict: MovieDictionary
    @Binding var displayMsg: String
    
    @Binding var movieTitle: String
    @Binding var movieGenre: String
    @Binding var movieTicketSale: String
    
    @State var showSearchAlert = false
    
    @State var searchTitle: String = ""
    
    var body: some View {
        Text("")
            .toolbar {
                ToolbarItemGroup(placement: .bottomBar) {
                    Spacer()
                    Button(action: {
                        let m = movieDict.prev()
                        if m != nil {
                            movieTitle = m!.title
                            movieGenre = m!.genre
                            movieTicketSale = "\(m!.ticketSale)"
                            displayMsg = ""
                        } else {
                            displayMsg = "Showing the first record"
                        }
                    },
                    label: {
                        Text("Prev")
                    })

                    Spacer()
                    Button(action: {
                        showSearchAlert = true
                    },
                    label: {
                        Image(systemName: "magnifyingglass")
                    })

                    Spacer()
                    Button(action: {
                        let m = movieDict.next()
                        if m != nil {
                            movieTitle = m!.title
                            movieGenre = m!.genre
                            movieTicketSale = "\(m!.ticketSale)"
                            displayMsg = ""
                        } else {
                            displayMsg = "No more records"
                        }
                    },
                    label: {
                        Text("Next")
                    })
                    Spacer()
                }
            }.alert("Search Movies", isPresented: $showSearchAlert, actions: {
                TextField("Movie Title", text: $searchTitle)

                Button("Search", action: {
                    let m = movieDict.search(title: searchTitle)
                    if m != nil {
                        movieTitle = m!.title
                        movieGenre = m!.genre
                        movieTicketSale = "\(m!.ticketSale)"
                        displayMsg = ""
                    } else {
                        displayMsg = "No movie found with that title"
                    }
                    searchTitle = ""
                    showSearchAlert = false
                })
                Button("Cancel", role: .cancel, action: {
                    searchTitle = ""
                    showSearchAlert = false
                })
            }, message: {
                Text("Please enter movie name to search.")
            })
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
