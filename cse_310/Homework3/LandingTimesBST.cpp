// CSE310 Summer 2022 (C) - Homework #3 Question 2
// Tyler Fichiera - 1218959911
// 06/12/2022

#include <iostream>
#include <cstdlib>

using namespace std;

class LandingTimesBST {
    public:
        int K_VALUE;
        class node {
            public:
                node* parent;
                node* left;
                node* right;
                int time;
                string flight;
        };
        node* root;
        LandingTimesBST() {
            root = NULL;
        }
        node* TREE_INSERT(int, string);
        void INORDER_TREE_WALK(node*);
        node* TREE_SEARCH(node*, int);
        node* TREE_MINIMUM(node*);
        node* TREE_MAXIMUM(node*);
        node* TREE_SUCCESSOR(node*);
        node* TREE_PREDECESSOR(node*);
        void TRANSPLANT(node*, node*);
        void TREE_DELETE(node*);
};

LandingTimesBST::node* LandingTimesBST::TREE_INSERT(int d, string f) {
	// This implements the algorithm in page 261 of the textbook
	node* z = new node();
	z->time = d;
    z->flight = f;
	z->left = NULL;
	z->right = NULL;

	node* y = NULL;
	node* x = root;
    node* parent = NULL;

	while (x != NULL) {
		y = x;
		if (z->time < x->time)
			x = x->left;
		else
			x = x->right;
	}

    parent = y;
    z->parent = y;
	if (y == NULL)
		root = z;
	else if (z->time < y->time)
		y->left = z;
	else
		y->right = z;

    return z;
}

// page 288
void LandingTimesBST::INORDER_TREE_WALK(node* x) {
	if (x != NULL) {
		if (x->left) INORDER_TREE_WALK(x->left);
		cout << " " << x->flight << " - " << x->time << " minute(s)" << endl;
		if (x->right) INORDER_TREE_WALK(x->right);
	}
}

// page 290
LandingTimesBST::node* LandingTimesBST::TREE_SEARCH(node* x, int k) {
    if (x == NULL || x->time == k)
        return x;
    if (k < x->time)
        return TREE_SEARCH(x->left, k);
    return TREE_SEARCH(x->right, k);
}

// page 291
LandingTimesBST::node* LandingTimesBST::TREE_MINIMUM(node* x) {
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

// page 291
LandingTimesBST::node* LandingTimesBST::TREE_MAXIMUM(node* x) {
    while (x->right != NULL) {
        x = x->right;
    }
    return x;
}

// page 292
LandingTimesBST::node* LandingTimesBST::TREE_SUCCESSOR(node* x) {
    if (x->right != NULL) {
        return TREE_MINIMUM(x->right);
    }
    node* y = x->parent;
    while (y != NULL && x == y->right) {
        x = y;
        y = y->parent;
    }
    return y;
}

LandingTimesBST::node* LandingTimesBST::TREE_PREDECESSOR(node* x) {
    if (x->right != NULL) {
        return TREE_MAXIMUM(x->right);
    }
    node* y = x->parent;
    while (y != NULL && x == y->left) {
        x = y;
        y = y->parent;
    }
    return y;
}

// page 296
void LandingTimesBST::TRANSPLANT(node* u, node* v) {
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
void LandingTimesBST::TREE_DELETE(node* z) {
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
	LandingTimesBST ltBst;
	int choice, time;
    string flight;

    cout << endl << "First, please enter the K time gap (int value) : ";
    cin >> ltBst.K_VALUE;

	while (true) {
		cout << endl << endl;
		cout << "       Landing Times BST       " << endl;
		cout << " ----------------------------- " << endl;
		cout << " 1. Request Landing" << endl;
		cout << " 2. Withdraw Landing Request" << endl;
		cout << " 3. List Landing Flights & Times" << endl;
		cout << " 4. Exit" << endl;
		cout << " Enter your choice : ";
		cin >> choice;
        cin.ignore();
		switch (choice) {
            case 1: {
                cout << endl << " Enter name of plane (string value) : ";
                getline(cin, flight);
                cout << " Enter landing time (int value) : ";
                cin >> time;
                cin.ignore();

                // temp add node to bst to find successor and predecessor
                LandingTimesBST::node* node = ltBst.TREE_INSERT(time, flight);

                LandingTimesBST::node* suc = ltBst.TREE_SUCCESSOR(node);
                LandingTimesBST::node* pre = ltBst.TREE_PREDECESSOR(node);

                // check if the landing time request satisfies based on K_VALUE
                // first check if suc or pre is null in case you're adding
                // the current smallest or largest value
                // remove the node if it does not satisfy
                if (
                    (suc == NULL || suc->time - time >= ltBst.K_VALUE) &&
                    (pre == NULL || time - pre->time >= ltBst.K_VALUE)
                ) {
                    cout << endl << " Success! Flight " << flight << " with time " << time << " add to queue";
                } else {
                    cout << endl << " Error! Flight " << flight << " with time " << time << " not added to queue";
                    ltBst.TREE_DELETE(node);
                }

                break;
            }
            case 2: {
                cout << endl << " Enter time of the flight (int value) you want to withdraw : ";
                cin >> time;
                cin.ignore();

                LandingTimesBST::node* node = ltBst.TREE_SEARCH(ltBst.root, time);
                if (node != NULL) {
                    ltBst.TREE_DELETE(node);
                    cout << endl << " FLight with time " << time << " removed";
                } else {
                    cout << endl << " No flight with time " << time << " found";
                }

                break;
            }
            case 3: {
                cout << endl;
                cout << " En Route Flights " << endl;
                cout << " -------------------" << endl;
                ltBst.INORDER_TREE_WALK(ltBst.root);
                break;
            }
            case 4: {
                return 0;
                break;
            }
            default: {
                cout << "Invalid choice";
            }
		}
	}
}
