// CSE310 Summer 2022 (C) - Homework #3 Question 2
// Tyler Fichiera - 1218959911
// 06/12/2022

#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
	// BinarySearchTree bst;
	int choice, time, flight;
	while (true) {
		cout << endl << endl;
		cout << " Binary Search Tree Example " << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. Insert a node" << endl;
		cout << " 2. Pre-Order Traversal" << endl;
		cout << " 3. Post-Order Traversal" << endl;
		cout << " 4. In-Order Traversal" << endl;
		cout << " 5. Find Max" << endl;
		cout << " 6. Remove Max" << endl;
		cout << " 7. Successor" << endl;
		cout << " 8. Delete a node" << endl;
		cout << " 9. Exit" << endl;
		cout << " Enter your choice : ";
		cin >> choice;
		switch (choice) {
            case 1: {
                cout << endl << " Enter key (int value) to be inserted : ";
                cin >> key;
                bst.TREE_INSERT(key);
                break;
            }
            case 2: {
                cout <<  endl << " Pre-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.PREORDER_TREE_WALK(bst.root);
                break;
            }
            case 3: {
                cout << endl <<  " Post-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.POSTORDER_TREE_WALK(bst.root);
                break;
            }
            case 4: {
                cout << endl <<  " In-Order Traversal " << endl;
                cout << " -------------------" << endl;
                bst.INORDER_TREE_WALK(bst.root);
                break;
            }
            case 5: {
                if (bst.root != NULL) {
                    BinarySearchTree::node* max = bst.TREE_MAXIMUM(bst.root);
                    cout << endl << " Max element : " << max->key;
                } else {
                    cout << endl << " No max element found";
                }
                break;
            }
            case 6: {
                if (bst.root != NULL) {
                    BinarySearchTree::node* max = bst.TREE_MAXIMUM(bst.root);
                    bst.TREE_DELETE(max);
                    cout << endl << " Max element " << max->key << " removed";
                } else {
                    cout << endl << " No max element found";
                }
                break;
            }
            case 7: {
                cout << endl << " Enter key (int value) to find successor : ";
                cin >> key;
                BinarySearchTree::node* node = bst.TREE_SEARCH(bst.root, key);
                if (node != NULL) {
                    BinarySearchTree::node* successor = bst.TREE_SUCCESSOR(node);
                    if (successor != NULL)
                        cout << endl << " Tree successor : " << successor->key;
                    else
                        cout << endl << " Element with key " << key << " has null parent so it has no successor";
                } else {
                    cout << endl << " No element with key " << key << " found";
                }
                break;
            }
            case 8: {
                cout << endl << " Enter key (int value) to be deleted : ";
                cin >> key;
                BinarySearchTree::node* node = bst.TREE_SEARCH(bst.root, key);
                if (node != NULL) {
                    bst.TREE_DELETE(node);
                    cout << endl << " Element with key " << key << " removed";
                } else {
                    cout << endl << " No element with key " << key << " found";
                }
                break;
            }
            case 9: {
                system("pause");
                return 0;
                break;
            }
            default: {
                cout << "Invalid choice";
            }
		}
	}
}
