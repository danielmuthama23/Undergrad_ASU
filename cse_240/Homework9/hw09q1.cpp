// CSE240 Fall 2021 HW9
// Tyler Fichiera
// Write the compiler used: g++

// READ BEFORE YOU START:
// You are given a partially completed program which consist of a class 'Patient' defined in patient.h
// The definitions of class member functions are to be filled in patient.cpp
// hw09q1.c (this file) creates an array of objects 'p[]' and uses a menu driven program to add a patient, display patient info, 
// sort the patient list and to find the oldest patient(by birth year).
// You should start completing the program from from Q1. Question numbers are given around line 33.
// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk getting compile error.
// You are not allowed to modify main ().

// ***** WRITE COMMENTS FOR IMPORANT STEPS OF YOUR CODE. *****
// ***** GIVE MEANINGFUL NAMES TO VARIABLES. *****

#include "patient.h"
#include <iostream>
#include <string>

#define MAX_PATIENTS 5

using namespace std;

// forward declaration of functions (already implmented)
void executeAction(char);

// functions that need implementation:
// in patient.cpp :
// Q1 Patient constructor		// 2 points
// Q2 Patient member functions // 18 points

// in this file (hw09q1.cpp) : Q3 to Q6
int addPatient(string name_input, int age_input, int DOByear_input, int ID_input); // 10 points
void displayPatients(); // 5 points
void sort(); // 10 points
void oldestPatient(); // 5 points

Patient s[MAX_PATIENTS]; // array of objects
int currentCount = 0; // number of patients in the list

int main() {
	// initialized to a dummy value
	char choice = 'i';
	do {
		cout << "\nCSE240 HW9\n";
		cout << "Please select an action:\n";
		cout << "\t a: add a new patient\n";
		cout << "\t d: display patient list\n";
		cout << "\t s: sort the patients in descending order based on age (within a range)\n";
		cout << "\t n: display the oldest patient whose name starts with a specific letter\n";
		cout << "\t q: quit\n";
		cin >> choice;
		cin.ignore(); // ignores the trailing \n
		executeAction(choice);
	} while (choice != 'q');

	return 0;
}

// Ask for details from user for the given selection and perform that action
// Read the function case by case
void executeAction(char c) {
	string name_input;
	int age_input, DOByear_input, ID_input, result = 0;

	switch (c) {
		case 'a': // add patient
			// input patient details from user
			cout << "Please enter patient name: ";
			getline(cin, name_input);
			cout << "Please enter age: ";
			cin >> age_input;
			cin.ignore();
			cout << "Please enter year of birth: ";
			cin >> DOByear_input;
			cin.ignore();
			cout << "Please enter ID: ";
			cin >> ID_input;
			cin.ignore();

			// add the patient to the list
			result = addPatient(name_input, age_input, DOByear_input, ID_input);
			if (result == 0)
				cout << "\nThat patient is already in the list or list is full! \n\n";
			else
				cout << "\nPatient successfully added to the list! \n\n";
			break;

		case 'd': // display the list
			displayPatients();
			break;

		case 's': // sort the list
			sort();
			break;

		case 'n': // find and display oldestt patient
			oldestPatient();
			break;

		case 'q': // quit
			break;

		default: cout << c << " is invalid input!\n";
	}

}

// Q3 addPatient (10 points)
// This function adds a new patient with the details given in function arguments.
// Add the patient in 'p' (array of objects) only if there is remaining capacity in the array and if the patient does not already exist in the list
// This function returns 1 if the patient is added successfully, else it returns 0 for the cases mentioned above.
// Assume user enters age in 0.0 - any positive integer range.
int addPatient(string name_input, int age_input, int DOByear_input, int ID_input) {
	// check if the array is full
	if (currentCount == MAX_PATIENTS) {
		return 0;
	}

	// check for duplicates in array based on name
	for (int i = 0; i < currentCount; i++) {
		if (name_input.compare(s[i].getName()) == 0) {
			return 0;
		}
	}

	// create new patient
	Patient* patient = new Patient();
	patient->setName(name_input);
	patient->setAge(age_input);
	patient->setDOByear(DOByear_input);
	patient->setID(ID_input);

	// append to array
	s[currentCount] = *patient;

	// increment currentCount
	currentCount++;
	
	return 1;
}

// Q4 displayPatients (5 points)
// This function displays the list of patients.
// Parse the object array 'p' and display the details of all patientss in the array. See expected output given in question file.
// You can call the class function 'displayPatients()' here. Note that these are two different functions.
// Patient::displayPatient() displays details of one Patient object, while displayPatients() should display all patients
void displayPatients() {
	// iterate through all element in array and call displayPatient
	for (int i = 0; i < currentCount; i++) {
		s[i].displayPatient();
	}
}

// Q5 sort (10 points)
// This function sorts the patients in descending order of age, and then display the patients within a given range.
// You may use the 'temp' object for sorting logic, if needed.
void sort() {
	// get a store inputs for the age range
	int lower_bound, higher_bound;
	cout << "Please enter the lower bound of age: ";
	cin >> lower_bound;
	cin.ignore();
	cout << "Please enter the higher bound of age: ";
	cin >> higher_bound;
	cin.ignore();

	// use sort method to sort list without using temp array
	for (int i = 0; i < currentCount; i++) {
		for (int j = i + 1; j < currentCount; j++) {
			if (s[i].getAge() < s[j].getAge()) {
				Patient temp = s[i];
				s[i] = s[j];
				s[j] = temp;
			}
		}
	}

	// display all patients in the range [lower_bound, higher_bound]
	for (int i = 0; i < currentCount; i++) {
		if (s[i].getAge() <= higher_bound && s[i].getAge() >= lower_bound) {
			s[i].displayPatient();
		}
	}
}

// Q6 oldestPatient (5 points)
// This functions displays patients who is oldest and whose name starts with a specific letter
// Parse the array to check if the patient is the oldest patient based of the character input
// If the patient is the oldest patient year then copy that patient's details (object's data members) 
// to 'newPatient' object created using 'new' and display those patient details using 'newPatient' object.
// Finally delete the 'newPatient' object.
// NOTE: You necessarily have to use the 'newPatient' object to store the patient details in it and delete it after displaying.
//       You should not display patient details using 'p[]' object.
void oldestPatient() {
	// Ask the user for a char
	char startingCharacter;
	cout << "Enter the first letter of the patients' first name: ";
	cin >> startingCharacter;
	cin.ignore();

	// tempList to store all Patients that start with `startingChar`
	Patient tempList[currentCount];
	int c = 0;

	for (int i = 0; i < currentCount; i++) {
		// check if name starts with `startingCharacter`
		if (s[i].getName()[0] == startingCharacter) {
			tempList[c] = s[i];
			c++;
		}
	}

	// return if no patients start with `startingCharacter`
	if (c == 0) {
		return;
	}


	// currentOldest is used for sorting
	Patient currentOldest = tempList[0];
	for (int i = 1; i < c; i++) {
		if (tempList[i].getAge() > currentOldest.getAge()) {
			currentOldest = tempList[i];
		}
	}

	// create newPatient then copy over data
	Patient* newPatient = new Patient;
	newPatient->setName(currentOldest.getName());
	newPatient->setAge(currentOldest.getAge());
	newPatient->setDOByear(currentOldest.getDOByear());
	newPatient->setID(currentOldest.getID());

	// call display on new object
	newPatient->displayPatient();

	// delete newPatient after execution
	delete newPatient;
}
