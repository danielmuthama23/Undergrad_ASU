#include "book.h"

// definitions of Book member functions
Book::Book(string bookName, double price_input, libraryType libType) {
	name = bookName;
	price = price_input;
	lib = libType;
}

string Book::getName() {
	return name;
}

double Book::getPrice() {
	return price;
}

libraryType Book::getLibraryType() {
	return lib;
}
