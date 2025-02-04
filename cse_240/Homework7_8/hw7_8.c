// CSE240 Fall 2021 HW 7 & 8
// Tyler Fichiera
// Write the compiler used: gcc

// READ BEFORE YOU START:
// You are given a partially completed program that creates a linked list of employee information.
// The global linked list 'list' is a list of employees with each node being struct 'employeeNode'.
// 'employeeNode' consists of struct 'employee' which has: employee name, room number, and a linked list of 'supervisors'.
// The linked list of supervisors has each node containing simply the name of the supervisor.
// HW7 ignores the 'supervisors' linked list since there is no operation/manipulation to be done on 'supervisors' list in HW7.
// HW8 has operations/manipulations to be done with 'supervisors' list like add a supervisor, display last added supervisor.

// To begin, you should trace through the given code and understand how it works.
// Please read the instructions above each required function and follow the directions carefully.
// If you modify any of the given code, the return types, or the parameters, you risk getting compile error.
// You are not allowed to modify main ().
// You can use string library functions.

// ***** WRITE COMMENTS FOR IMPORANT STEPS OF YOUR CODE. *****
// ***** GIVE MEANINGFUL NAMES TO VARIABLES. *****
// ***** Before implementing any function, see how it is called in executeAction() *****

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning(disable: 4996) // for Visual Studio

#define MAX_NAME 30

// global linked list 'list' contains the list of employees
struct employeeNode {
	struct employee* employee;
	struct employeeNode* next;
}*list = NULL; // currently empty list

// structure "employee" contains the employee's name, room number and linked list of supervisors
struct employee {
	char name[MAX_NAME];
	unsigned int roomNumber;
	struct supervisor* supervisors; // linked list 'supervisors' contains names of supervisors
};

// structure 'supervisor' contains supervisor's name 
struct supervisor {
	char name[MAX_NAME];
	struct supervisor* next;
};

// forward declaration of functions (already implmented)
void flushStdIn();
void executeAction(char);

// functions that need implementation:
// HW 7
void addEmployee(char* employeeNameInput, unsigned int roomNumInput); // 20 points
void displayEmployeeList(struct employeeNode* tempList); // 15 points
struct employee* searchEmployee(char* employeeNameInput); // 15 points
//HW 8
void addSupervisor(char* employeeNameInput, char* supervisorNameInput);	// 15 points
void displayEmployeeSupervisorList(struct employeeNode* tempList); // 15 points
void removeEmployee(char* employeeNameInput); // 20 points

int main() {
	char selection = 'a'; // initialized to a dummy value
	do {
		printf("\nCSE240 HW 7,8\n");
		printf("Please enter your selection:\n");
		printf("HW7:\n");
		printf("\t a: add a new employee to the list\n");
		printf("\t d: display employee list (no supervisors)\n");
		printf("\t b: search for an employee on the list\n");
		printf("\t q: quit\n");
		printf("HW8:\n");
		printf("\t c: add a supervisor of a employee\n");
		printf("\t l: display employees who report to a specific supervisor\n");
		printf("\t r: remove an employee\n");
		printf("\t q: quit\n");

		selection = getchar();
		flushStdIn();
		executeAction(selection);
	} while (selection != 'q');

	return 0;
}

// flush out leftover '\n' characters
void flushStdIn() {
	char c;
	do c = getchar();
	while (c != '\n' && c != EOF);
}

// Ask for details from user for the given selection and perform that action
// Read the function case by case
void executeAction(char c) {
	char employeeNameInput[MAX_NAME], supervisorNameInput[MAX_NAME];
	unsigned int roomNumInput;
	struct employee* searchResult = NULL;

	switch (c) {
		// add employee
		case 'a':
			// input employee details from user
			printf("\nPlease enter employee's name: ");
			fgets(employeeNameInput, sizeof(employeeNameInput), stdin);
			employeeNameInput[strlen(employeeNameInput) - 1] = '\0'; // discard the trailing '\n' char
			printf("Please enter room number: ");
			scanf("%d", &roomNumInput);
			flushStdIn();

			if (searchEmployee(employeeNameInput) == NULL)	// un-comment this line after implementing searchEmployee()					
			//if (1)									// comment out this line after implementing searchEmployee()
			{
				addEmployee(employeeNameInput, roomNumInput);
				printf("\nEmployee successfully added to the list!\n");
			} else {
				printf("\nThat employee is already on the list!\n");
			}
			break;

		// display the list
		case 'd':
			displayEmployeeList(list);
			break;

		// search for an employee on the list
		case 'b':
			printf("\nPlease enter employee's name: ");
			fgets(employeeNameInput, sizeof(employeeNameInput), stdin);
			employeeNameInput[strlen(employeeNameInput) - 1] = '\0'; // discard the trailing '\n' char

			if (searchEmployee(employeeNameInput) == NULL)	// un-comment this line after implementing searchEmployee()					
			//if (0)									// comment out this line after implementing searchEmployee()
			{
				printf("\nEmployee name does not exist or the list is empty! \n\n");
			} else {
				printf("\nEmployee name exists on the list! \n\n");
			}
			break;

		// remove employee
		case 'r':
			printf("\nPlease enter employee's name: ");
			fgets(employeeNameInput, sizeof(employeeNameInput), stdin);
			employeeNameInput[strlen(employeeNameInput) - 1] = '\0'; // discard the trailing '\n' char

			if (searchEmployee(employeeNameInput) == NULL)	// un-comment this line after implementing searchEmployee()					
			//if (0)									// comment out this line after implementing searchEmployee()
			{
				printf("\nEmployee name does not exist or the list is empty! \n\n");
			} else {
				removeEmployee(employeeNameInput);
				printf("\nEmployee successfully removed from the list! \n\n");
			}
			break;

		// add supervisor
		case 'c':
			printf("\nPlease enter employee's name: ");
			fgets(employeeNameInput, sizeof(employeeNameInput), stdin);
			employeeNameInput[strlen(employeeNameInput) - 1] = '\0'; // discard the trailing '\n' char

			if (searchEmployee(employeeNameInput) == NULL)	// un-comment this line after implementing searchEmployee()					
			//if (0)										// comment out this line after implementing searchEmployee()
			{
				printf("\nEmployee name does not exist or the list is empty! \n\n");
			} else {
				printf("\nPlease enter supervisor's name: ");
				fgets(supervisorNameInput, sizeof(supervisorNameInput), stdin);
				supervisorNameInput[strlen(supervisorNameInput) - 1] = '\0'; // discard the trailing '\n' char

				addSupervisor(employeeNameInput, supervisorNameInput);
				printf("\nSupervisor added! \n\n");
			}
			break;

		// list supervisor's employees
		case 'l':
			displayEmployeeSupervisorList(list);
			break;

		// quit
		case 'q':
			break;

		default:
			printf("%c is invalid input!\n", c);
	}
}

// HW7 Q1: addEmployee (20 points)
// This function is used to insert a new employee in the linked list. 
// You must insert the new employee to the head of linked list 'list'.
// You need NOT check if the employee already exists in the list because that is taken care by searchEmployee() called in executeAction(). Look at how this function is used in executeAction().
// Don't bother to check how to implement searchEmployee() while implementing this function. Simply assume that employee does not exist in the list while implementing this function.
// NOTE: The function needs to add the employee to the head of the list.
// NOTE: This function does not add supervisors to the employee info. There is another function addSupervisor() in HW8 for that.
// Hint: In this question, no supervisors means NULL supervisors.
void addEmployee(char* employeeNameInput, unsigned int roomNumInput) {
	// create temporary employee and fill fields with given vals from params
	struct employee* tempEmployee = (struct employee*)malloc(sizeof(struct employee));
	strcpy(tempEmployee->name, employeeNameInput);
	tempEmployee->roomNumber = roomNumInput;

	// create tempList and add employee to head of list
	struct employeeNode* tempList = (struct employeeNode*)malloc(sizeof(struct employeeNode));
	tempList->employee = tempEmployee;
	tempList->next = list;

	// set new list as main list
	list = tempList;
}

// HW7 Q2: displayEmployeeList (15 points)
// This function displays the employee details (struct elements) of each employee.
// Parse through the linked list 'list' and print the employee details ( name and room number) one after the other. See expected output screenshots in homework question file.
// You should not display supervisor names (because they are not added in HW7).
// You MUST use recursion in the function to get full points. Notice that 'list' is passed to the function argument. Use recursion to keep calling this function till end of list.
void displayEmployeeList(struct employeeNode* tempList) {
	// return if the list is empty to prevent errors
	if (tempList == NULL) {
		return;
	}

	// print info and break to new lines
	printf("\nEmployee Name: %s\n", tempList->employee->name);
	printf("Employee Room Number: %i\n", tempList->employee->roomNumber);

	// statement to end recursion if list has reached tail
	if (tempList->next != NULL) {
		displayEmployeeList(tempList->next);
	}
}

// HW7 Q3: searchEmployee (15 points)
// This function searches the 'list' to check if the given employee exists in the list. Search by employee name.
// If it exists then return that 'employee' node of the list. Notice the return type of this function.
// If the employee does not exist in the list, then return NULL.
// NOTE: After implementing this fucntion, go to executeAction() to comment and un-comment the lines mentioned there which use searchEmployee()
//       in case 'a', case 'r', case 'l' (total 3 places)
struct employee* searchEmployee(char* employeeNameInput) {
	// work on a copy of 'list'
	struct employeeNode* tempList = list;

	// iterate through all employees
	while (tempList != NULL) {
		// check for employee name to match input, then return it
		if (strcmp(tempList->employee->name, employeeNameInput) == 0) {
			return tempList->employee;
		}
		// increment list to next node
		tempList = tempList->next;
	}

	// return null if not found
	return NULL;
}



// HW8 Q1: addSupervisor (15 points)
// This function adds supervisor's name to a employee node.
// Parse the list to locate the employee and add the supervisor to that employee's 'supervisors' linked list. No need to check if the employee name exists on the list. That is done in executeAction().
// If the 'supervisors' list is empty, then add the supervisor. If the employee has existing supervisors, then you may add the new supervisor to the head or the tail of the 'supervisors' list.
// You can assume that the same supervisor name does not exist. So no need to check for existing supervisor names, like we do when we add new employee.
// NOTE: Make note of whether you add the supervisor to the head or tail of 'supervisors' list. 
//       (Sample solution has supervisor added to the tail of 'supervisors' list. You are free to add new supervisor to head or tail of 'supervisors' list.)
void addSupervisor(char* employeeNameInput, char* supervisorNameInput) {
	// work on a copy of 'list'
	struct employeeNode* tempList = list;

	// iterate through all employees
	while (tempList != NULL) {
		// compare employee to inputted name
		if (strcmp(tempList->employee->name, employeeNameInput) == 0) {
			// create supervisor struct and copy details
			struct supervisor* tempSupervisors = (struct supervisor*)malloc(sizeof(struct supervisor));
			strcpy(tempSupervisors->name, supervisorNameInput);

			// check if there are existing supervisors, add them after new head if there are
			if (tempList->employee->supervisors == NULL) {
				tempSupervisors->next = NULL;
			} else {
				tempSupervisors->next = tempList->employee->supervisors;
			}

			// add new supervisors list to employee
			tempList->employee->supervisors = tempSupervisors;

			return;
		}
		// increment to next node in linked list
		tempList = tempList->next;
	}

	// set main list to temp list
	list = tempList;
}

// HW8 Q2: displayEmployeeSupervisorList (15 points)
// This function prompts the user to enter a supervisor name. This function then searches for employees with this supervisor.
// Parse through the linked list passed as parameter and print the matching employee details ( name and room number) one after the other. See expected output screenshots in homework question file.
// HINT: Use inputs gathered in executeAction() as a model for getting the supervisor name input.
// NOTE: You may re-use some HW7 Q2 displayEmployeeList(list) code here.
void displayEmployeeSupervisorList(struct employeeNode* tempList) {
	// return if the the list is empty
	if (tempList == NULL) {
		return;
	}

	// store input of desired supervisor
	char supervisorNameInput[MAX_NAME];
	printf("\nPlease enter supervisor's name: ");
	fgets(supervisorNameInput, sizeof(supervisorNameInput), stdin);
	supervisorNameInput[strlen(supervisorNameInput) - 1] = '\0'; // discard the trailing '\n' char

	// iterate through all employees in linked list
	while (tempList != NULL) {
		// create temp supervisors list
		struct supervisor* tempSupervisorsList = tempList->employee->supervisors;

		// iterate through all supervisors
		while (tempSupervisorsList != NULL) {
			// check if supervisor's name matches input, display if so
			if (strcmp(tempSupervisorsList->name, supervisorNameInput) == 0) {
				printf("\nEmployee Name: %s\n", tempList->employee->name);
				printf("Employee Room Number: %i\n", tempList->employee->roomNumber);
			}
			// increment supervisor list
			tempSupervisorsList = tempSupervisorsList->next;
		}

		// increment employee list
		tempList = tempList->next;
	}
}

// HW8 Q3: removeEmployee (20 points)
// This function removes an employee from the list.
// Parse the list to locate the employee and delete that 'employee' node.
// You need not check if the employee exists because that is done in executeAction()
// removeEmployee() is supposed to remove employee details like name and room number.
// The function will remove supervisors of the employee too.
// When the employee is located in the 'list', after removing the employee name and room number, parse the 'supervisors' list of that employee
// and remove the supervisors.
void removeEmployee(char* employeeNameInput) {
	// return if list is empty
	if (list == NULL) {
		return;
	}

	// check if the one we want is currently the head, remove if so
	if (strcmp(list->employee->name, employeeNameInput) == 0) {
		list = list->next;
		return;
	}

	// work on a copy of 'list'
	struct employeeNode* tempListCur = list;
	struct employeeNode* tempListPrev = list;

	// iterate through all elements while their is a proceeding elements
	while (tempListCur != NULL && tempListCur->next != NULL) {
		// check for desired element and skip to the one after it to fully remove it
		if (strcmp(tempListCur->next->employee->name, employeeNameInput) == 0) {
			tempListCur->next = tempListCur->next->next != NULL ? tempListCur->next->next : NULL;
		}

		// inprement to next element
		tempListCur = tempListCur->next;
	}

	// set list to tempList
	list = tempListPrev;
}
