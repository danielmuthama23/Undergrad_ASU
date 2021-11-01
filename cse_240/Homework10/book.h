#ifndef _BOOK_H_
#define _BOOK_H_

#include <string>
using namespace std;

enum libraryType { hayden = 0, noble };	// definition of libraryType

class Book {
	private:
		string name; // private data members
		double price;
		libraryType lib;

	public:
		Book(string bookName, double price, libraryType libType); // constructor

		// accessor methods
		string getName();
		double getPrice();
		libraryType getLibraryType();

		virtual void displayBook() {}

		// Q3a: Declare Friend Function changePrice()  (1 point)
		// Declare a friend function named changePrice() which has 2 parameters and no return value.
		// The first parameter is a pointer to Book class, and the second is a double which is the new unit price.
		// You need to define this function in hw10.cpp and call this function in case 'c' of executeAction() in hw10.cpp file
		friend void changePrice(Book *book, double newPrice);
};

#endif // _BOOK_H_
