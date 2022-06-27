// CSE310 Summer 2022 (C) - Homework #4 Part 2a
// Tyler Fichiera - 1218959911
// 06/22/2022

#include <iostream>
#include <cstdlib>

using namespace std;

#define SIZE_M 753

class HashChain {
    public:
        struct Node {
            string owner_name;
            int account_number; // [100001, 999999]
            double account_balance;
            struct Node* next; // pointer to next node
        };
        Node* table[SIZE_M];
        HashChain() {
            // make all indexes null to begin with
            for (int i = 0; i < SIZE_M; i++) table[i] = NULL;
        }
        // insert the bank account record x to T
        void INSERT_Account(Node* T[], Node* x);
        // delete the bank account record from the table where k is the account number
        bool DELETE_Account(Node* T[], int k);
        // search the account number k in the hash table and returns the corresponding record
        Node* SEARCH_Account(Node* T[], int k);
        // get hash using h(k) = k mod m
        int hashFunction(int k) { return k % SIZE_M; }
};

void HashChain::INSERT_Account(Node* T[], Node* x) {
    int hash = hashFunction(x->account_number);
    HashChain::Node* list = T[hash];
    if (list == NULL) {
        T[hash] = x;
    } else {
        while (list->next != NULL) {
			list = list->next;
		}
	    // add new record as last element in linked list
		list->next = x;
    }
}

bool HashChain::DELETE_Account(Node* T[], int k) {
    int hash = hashFunction(k);
    HashChain::Node* list = T[hash];

    // return if list is empty
	if (list == NULL) {
		return false;
	}

	// check if the one we want is currently the head, remove if so
	if (list->account_number == k) {
		T[hash] = list->next;
		return true;
	}

	// work on a copy of `list`
	HashChain::Node* tempListCur = list;
	HashChain::Node* tempListPrev = list;

    bool isDeleted = false;

	// iterate through all elements while their is a proceeding elements
	while (tempListCur != NULL && tempListCur->next != NULL) {
		// check for desired element and skip to the one after it to fully remove it
		if (tempListCur->next->account_number == k) {
			tempListCur->next = tempListCur->next->next != NULL ? tempListCur->next->next : NULL;
            isDeleted = true;
		}

		// inprement to next element
		tempListCur = tempListCur->next;
	}

	// set list to tempList
	T[hash] = tempListPrev;

    return isDeleted;
}

HashChain::Node* HashChain::SEARCH_Account(Node* T[], int k) {
    int hash = hashFunction(k);
    HashChain::Node* list = T[hash];
    while (list != NULL) {
        if (list->account_number == k)
            return list;
        list = list->next;
    }
    return NULL;
}

int main() {
    HashChain hash;
    int choice, account_number;
    string owner_name;
    double account_balance;
	while (true) {
		cout << endl << endl;
		cout << "Sun Devil Banking (Hash Chain)" << endl;
		cout << "----------------------------- " << endl;
		cout << "1. Insert Account" << endl;
		cout << "2. Delete Account" << endl;
		cout << "3. Search for Account" << endl;
		cout << "4. Display Table" << endl;
		cout << "5. Exit" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
        cin.ignore();
		switch (choice) {
            case 1: {
                cout << endl << "Enter owner's name (string val): ";
                getline(cin, owner_name);
                cout << "Enter account number (int val in range [100001, 999999]): ";
                cin >> account_number;
                cout << "Enter account balance (double val): ";
                cin >> account_balance;

                HashChain::Node* record = new HashChain::Node();
                record->owner_name = owner_name;
                record->account_number = account_number;
                record->account_balance = account_balance;
                record->next = NULL;

                hash.INSERT_Account(hash.table, record);

                break;
            }
            case 2: {
                cout << endl << "Enter account number (int val in range [100001, 999999]): ";
                cin >> account_number;

                bool isDeleted = hash.DELETE_Account(hash.table, account_number);
                cout << endl;
                if (isDeleted)
                    cout << "Account with number " << account_number << " deleted!";
                else
                    cout << "No account with number " << account_number << " found!";

                break;
            }
            case 3: {
                cout << endl << "Enter account number (int val in range [100001, 999999]): ";
                cin >> account_number;

                HashChain::Node* record = hash.SEARCH_Account(hash.table, account_number);
                cout << endl;
                if (record != NULL) {
                    cout << "Account: " << account_number << endl;
                    cout << "Owner: " << record->owner_name << endl;
                    cout << "Balance: " << record->account_balance;
                } else {
                    cout << "No account with number " << account_number << " found!";
                }

                break;
            }
            case 4: {
                cout << endl;
                cout << "     Hash Table     " << endl;
                cout << "--------------------" << endl;
                for (int i = 0; i < SIZE_M; i++) {
                    HashChain::Node* list = hash.table[i];
                    if (list != NULL) {
                        cout << "Index " << i << ": ";
                        while (list != NULL) {
                            cout << list->owner_name << " " << list->account_number << " " << list->account_balance; 
                            list = list->next;
                            if (list != NULL) cout << ", ";
                        }
                        cout << endl;
                    }
                }
                break;
            }
            case 5: {
                return 0;
                break;
            }
            default: {
                cout << "Invalid choice";
                break;
            }
		}
	}
    return 0;
}
