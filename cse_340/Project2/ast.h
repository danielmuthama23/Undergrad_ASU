#include <string>
#include <vector>
#include <iostream>
#include "execute.h"

using namespace std;

enum ASTtype {
    t_ARRAY = 0, t_SCALAR, t_ERROR, t_ARRAY_DECL
};

enum Operator {
    o_MINUS = 0,
    o_PLUS,
    o_MULT,
    o_DIV,
    o_LPAREN,
    o_EXPR,
    o_DOT,
    o_NOOP
};

typedef struct ASTNode {
    ASTNode* right;
    ASTNode* left;
    ASTtype type;
    Operator oper;
    string value;
    string unchanged_val;
    bool w, n;

    instNode* instN;

    // overloaded methods
    ASTNode(){};
    ASTNode(ASTNode *r, ASTNode *l, string val) { right = r; left = l; value = val; };
    ASTNode(ASTNode *r, ASTNode *l, ASTtype t, Operator o, string v, string ra) {
        right = r;
        left = l;
        type = t;
        oper = o;
        value = v;
        unchanged_val = ra;
        w = false;
        n = false;
    };
} ASTNode;

class ASTree {
    public:
    ASTNode* root;
    int line_no;

    int tree_height(ASTNode*);
    void print_tree(ASTNode*, int);

    // constructors
    ASTree() {};
    ASTree(ASTNode* r, int l) { root = r; line_no = l; };
};
