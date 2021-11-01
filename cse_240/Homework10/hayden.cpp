#include <iostream>
#include "hayden.h"

using namespace std;

// Q2a: Define displayBook() for Hayden class (5 points)
// Define the function displayBook() that you declared within the Hayden class in the header file
// See expected output in question file.
void Hayden::displayBook() {
    cout << "\nBook name: " << this->getName() << endl;
    cout << "Price: " << this->getPrice() << endl;
    cout << "Library: Hayden" << endl;
}

// (displayList() function in hw10.cpp should call this function.)
// Include necessary header files
