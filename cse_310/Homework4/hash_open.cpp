// CSE310 Summer 2022 (C) - Homework #4 Part 2b
// Tyler Fichiera - 1218959911
// 06/22/2022

#include <iostream>
#include <cstdlib>

using namespace std;

#define SIZE_M 753

class HashOpen {
    public:
        struct Node {
            string owner_name;
            int account_number; // [100001, 999999]
            double account_balance;
        };
        Node* table[SIZE_M];
        HashOpen() {
            // make all indexes null to begin with
            for (int i = 0; i < SIZE_M; i++) table[i] = NULL;
        }
        // insert the bank account record x to T
        void INSERT_Account(Node* T[], Node* x);
        // search the account number k in the hash table and returns the corresponding record
        Node* SEARCH_Account(Node* T[], int k);
        // get hash using h(k) = k mod m
        int hashFunction(int k, int i) { return ((k % SIZE_M) + i) % SIZE_M; }
};

void HashOpen::INSERT_Account(Node* T[], Node* x) {    
    int i = 0;
    while (i != SIZE_M){
        int j = hashFunction(x->account_number, i);
        if (T[j] == NULL) {
            T[j] = x;
            return;
        }
        i++;
    }
    throw string("hash table overflow");
}

HashOpen::Node* HashOpen::SEARCH_Account(Node* T[], int k) {
    int i = 0;
    int j = hashFunction(k, i);
    while (T[j] != NULL && i != SIZE_M) {
        if (T[j]->account_number == k)
            return T[j];
        i++;
        j = hashFunction(k, i);
    };
    return NULL;
}

int main() {
    HashOpen hash;
    int choice, account_number;
    string owner_name;
    double account_balance;
	while (true) {
		cout << endl << endl;
		cout << "Sun Devil Banking (Hash Open)" << endl;
		cout << "----------------------------- " << endl;
		cout << "1. Insert Account" << endl;
		cout << "2. Search for Account" << endl;
		cout << "3. Display Table" << endl;
		cout << "4. Exit" << endl;
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

                HashOpen::Node* record = new HashOpen::Node();
                record->owner_name = owner_name;
                record->account_number = account_number;
                record->account_balance = account_balance;

                try {
                    hash.INSERT_Account(hash.table, record);
                } catch (string e) {
                    // catch and print error
                    cout << endl << e << endl;
                }

                break;
            }
            case 2: {
                cout << endl << "Enter account number (int val in range [100001, 999999]): ";
                cin >> account_number;

                HashOpen::Node* record = hash.SEARCH_Account(hash.table, account_number);
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
            case 3: {
                cout << endl;
                cout << "     Hash Table     " << endl;
                cout << "--------------------" << endl;
                for (int i = 0; i < SIZE_M; i++) {
                    HashOpen::Node* node = hash.table[i];
                    if (node != NULL) {
                        cout << "Index " << i << ": ";
                        cout << node->owner_name << "\t\t" << node->account_number << "\t\t" << node->account_balance << endl;
                    }
                }
                break;
            }
            case 4: {
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
