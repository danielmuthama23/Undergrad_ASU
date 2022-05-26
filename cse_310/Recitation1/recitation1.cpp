// CSE310 Summer 2022 (C) - Recitation #1
// Tyler Fichiera - 1218959911
// 05/25/2022

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

// function declarations
void executeAction(int choice);
void addRecord(string name, double final_avg);
void displayRecords();

// custom student record data type
struct StudentRecord {
	string name;
	double final_avg;
	struct StudentRecord* next; // pointer to next node
}*list = NULL;

// student record count
int records_count = 0;

int main() {
    int choice;

    do {
		cout << "\nCSE310 Recitation1\n";
		cout << "Please enter your selection:\n";
		cout << "1. Add student record\n";
		cout << "2. Display student records\n";
		cout << "3. Count number of records\n";
		cout << "4. Exit\n";
		cin >> choice;
		cin.ignore();
		executeAction(choice);
	} while (choice != 4);

    return 0;
}

void executeAction(int choice) {
	switch (choice) {
		// add student record
		case 1: {
			string student_name;
			double final_avg;

			cout << "\nEnter student's name: ";
			getline(cin, student_name);
			cout << "Enter student's final average: ";
			cin >> final_avg;
			cin.ignore();

			addRecord(student_name, final_avg);

			break;
		}

		// display student records
		case 2:
			displayRecords();
			break;

		// count number of records
		case 3:
			cout << records_count << endl;
			break;

		// exit
		case 4:
			break;

		default:
			cout << choice << " is an invalid input!\n";
			break;
	}
}

void addRecord(string name, double final_avg) {
	struct StudentRecord* tempList = list; // work on a copy of 'list'

	// create temp student record
	StudentRecord *student = new StudentRecord();
	student->name = name;
	student->final_avg = final_avg;
	student->next = NULL;

	if (records_count == 0) {
		list = student;
	} else {
		// iterate through all elements in the linked list
		while (tempList->next != NULL) {
			tempList = tempList->next;
		}

		// add new book as last element in linked list
		tempList->next = student;
	}

	// increment record count
	records_count++;
}

void displayRecords() {
	// check if list is empty
	if (records_count == 0) {
		cout << "No student records\n";
		return;
	}

	struct StudentRecord* tempList = list; // work on a copy of 'list'

	// traverse all elements and print out their values
	while (tempList != NULL) {
		// print out info
		cout << tempList->name << "\t\t" << tempList->final_avg << endl;

		// increment to next node
		tempList = tempList->next;
	}
}
