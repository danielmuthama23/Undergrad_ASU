// CSE310 Summer 2022 (C) - Homework #3 Question 1
// Tyler Fichiera - 1218959911
// 06/12/2022

#include <iostream>
#include <cstdlib>

using namespace std;

class BinarySearchTree {
    public:
        class node {
            public:
                node* parent;
                node* left;
                node* right;
                int key;
        };
        node* root;
        BinarySearchTree() {
            root = NULL;
        }
        bool isEmpty() const { return root == NULL; }
        void TREE_INSERT(int);
        void INORDER_TREE_WALK(node*);
        void PREORDER_TREE_WALK(node*);
        void POSTORDER_TREE_WALK(node*);
        node* TREE_SEARCH(node*, int k);
        node* TREE_MINIMUM(node*);
        node* TREE_MAXIMUM(node*);
        // void REMOVE_MAX();
        node* TREE_SUCCESSOR(node*);
        void TRANSPLANT(node*, node*);
        void TREE_DELETE(node*);
};

// 294
void BinarySearchTree::TREE_INSERT(int d) {
	// This implements the algorithm in page 261 of the textbook
	node* z = new node();
	z->key = d;
	z->left = NULL;
	z->right = NULL;

	node* y = NULL;
	node* x = root;
    node* parent = NULL;

	while (x != NULL) {
		y = x;
		if (z->key < x->key)
			x = x->left;
		else
			x = x->right;
	}

    parent = y;
    z->parent = y;
	if (y == NULL)
		root = z;
	else if (z->key < y->key)
		y->left = z;
	else
		y->right = z;	
}

// page 288
void BinarySearchTree::INORDER_TREE_WALK(node* x) {
	if (x != NULL) {
		if (x->left) INORDER_TREE_WALK(x->left);
		cout << " " << x->key << " ";
		if (x->right) INORDER_TREE_WALK(x->right);
	}
}

void BinarySearchTree::PREORDER_TREE_WALK(node* x) {
    if (x != NULL) {
        cout << " " << x->key << " ";
        if (x->left) PREORDER_TREE_WALK(x->left);
        if (x->right) PREORDER_TREE_WALK(x->right);
    }
}

void BinarySearchTree::POSTORDER_TREE_WALK(node* x) {
    if (x != NULL) {
        if (x->left) POSTORDER_TREE_WALK(x->left);
        if (x->right) POSTORDER_TREE_WALK(x->right);
        cout << " " << x->key << " ";
    }
}

// page 290
BinarySearchTree::node* BinarySearchTree::TREE_SEARCH(node* x, int k) {
    if (x == NULL || x->key == k)
        return x;
    if (k < x->key)
        return TREE_SEARCH(x->left, k);
    return TREE_SEARCH(x->right, k);
}

// page 291
BinarySearchTree::node* BinarySearchTree::TREE_MINIMUM(node* x) {
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

// page 291
BinarySearchTree::node* BinarySearchTree::TREE_MAXIMUM(node* x) {
    while (x->right != NULL) {
        x = x->right;
    }
    return x;
}

// page 292
BinarySearchTree::node* BinarySearchTree::TREE_SUCCESSOR(node* x) {
    if (x->right != NULL) {
        cout << "here 1" << endl;
        return TREE_MINIMUM(x->right);
    }
    node* y = x->parent;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

// page 296
void BinarySearchTree::TRANSPLANT(node* u, node* v) {
    if (u->parent == NULL)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;
    if (v != NULL) {
        v->parent = u->parent;
    }
}

// page 298
void BinarySearchTree::TREE_DELETE(node* z) {
    if (z->left == NULL)
        TRANSPLANT(z, z->right);
    else if (z->right == NULL)
        TRANSPLANT(z, z->left);
    else {
        node* y = TREE_MINIMUM(z->right);
        if (y->parent != z) {
            TRANSPLANT(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        TRANSPLANT(z, y);
        y->left = z->left;
        y->left->parent = y;
    }
}

int main() {
	BinarySearchTree bst;
	int choice, key;
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
