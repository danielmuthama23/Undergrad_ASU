#include "ast.h"

using namespace std;

// get height by getting the maximum depth from the root to a leaf
int ASTree::tree_height(ASTNode* n) {
    if (n == NULL) return 0;

    // find height of subtrees
    int left_height = tree_height(n->left);
    int right_height = tree_height(n->right);

    // return the max of the two
    // add +1 for real height including root
    return max(left_height, right_height) + 1;
}

// print tree in a level order traversal
void ASTree::print_tree(ASTNode* n, int level) {
    if (n == NULL) return;
    if (level == 1)
        cout << n->value << " ";
    else if (level > 1) {
        print_tree(n->left, level - 1);
        print_tree(n->right, level - 1);
    }
}