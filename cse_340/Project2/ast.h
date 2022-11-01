#include <string>
#include <vector>
#include <iostream>
#include "execute.h"

using namespace std;

enum ASTtype {
    t_ARRAY = 0, t_SCALAR, t_ERROR, t_ARRAY_DECL
};

// NAME
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

typedef struct ASTNode
{
    ASTNode* right;
    ASTNode* left;
    ASTtype type;
    Operator oper;
    string value;
    string raw_value; // NAME \/
    bool wrapped;
    bool is_num;

    instNode* instN;

    // LOGIC
    ASTNode(){};
    ASTNode(ASTNode *r, ASTNode *l, string val)
    {
        right = r;
        left = l;
        value = val;
    };
    ASTNode(ASTNode *r, ASTNode *l, ASTtype t, Operator o, string v, string raw)
    {
        right = r;
        left = l;
        type = t;
        oper = o;
        value = v;
        raw_value = raw;
        wrapped = false;
        is_num = false;
    };
} ASTNode;

class ASTree
{
    public:
    ASTNode* root;
    int line_no;

    void init(ASTNode*, ASTNode*, int);
    int tree_height(ASTNode*);
    void print_tree(ASTNode*, int);

    // constructors
    ASTree() {};
    ASTree(ASTNode* r, int l) { root = r; line_no = l; };
};
