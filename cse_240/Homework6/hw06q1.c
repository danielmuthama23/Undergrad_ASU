// CSE240 Fall 2021 HW6
// Tyler Fichiera
// Write the compiler used: gcc

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996) // for Visual Studio Only

#define MAX_BOOKS 15
#define MAX_NAME_LENGTH 25

typedef enum { Nonfiction = 0, Fiction } bookType; // enum type

struct libraryRecord { // struct for book details
	char bookTitle[MAX_NAME_LENGTH];
	char author[MAX_NAME_LENGTH];
	bookType booktype;
	unsigned int bookId;
	unsigned int aisle;
	struct libraryRecord* next; // pointer to next node
}*list = NULL; // declare linked list 'list'

// the number of books currently stored in the list (initialized to 0)
int count = 0;

// functions already implmented
void flushStdIn();
void executeAction(char);
void save(char* fileName);

// functions that need implementation:
int add(char* bookTitle_input, char* author_input, char* booktype_input, unsigned int bookId_input, unsigned int aisle_input); // 20 points
void sort(); // 10 points
int delete(unsigned int bookId_input); // 10 points
void load(char* fileName); // 10 points
void display(); // given

int main() {
	char* fileName = "Book_List.txt";
	load(fileName); // load list of books from file (if it exists). Initially there will be no file.
	char choice = 'i'; // initialized to a dummy value
	do {
		printf("\nEnter your selection:\n");
		printf("\t a: add a new book\n");
		printf("\t d: display book list\n");
		printf("\t r: remove a book from list\n");
		printf("\t s: sort book list by ID\n");
		printf("\t q: quit\n");
		choice = getchar();
		flushStdIn();
		executeAction(choice);
	} while (choice != 'q');

	save(fileName); // save list of books to file (overwrites file, if it exists)
	return 0;
}

// flush out leftover '\n' characters
void flushStdIn() {
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

// ask for details from user for the given selection and perform that action
void executeAction(char c) {
	char bookTitle_input[MAX_NAME_LENGTH], author_input[MAX_NAME_LENGTH];
	unsigned int bookId_input, aisle_input, add_result = 0;
	char booktype_input[20];
	switch (c) {
		case 'a':
			// input book record from user
			printf("\nEnter book title: ");
			fgets(bookTitle_input, sizeof(bookTitle_input), stdin);
			bookTitle_input[strlen(bookTitle_input) - 1] = '\0'; // discard the trailing '\n' char
			printf("Enter author name: ");
			fgets(author_input, sizeof(author_input), stdin);
			author_input[strlen(author_input) - 1] = '\0';	// discard the trailing '\n' char
			printf("Enter book type (Fiction/ Nonfiction): ");
			fgets(booktype_input, sizeof(booktype_input), stdin);
			booktype_input[strlen(booktype_input) - 1] = '\0';	// discard the trailing '\n' char
			printf("Please enter book ID number: ");
			scanf("%d", &bookId_input);
			printf("Please enter aisle number: ");
			scanf("%d", &aisle_input);
			flushStdIn();

			// add the book to the list
			add_result = add(bookTitle_input, author_input, booktype_input, bookId_input, aisle_input);
			if (add_result == 0)
				printf("\nBook is already on the list! \n\n");
			else if (add_result == 1)
				printf("\nBook successfully added to the list! \n\n");
			else
				printf("\nUnable to add. Book list is full! \n\n");
			break;

		case 'r':
			printf("Please enter ID number of book to be deleted: ");
			scanf("%d", &bookId_input);
			flushStdIn();
			int delete_result = delete(bookId_input);
			if (delete_result == 0)
				printf("\nBook not found in the list! \n\n");
			else
				printf("\nBook deleted successfully! \n\n");
			break;
		case 'd': display(); break;
		case 's': sort(); break;
		case 'q': break;
		default: printf("%c is invalid input!\n", c);
	}
}

// Q1 : add (10 points)
// This function is used to add a book into the list. You can simply add the new book to the end of list (linked list of structs).
// Do not allow the book to be added to the list if it already exists in the list. You can do that by checking book names AND IDs already in the list.
// If the book already exists then return 0 without adding it to the list. If the book does not exist in the list then add the book at the end of the list and return 1.
// If book list is full, then do not add new book to the list and return 2.
// NOTE: Notice how return type of add() is checked in case 'a' of executeAction()
// NOTE: You must convert the string 'booktype_input' to an enum type and store it in the list because the booktype has enum type (not string type).
// The list should be case sensitive. For instance, 'Roger' and 'roger' should be considered two different names.
// Hint: 'count' holds the number of books currently in the list
int add(char* bookTitle_input, char* author_input, char* booktype_input, unsigned int bookId_input, unsigned int aisle_input) {
	struct libraryRecord* tempList = list; // work on a copy of 'list'

	// return 2 if at max books
	if (count == MAX_BOOKS) {
		return 2;
	}

	// create temp book record
	struct libraryRecord* book = (struct libraryRecord*)malloc(sizeof(struct libraryRecord));
	strcpy(book->bookTitle, bookTitle_input);
	strcpy(book->author, author_input);
	// use ternary operator to convert string to enum type
	book->booktype = strcmp(booktype_input, "Fiction") == 0 ? Fiction : Nonfiction;
	book->bookId = bookId_input;
	book->aisle = aisle_input;
	// set next to null because it will be at the end of the linked list
	book->next = NULL;

	if (count == 0) {
		list = book;
		count++;
		return 1;
	}

	// iterate through all elements in the linked list
	while (tempList->next != NULL) {
		// check for duplicates
		if (
			strcmp(tempList->bookTitle, bookTitle_input) == 0 &&
			tempList->bookId == bookId_input
		) {
			return 0;
		}
		tempList = tempList->next;
	}

	// add new book as last element in linked list
	tempList->next = book;

	count++;

	return 1;
}

// This function displays the book list with the details (struct elements) of each book. 
// Q2. display (10 points)
// Display all books.
void display() {
	struct libraryRecord* tempList = list; // work on a copy of 'list'

	// traverse all elements and print out their values
	while (tempList != NULL) {
		printf("\nBook Title: %s", tempList->bookTitle); // display Book title
		printf("\nAuthor Name: %s", tempList->author); // display author	
		printf("\nBook Type: %s", tempList->booktype == Fiction ? "Fiction" : "Nonfiction"); // display book type
		printf("\nBook ID: %d", tempList->bookId); // display book id
		printf("\nAisle number: %d", tempList->aisle); // display aisle number
		printf("\n");

		// increment after each while loop
		tempList = tempList->next;
	}
}

// Q3 : sort (10 points)
// This function is used to sort the list(linked list of structs) numerically by book ID.
// Parse the list and compare the book IDs to check which one should appear before the other in the list.
// Sorting should happen within the list. That is, you should not create a new node of structs having sorted books.
void sort() {
	struct libraryRecord* tempList = list; // work on a copy of 'list'

	// bubble sort method similar to how I implemented it in assignment 5
	for (int i = 0; i < count; i++) {
		while (tempList->next != NULL) {
			// compare the two elements and if it is greater than, swap elements
			if (tempList->bookId > tempList->next->bookId) {
				char title[MAX_NAME_LENGTH], author[MAX_NAME_LENGTH];
				strcpy(title, tempList->bookTitle);
				strcpy(author, tempList->author);

				bookType bookType = tempList->booktype;
				int bookId = tempList->bookId;
				int aisle = tempList->aisle;

				strcpy(tempList->bookTitle, tempList->next->bookTitle);
				strcpy(tempList->author, tempList->next->author);
				tempList->booktype = tempList->next->booktype;
				tempList->bookId = tempList->next->bookId;
				tempList->aisle = tempList->next->aisle;

				strcpy(tempList->next->bookTitle, title);
				strcpy(tempList->next->author, author);
				tempList->next->booktype = bookType;
				tempList->next->bookId = bookId;
				tempList->next->aisle = aisle;
			}
			// increment to next elements
			tempList = tempList->next;
		}
	}

	// point head back to tempList
	tempList = list;

	// display message for user to check the result of sorting.
	printf("\nBook list sorted! Use display option 'd' to view sorted list.\n");
}

// save() is called at the end of main()
// This function saves the linked list of structures to file.
// save() is called at end of main() to save the book list to a file.
// The file is saved at the same place as your C file. For VS, the default directory looks like this:
// C:\Users\<username>\Documents\Visual Studio 2019\Projects\Project1\Project1
// You can simply delete the file to 'reset the list' or to avoid loading from it.
void save(char* fileName) {
	struct libraryRecord* tempList = list; // work on a copy of 'list'

	FILE* file;
	int booktypeValue = 0;
	file = fopen(fileName, "wb"); // open file for writing

	fwrite(&count, sizeof(count), 1, file); // First, store the number of books in the list

	// Parse the list and write book record to file
	while (tempList != NULL) {
		fwrite(tempList->bookTitle, sizeof(tempList->bookTitle), 1, file);
		fwrite(tempList->author, sizeof(tempList->author), 1, file);
		// convert enum to a number for storing
		if (tempList->booktype == Nonfiction)
			booktypeValue = 0; // 0 for Nonfiction
		else
			booktypeValue = 1; // 1 for Fiction

		fwrite(&booktypeValue, sizeof(booktypeValue), 1, file);
		fwrite(&tempList->bookId, sizeof(tempList->bookId), 1, file);
		fwrite(&tempList->aisle, sizeof(tempList->aisle), 1, file);

		tempList = tempList->next;
	}

	fclose(file); // close the file after writing
}

// Q4 : delete (10 points)
// This function is used to delete a book by ID.
// Parse the list and compare the book IDs to check which one should be deleted.
// Return 0 if the specified ID was not found. Return 1 upon successful removal of a record.
int delete(unsigned int bookId_input) {
	// if desired element is head, increment list by one then return
	if (list->bookId == bookId_input) {
		list = list->next;
		return 1;
	}

	// used to store return value of 0 or 1
	int value = 0;

	// work on a copy of 'list'
	struct libraryRecord* tempListCur = list;
	struct libraryRecord* tempListPrev = list;

	// iterate through all elements while their is a proceeding elements
	while (tempListCur != NULL && tempListCur->next != NULL) {
		// check for desired element and skip to the one after it to fully remove it
		if (tempListCur->next->bookId == bookId_input) {
			tempListCur->next = tempListCur->next->next != NULL ? tempListCur->next->next : NULL;
			// set value to 1 since element was found
			value = 1;
		}
		// increment tempList to next element
		tempListCur = tempListCur->next;
	}

	// set back to head
	list = tempListPrev;

	// return to value
	return value;
}

// Q5:  load (10 points)
// This function is called in the beginning of main().
// This function reads the book list from the saved file and builds the linked list of structures 'list'. 
// In the first run of the program, there will be no saved file because save() is called at the end of program.
// So at the begining of this function, write code to open the file and check if it exists. If file does not exist, then return from the function.
// (See expected output of add() in homework question file. It displays "Book_List.txt not found" because the file did not exist initially.)
// If the file exists, then parse the book list to read the book details from the file.
// Use the save function given above as an example of how to write this function. Notice the order in which the struct elements are saved in save()
// You need to use the same order to read the list back.
// NOTE: The saved file is not exactly readable because all elements of the struct are not string or char type.
//       So you need to implement load() similar to how save() is implemented. Only then the 'list' will be loaded correctly.
//		You can simply delete the file to 'reset the list' or to avoid loading from it.
void load(char* fileName) {
	// load file
	FILE *file = fopen(fileName, "rb");

	// check if it exists
	if (!file) {
		printf("%s not found\n", fileName);
		return;
	}

	// read the tempCount variable
	int tempCount = 0;
	fread(&tempCount, sizeof(tempCount), 1, file);

	// iterate through all elements in the list
	for (int i = 0; i < tempCount; i++) {
		// read and copy string vars
		char bookTitle[MAX_NAME_LENGTH], author[MAX_NAME_LENGTH];
		fread(bookTitle, sizeof(bookTitle), 1, file);
		fread(author, sizeof(author), 1, file);

		// read and copy int vars
		int bookType, bookId, aisle;
		fread(&bookType, sizeof(bookType), 1, file);
		fread(&bookId, sizeof(bookId), 1, file);
		fread(&aisle, sizeof(aisle), 1, file);

		// add to linked list using existing method
		add(bookTitle, author, bookType == 0 ? "Fiction" : "Nonfiction", bookId, aisle);
	}

	printf("Books record loaded from %s.\n", fileName);
	fclose(file);
}