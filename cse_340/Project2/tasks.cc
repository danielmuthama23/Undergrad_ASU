#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "lexer.h"
#include "execute.h"
#include "tasks.h"

using namespace std;

/* --- STACK IMPLEMENTATION --- */
StackNode PPStack::terminalTop() { return stack.back(); }

StackNode PPStack::terminalPeek() {
    vector<StackNode> tmp = stack;
    StackNode n = tmp.back();
    // ignores non-terminals
    if (n.type == EXPR) {
        tmp.pop_back();
        n = tmp.back();
    }
    return n;
}

StackNode PPStack::pop() {
    StackNode n = stack.back();
    stack.pop_back();
    return n;
}

void PPStack::push(StackNode& n) { stack.push_back(n); }

void PPStack::init() {
    StackNode n;
    n.type = TERM;
    n.term.lexeme = "$"; // contains $ initially
    n.term.line_no = -1;
    n.term.token_type = END_OF_FILE;
    push(n);
}
/* --- STACK IMPLEMENTATION --- */

// program → decl-section block
void Parser::parse_program() {
    stack.init();
    parse_decl_section();
    parse_block();
    expect(END_OF_FILE);
}

// decl-section → scalar-decl-section array-decl-section
void Parser::parse_decl_section() {
    curr_scalars = parse_scalar_decl_section();
    for (string s : curr_scalars) {
        Location l = Location(first_i, s, l_SCALAR);
        location_list.push_back(l);
        first_i++;
    }

    curr_arrays = parse_array_decl_section();
    for (string a : curr_arrays) {
        Location l = Location(first_i, a, l_SCALAR);
        location_list.push_back(l);
        first_i++;
    }

    second_i = first_i;
}

// scalar-decl-section → SCALAR id-list
vector<string> Parser::parse_scalar_decl_section() {
    expect(SCALAR);
    return parse_id_list();
}

// array-decl-section → ARRAY id-list
vector<string> Parser::parse_array_decl_section() {
    expect(ARRAY);
    return parse_id_list();
}

// id-list → ID
// id-list → ID id-list
vector<string> Parser::parse_id_list() {
    vector<string> parsed_ids;
    string id = expect(ID).lexeme;
    TokenType t = peek(1);
    if (t == ID) {
        parsed_ids = parse_id_list();
        parsed_ids.push_back(id);
    } else if (t == ARRAY || t == LBRACE) {
        parsed_ids.push_back(id);
    } else {
        syntax_error();
    }
    return parsed_ids;
}

// block → LBRACE stmt-list RBRACE
void Parser::parse_block() {
    expect(LBRACE);
    parse_stmt_list();
    expect(RBRACE);
}

// stmt-list → stmt
// stmt-list → stmt stmt-list
instNode* Parser::parse_stmt_list() {
    instNode* i = parse_stmt();
    TokenType t = peek(1);

    if (t == ID || t == OUTPUT) { // stmt-list → stmt
        append_to_end(i, parse_stmt_list());
        return i;
    } else if (t == RBRACE) // stmt-list → stmt stmt-list
        return i;
    else
        syntax_error();
}

// stmt → assign-stmt
// stmt → output-stmt
instNode* Parser::parse_stmt() {
    TokenType t = peek(1);
    if (t == ID)
        return parse_assign_stmt(); // stmt → assign-stmt
    else if (t == OUTPUT)
        return parse_output_stmt(); // stmt → output-stmt
    else
        syntax_error();
}

// assign-stmt → variable-access EQUAL expr SEMICOLON
instNode* Parser::parse_assign_stmt() {
    ASTNode* left = parse_variable_access(); // variable-access
    Token eqTok = expect(EQUAL); // EQUAL
    ASTNode* right = parse_expr(); // expr
    Token semTok = expect(SEMICOLON); // SEMICOLON

    ASTNode* equal_node = new ASTNode(right, left, "=");
    astrees.push_back(ASTree(equal_node, semTok.line_no));

    bool has_expr_er = has_expr_type_err(right);
    bool has_acc_er = has_access_type_err(left);

    if (has_expr_er)
        type_errors.push_back(eqTok.line_no);
    else if (has_acc_er)
        type_errors.push_back(eqTok.line_no);

    bool has_assign_er = has_assign_type_err(new ASTNode(right, left, "="));
    if (has_assign_er)
        assign_errors.push_back(eqTok.line_no);

    // get to the end of both nodes for reverse search
    instNode* right_node = right->instN;
    while (right_node->next != NULL)
        right_node = right_node->next;

    instNode* left_node = left->instN;
    while (left_node->next != NULL)
        left_node = left_node->next;

    instNode* i = new instNode();
    i->iType = ASSIGN_INST;
    i->lhs = left_node->lhs;
    i->op1 = right_node->lhs;
    i->op1at = right_node->lhsat;
    i->oper = OP_NOOP;
    if (left_node->lhs > second_i)
        i->lhsat = INDIRECT;
    else
        i->lhsat = DIRECT;

    // check which nodes can be appended
    if (left->instN->op1 > -1 && right->instN->op1 > -1) {
        append_to_end(left->instN, right->instN);
        return append_to_end(left->instN, i);
    }

    if (right->instN->op1 < 0 && left->instN->op1 > -1)
        return append_to_end(left->instN, i);

    if (right->instN->op1 > -1 && left->instN->op1 < 0)
        return append_to_end(right->instN, i);

    return i;
}

// output-stmt → OUTPUT variable-access SEMICOLON
instNode* Parser::parse_output_stmt() {
    // logic very similar to parse_assign_stmt
    Token outTok = expect(OUTPUT); // OUTPUT
    ASTNode* var_acc = parse_variable_access(); // variable-access
    expect(SEMICOLON); // SEMICOLON

    // check output for type errs
    if (has_access_type_err(var_acc))
        type_errors.push_back(outTok.line_no);

    instNode* n = var_acc->instN;
    while (n->next != NULL)
        n = n->next;

    instNode* i = new instNode();
    i->iType = OUTPUT_INST;
    i->op1 = n->lhs;
    if (n->lhs > second_i)
        i->op1at = INDIRECT;
    else
        i->op1at = DIRECT;

    if (var_acc->instN->op1 > -1)
        return append_to_end(var_acc->instN, i);

    return i;
}

// variable-access → ID
// variable-access → ID LBRAC expr RBRAC
// variable-access → ID LBRAC DOT RBRAC
ASTNode* Parser::parse_variable_access() {
    Token exTok = expect(ID); // ID
    vector<StackNode> tmp = { StackNode(TERM, NULL, exTok) };
    StackNode e = reduce(tmp, 7); // 7 = primary
    TokenType t = peek(1);
    if (t == LBRAC) { // LBRAC
        stack.push(e);
        return parse_expr();
    } else if (t == EQUAL || t == SEMICOLON)
        return e.expr;
    syntax_error();
}

// RULES and their keys:
// 0: expr → expr MINUS expr
// 1: expr → expr PLUS expr
// 2: expr → expr MULT expr
// 3: expr → expr DIV expr
// 4: expr → LPAREN expr RPAREN
// 5: expr → expr LBRAC expr RBRAC
// 6: expr → expr LBRAC DOT RBRAC
// 7: expr → primary
ASTNode* Parser::parse_expr() {
    instNode* head = NULL;
    
    while (true) {
        // relationship between the terminal closest to the top of the stack
        // and the next input symbol.
        if (stack.terminalPeek().term.lexeme == "$" && get_next_symbol() == "$") {
            StackNode s = stack.pop();
            // if (head != NULL) {
            //     instNode* n = head;
            //     while (n->next != NULL)
            //         n = n->next;
            //     s.expr->instN = head;
            // }
            return s.expr;
        }

        Token t = lexer.peek(1);
        int r = get_order_of(stack.terminalPeek().term.token_type);
        int c = get_order_of(t.token_type);
        // cout << "c: " << c << "r: " << r << endl;

        string oper = table[r][c];

        if (oper == "<" || oper == "=") {
            t = lexer.GetToken();
            StackNode s_node = StackNode(TERM, NULL, t);
            stack.push(s_node);
        } else if (oper == ">") { 
            // vector<string> rhs_v;
            vector<StackNode> reduce_me;
            StackNode lpt;
            bool lpt_set = false;

            vector<StackNode> rhs_nodes;
            int rhs_rule = -1;

            while (true) {
                StackNode s = stack.pop();
                if (s.type == TERM) {
                    lpt_set = true;
                    lpt = s;
                }
                reduce_me.push_back(s);
                rhs_nodes.push_back(s);
                int r_ = get_order_of(stack.terminalPeek().term.token_type);
                int c_ = get_order_of(lpt.term.token_type);
                if (lpt_set &&stack.terminalTop().type == TERM &&table[r_][c_] == "<")
                    break;
            }

            reverse(rhs_nodes.begin(), rhs_nodes.end());
            rhs_rule = rhs_rule_key(rhs_nodes);

            // cout << "rhs_rule: " << rhs_rule << endl;

            reverse(reduce_me.begin(), reduce_me.end());

            if (rhs_rule > -1) {
                StackNode e = reduce(reduce_me, rhs_rule);
                stack.push(e);

                // check to make sure it is one of the arithmetic operators and not w
                if (e.expr->instN->oper > 0 && e.expr->instN->oper < 5 && e.expr->w == false) {
                    head = append_to_end(head, e.expr->instN);
                }
            } else {
                syntax_error();
            }
        } else {
            syntax_error();
        }
    }
}

TokenType Parser::peek(int how_far) {
    return lexer.peek(how_far).token_type;
}

Token Parser::expect(TokenType expected_type) {
    Token t = lexer.GetToken();
    if (t.token_type != expected_type)
        syntax_error();
    return t;
}

void Parser::syntax_error() {
    cout << "SNYATX EORRR !!!\n";
    exit(1);
}

// add tail to end of linkedlist
instNode* Parser::append_to_end(instNode* head, instNode* tail) {
    if (head == NULL)
        head = tail;
    else {
        instNode* n = head;
        while (n->next) {
            n = n->next;
        }
        n->next = tail;
    }
    return head;
}

// to determine the relationship between the terminal closest to the top of the stack
string Parser::get_next_symbol() {
    TokenType t = peek(1);
    if (t == EQUAL || t == SEMICOLON) {
        return "$";
    } else if (t == RBRAC) {
        if (peek(2) == EQUAL) {
            return "$";
        }
    } else {
        return lexer.peek(1).lexeme; //  return the next token in all other cases.
    }
}

int Parser::get_order_of(TokenType key) {
    int i = 0;
    for (TokenType t : op_pres_order) {
        if (t == key) return i;
        i++;
    }
    return op_pres_order.size();
}


// RULES and their keys:
// -1: invalid rule (check for this)
// 0: expr → expr MINUS expr
// 1: expr → expr PLUS expr
// 2: expr → expr MULT expr
// 3: expr → expr DIV expr
// 4: expr → LPAREN expr RPAREN
// 5: expr → expr LBRAC expr RBRAC
// 6: expr → expr LBRAC DOT RBRAC
// 7: expr → primary
int Parser::rhs_rule_key(vector<StackNode> s) {
    // 7: expr → primary
    if (
        s.at(0).type == TERM &&
        (s.at(0).term.token_type == NUM || s.at(0).term.token_type == ID)
    )
        return 7;

    if (s.at(0).type == EXPR) {
        // 0: expr → expr MINUS expr
        if (s.at(1).term.token_type == MINUS && s.at(2).type == EXPR)
            return 0;
        // 1: expr → expr PLUS expr
        if (s.at(1).term.token_type == PLUS && s.at(2).type == EXPR)
            return 1;
        // 2: expr → expr MULT expr
        if (s.at(1).term.token_type == MULT && s.at(2).type == EXPR)
            return 2;
        // 3: expr → expr DIV expr
        if (s.at(1).term.token_type == DIV && s.at(2).type == EXPR)
            return 3;
    }
    
    // 4: expr → LPAREN expr RPAREN
    if (
        s.at(0).type == TERM &&
        s.at(0).term.token_type == LPAREN &&
        s.at(1).type == EXPR &&
        s.at(2).term.token_type == RPAREN
    )
        return 4;

    if (s.at(0).type == EXPR) {
        // 5: expr → expr LBRAC expr RBRAC
        if (
            s.at(1).term.token_type == LBRAC &&
            s.at(2).type == EXPR &&
            s.at(3).term.token_type == RBRAC
        )
            return 5;
        // 6: expr → expr LBRAC DOT RBRAC
        if (
            s.at(1).term.token_type == LBRAC &&
            s.at(2).term.token_type == DOT &&
            s.at(3).term.token_type == RBRAC
        )
            return 6;
    }

    // else return -1 which is an error / not valid
    return -1;
}

StackNode Parser::reduce(vector<StackNode> n_stack, int rule_key) {
    ASTNode* ast_node;
    instNode* instN = new instNode();

    // arithmetic operations
    if (rule_key >= 0 && rule_key <= 3) {
        if (rule_key == 0) {
            ast_node = new ASTNode(n_stack.at(2).expr, n_stack.at(0).expr, t_ARRAY, o_MINUS, "-", "-");
            instN->oper = OP_MINUS;
        }
        if (rule_key == 1) {
            ast_node = new ASTNode(n_stack.at(2).expr, n_stack.at(0).expr, t_ARRAY, o_PLUS, "+", "+");
            instN->oper = OP_PLUS;
        }
        if (rule_key == 2) {
            ast_node = new ASTNode(n_stack.at(2).expr, n_stack.at(0).expr, t_ARRAY, o_MULT, "*", "*");
            instN->oper = OP_MULT;
        }
        if (rule_key == 3) {
            ast_node = new ASTNode(n_stack.at(2).expr, n_stack.at(0).expr, t_ARRAY, o_DIV, "/", "/");
            instN->oper = OP_DIV;
        }
        instN->lhsat = DIRECT;
        instN->lhs = first_i++;
        instN->iType = ASSIGN_INST;
        instN->op1at = n_stack.at(0).expr->instN->lhsat;
        instN->op1 = n_stack.at(0).expr->instN->lhs;
        instN->op2at = n_stack.at(2).expr->instN->lhsat;
        instN->op2 = n_stack.at(2).expr->instN->lhs;
    } else if (rule_key == 4) {
        ast_node = n_stack[1].expr;
        ast_node->w = true;

        instN = n_stack[1].expr->instN;
    } else if (rule_key == 5) {
        ast_node = new ASTNode(n_stack.at(2).expr, n_stack.at(0).expr, t_ARRAY, o_EXPR, "[]", "[]");

        instN->lhsat = DIRECT;
        instN->lhs = first_i++;
        instN->iType = ASSIGN_INST;
        instN->op1at = IMMEDIATE;
        instN->op1 = n_stack.at(0).expr->instN->lhs;
        instN->oper = OP_PLUS;
        instN->op2at = n_stack.at(2).expr->instN->lhsat;
        instN->op2 = n_stack.at(2).expr->instN->lhs;
    } else if (rule_key == 6) {
        ast_node = new ASTNode(NULL, n_stack.at(0).expr, t_ARRAY, o_DOT, "[.]", "[.]");

        instN->lhsat = DIRECT;
        instN->lhs = first_i++;
        instN->iType = ASSIGN_INST;
        instN->op1at = IMMEDIATE;
        instN->op1 = n_stack.at(0).expr->instN->lhs;
        instN->oper = OP_NOOP;
    } else if (rule_key == 7) {
        string a;
        if (n_stack.at(0).term.token_type == NUM) {
            string k = "NUM \"" + n_stack.at(0).term.lexeme + "\"";
            ast_node = new ASTNode(NULL, NULL, t_ARRAY, o_NOOP, k, n_stack.at(0).term.lexeme);
            ast_node->n = true;
            instN->lhsat = IMMEDIATE;
            instN->lhs = stoi(n_stack.at(0).term.lexeme);
        } else {
            string k = "ID \"" + n_stack.at(0).term.lexeme + "\"";
            ast_node = new ASTNode(NULL, NULL, t_ARRAY, o_NOOP, k, n_stack.at(0).term.lexeme);
            instN->lhsat = DIRECT;
            instN->lhs = get_location(n_stack.at(0).term.lexeme);
        }
    }
    ast_node->instN = instN;

    StackNode s_node;
    s_node.type = EXPR;
    s_node.expr = ast_node;
    return s_node;
}

ASTNode* Parser::create_inst(ASTNode* ast_node) {
    ASTNode *rt = new ASTNode();
    instNode *instN = new instNode();

    // base catcher to prevent accessor error?
    if (ast_node == NULL) return rt;

    if (ast_node->left == NULL && ast_node->right == NULL) {
        if (ast_node->type == t_SCALAR || ast_node->type == t_ARRAY) {
            instN->lhs = get_location(ast_node->unchanged_val);
            instN->lhsat = DIRECT;
            rt->instN = instN;
            return rt;
        } else if (ast_node->n) {
            instN->lhs = stoi(ast_node->unchanged_val);
            instN->lhsat = IMMEDIATE; // primary
            rt->instN = instN;
            return rt;
        }
    } else {
        ASTNode *right = create_inst(ast_node->right);
        ASTNode *left = create_inst(ast_node->left);
        if (
            (right->type == t_SCALAR && left->type == t_SCALAR) &&
            (ast_node->oper >= 0 && ast_node->oper <= 3)
        ) {
            instN->lhsat = DIRECT;
            instN->lhs = first_i++;
            instN->iType = ASSIGN_INST;
            instN->op1at = left->instN->lhsat;
            instN->op1 = left->instN->lhs;
            instN->op2at = right->instN->lhsat;
            instN->op2 = right->instN->lhs;
            instN->oper = op_to_optype(ast_node->oper);
            rt->instN = instN;
            return rt;
        } else if (
            left->type == t_ARRAY &&
            right->type == t_SCALAR &&
            (ast_node->oper == o_EXPR)
        ) {
            // add undefined part
            instN->lhsat = DIRECT;
            instN->lhs = first_i++;
            instN->iType = ASSIGN_INST;
            instN->op1at = IMMEDIATE;
            instN->op1 = left->instN->lhs;
            instN->oper = OP_PLUS;
            instN->op2at = right->instN->lhsat;
            instN->op2 = right->instN->lhs;
            rt->instN = instN;
            return rt;
        } else if (
            (right->oper == o_DOT && left->oper == o_DOT) &&
            (left->type == t_ARRAY && right->type == t_ARRAY) &&
            (ast_node->oper >= 0 && ast_node->oper <= 2) // make sure it is artith
        ) {
            instNode * head = new instNode(), *prev = new instNode();
            instN->oper = op_to_optype(ast_node->oper);
            rt->instN = instN;
            return rt;
        }
    }
}

int Parser::get_location(string lex) {
    for (Location l : location_list)
        if (l.lex == lex) return l.addr;
    return -1;
}

OpType Parser::op_to_optype(Operator op) {
    // for arithmetic ops only, dont need the rest
    switch (op) {
        case o_MINUS:
            return OP_MINUS;
        case o_PLUS:
            return OP_PLUS;
        case o_MULT:
            return OP_MULT;
        case o_DIV:
            return OP_DIV;
        default:
            cout << "error in op_to_operator!" << endl;
            exit(1);
    }
}

// helper function
bool contains(vector<string> vec, string value) {
    return count(vec.begin(), vec.end(), value);
}

// used for type checking
bool is_arith(string c) {
    return (c == "+" || c == "-" || c == "*" || c == "/");
}

/*
1. If x is a lexeme that appears in the id-list of the scalar-decl-section, then the expression x has type scalar.
2. The type of an expression consisting of a single NUM is scalar.
3. If x appears in the id-list of the array-decl-section, then the expression x[.] has type array.
4. If x appears in the id-list of the array-decl-section, and expr has type scalar, then the expression x[expr] has type scalar.
5. If expr1 and expr2 have type scalar, then expr1 OP expr2(where OP is PLUS, MINUS, MULT or DIV ) has type scalar.
6. If expr1 and expr2 have type array, then expr1 OP expr2(where OP is PLUS or MINUS) has type array.
7. If expr1 and expr2 have type array, then expr1 MULT expr2 has type scalar.
8. If expr1 has type array and expr2 has type scalar, then expr1 [expr2] has type scalar.
9. If expr1 has type scalar, then expr1 [.] has type array.
10. If expr2 has type other than scalar, then expr1 [expr2] has type error.
11. If expr1 has type scalar or error, then expr1 [expr2] has type error.
12. If expr1 and expr2 have different types, then expr1 OP expr2 (where OP is PLUS ,MINUS MULT or DIV ) has type error.
13. If expr1 and expr2 have type array, then expr1 DIV expr2 has type error.
14. If x is a lexeme that does not appear in the id-list of the scalar-decl-section or the id-list of the array-decl-section, then the expression x has type error.
15. If none of the above conditions hold, the expression has type error.
*/
bool Parser::has_expr_type_err(ASTNode *node) {
    if (node->left == NULL && node->right == NULL) {
        if (contains(curr_scalars, node->unchanged_val)) {
            node->type = t_SCALAR; // 1
            return false;
        } else if (contains(curr_arrays, node->unchanged_val)) {
            node->type = t_ARRAY_DECL; // 1
            return false;
        } else if (node->n) {
            node->type = t_SCALAR; // 2
            return false;
        } else if (
            !contains(curr_scalars, node->unchanged_val) &&
            !contains(curr_arrays, node->unchanged_val)
        ) {
            node->type = t_ERROR;  // 14
            return true;
        } else {
            node->type = t_ERROR; // 15
            return true;
        }
    } else {
        bool leftside_errs = has_expr_type_err(node->left);
        bool rightside_errs = node->value != "[.]" ?
            has_expr_type_err(node->right) : false;
        if (
            node->value == "[]" &&
            node->left->type == t_ARRAY_DECL &&
            node->right->type == t_SCALAR
        ) {
            node->type = t_SCALAR; // 4
            return false;
        } else if (
            node->value == "[.]" &&
            node->left->type == t_ARRAY_DECL &&
            node->right == NULL
        ) {
            node->type = t_ARRAY; // 3
            return false;
        } else if (
            is_arith(node->value) && node->left->type == t_SCALAR &&
            node->right->type == t_SCALAR
        ) {
            node->type = t_SCALAR; // 5
            return false;
        } else if ((node->value == "+" || node->value == "-") && node->left->type == t_ARRAY && node->right->type == t_ARRAY) {
            node->type = t_ARRAY; // 6
            return false;
        }
        else if (node->value == "*" && node->left->type == t_ARRAY && node->right->type == t_ARRAY) {
            node->type = t_SCALAR; // 7
            return false;
        } else if (node->value == "[]" && node->left->type == t_ARRAY && node->right->type == t_SCALAR) {
            node->type = t_SCALAR; // 8
            return false;
        } else if (node->value == "[.]" && node->left->type == t_SCALAR && node->right == NULL) {
            node->type = t_ARRAY; // 9
            return false;
        } else if (node->value == "[]" && ((node->left->type == t_SCALAR && node->left->type == t_ERROR) || (node->right->type != t_SCALAR))) {
            node->type = t_ERROR; // 10 / 11
            return true;
        }
        else if (is_arith(node->value) && (node->left->type != node->right->type)) {
            node->type = t_ERROR; // 12
            return true;
        } else if (node->value == "/" && node->left->type == t_ARRAY && node->right->type == t_ARRAY) {
            node->type = t_ERROR; // 13
            return true;
        } else {
            node->type = t_ERROR; // 15
            return true;
        }

        return (leftside_errs || rightside_errs);
    }

    return false;
}

bool Parser::has_assign_type_err(ASTNode *node) {
    if (!(node->left == NULL && node->right == NULL)) {
        if (node->left->type == node->right->type) {
            node->type = node->left->type;
            return false;
        } else if (node->left->type == t_ARRAY && node->right->type == t_SCALAR) {
            node->type = t_ARRAY;
            return false;
        } else {
            node->type = t_ERROR;
            return true;
        }
    }
    return false;
}

/*
1. If x is a lexeme that appears in the id-list of the scalar-decl-section, then the variable access x has type scalar.
2. If x is a lexeme that appears in the id-list of the array-decl-section and expr has type scalar, then x[expr] has type scalar.
3. If x is a lexeme that appears in the id-list of the array-decl-section, then x[.] has type array.
4. If x is a lexeme that does not appear in the id-list of the scalar-decl-section then the variable access x has type error.
5. If x is a lexeme that does not appear in the id-list of the of the array-decl-section, then the variable access x[.] has type error.
6. If x is a lexeme that does not appear in the id-list of the array-decl-section, then the variable access x[expr] has type error.
*/
bool Parser::has_access_type_err(ASTNode *node) {
    bool acc = false;
    if (node->left == NULL && node->right == NULL) {
        if (contains(curr_scalars, node->unchanged_val)) {
            node->type = t_SCALAR; // 1
            return false;
        } else {
            node->type = t_ERROR; // 4
            return true;
        }
    } else {
        bool expr = false;
        if (node->value != "[.]")
            expr = has_expr_type_err(node->right);
        if (node->value == "[]" && contains(curr_arrays, node->left->unchanged_val) && node->right->type == t_SCALAR) {
            node->type = t_SCALAR; // 2
        } else if (node->value == "[.]" && contains(curr_arrays, node->left->unchanged_val)) {
            node->type = t_ARRAY; // 3
        // } else if (node->value == "[.]" && contains(curr_arrays, node->left->unchanged_val)) {
        //     node->type = t_ERROR; // 5
        //     acc = true;
        } else if (node->value == "[]" && contains(curr_arrays, node->left->unchanged_val)) {
            node->type = t_ERROR; // 6
            acc = true;
        } else {
            node->type = t_ERROR; // default err
            acc = true;
        }

        return (expr || acc);
    }

    return acc;
}

void Parser::print_type_errors() {
    if (type_errors.size() == 0) {
        if (assign_errors.size() == 0)
            cout << "Amazing! No type errors here :)\n";
        else {
            cout << "The following assignment(s) is/are invalid :(\n\n";
            for (int line : assign_errors)
                cout << "Line " << line << endl;
        }
        return;
    }
    cout << "Disappointing expression type error :(\n\n";
    for (int line : type_errors)
        cout << "Line " << line << endl;
}

/* --- MAIN TASK HANDLERS --- */

// Task 1
void Parser::parse_and_generate_AST() {
    parse_program();
    ASTNode* root = astrees[0].root;
    int h = astrees[0].tree_height(root);
    for (int i = 1; i <= h; i++) 
        astrees[0].print_tree(root, i);
}

// Task 2
void Parser::parse_and_type_check() {
    parse_program();
    print_type_errors();
}

// Task 3
instNode* Parser::parse_and_generate_statement_list()
{
    cout << "3" << endl;

    // The following is the hardcoded statement list 
    // generated for a specific program
    // you should replace this code with code that parses the
    // input and generayes a statement list
    // 
    // program
    // SCALAR a b c d
    // ARRAY x y z
    // a = 1;
    // b = 2;
    // c = 3;
    // d = (a+b)*(b+c);
    // OUTPUT d;
    // x[a+b] = d;
    // OUTPUT x[3];
    //
    //  a will be at location 0
    //  b will be at location 1
    //  c will be at location 2
    //  d will be at location 3
    //  x will be at location 4 - 13
    //  y will be at location 14 - 23
    //  z will be at location 24 - 33
    //  t1 will be at location 34 : intermediate value for (a+b)
    //  t2 will be at location 35 : intermediate value for (b+c)
    //  t3 will be at location 36 : intermediate value (a+b)*(b+c)
    //  t4 will be at location 37 : intermediate value for a+b index of array
    //  t5 will be at location 38 : intermediate value for addr of x[a+b] =
    //                              address_of_x + value of a+b =
    //                              4 + value of a+b
    //  t6 will be at location 39 : intermediate value for addr of x[3] =
    //                              address_of_x + value of 3 =
    //                              4 + value of 3 (computation is not done at
    //                              compile time)
    //
    instNode * i01 = new instNode();
    i01->lhsat=DIRECT; i01->lhs = 0;    // a
    i01->iType=ASSIGN_INST;             // =
    i01->op1at=IMMEDIATE; i01->op1 = 1; // 1
    i01->oper = OP_NOOP;                // no operator

    instNode * i02 = new instNode();
    i02->lhsat=DIRECT; i02->lhs = 1;    // b
    i02->iType=ASSIGN_INST;             // =
    i02->op1at=IMMEDIATE; i02->op1 = 2; // 2
    i02->oper = OP_NOOP;                // no operator

    i01->next = i02;

    instNode * i03 = new instNode();
    i03->lhsat=DIRECT; i03->lhs = 2;    // c
    i03->iType=ASSIGN_INST;             // =
    i03->op1at=IMMEDIATE; i03->op1 = 3; // 3
    i03->oper = OP_NOOP;                // no operator

    i02->next = i03;


    instNode * i1 = new instNode();
    i1->lhsat=DIRECT; i1->lhs = 34; // t1
    i1->iType=ASSIGN_INST;          // =
    i1->op1at=DIRECT; i1->op1 = 0;  // a
    i1->oper = OP_PLUS;             // +
    i1->op2at=DIRECT; i1->op2 = 1;  // b

    i03->next = i1;

    instNode * i2 = new instNode();
    i2->lhsat=DIRECT; i2->lhs = 35; // t2
    i2->iType=ASSIGN_INST;          // =
    i2->op1at=DIRECT; i2->op1 = 1;  // b
    i2->oper = OP_PLUS;             // +
    i2->op2at=DIRECT; i2->op2 = 2;  // c

    i1->next = i2;

    instNode * i3 = new instNode();
    i3->lhsat=DIRECT; i3->lhs = 36; // t3
    i3->iType=ASSIGN_INST;          // =
    i3->op1at=DIRECT; i3->op1 = 34;  // t1
    i3->oper = OP_MULT;             // *
    i3->op2at=DIRECT; i3->op2 = 35;  // t2


    i2->next = i3;                  // i3 should be after i1 and i2

    instNode * i4 = new instNode();
    i4->lhsat=DIRECT; i4->lhs = 3;  // d
    i4->iType=ASSIGN_INST;          // =
    i4->op1at=DIRECT; i4->op1 = 36; // t3
    i4->oper = OP_NOOP;             // no operator


    i3->next = i4;

    instNode * i5 = new instNode();
    i5->iType=OUTPUT_INST;          // OUTPUT
    i5->op1at=DIRECT; i5->op1 = 3;  // d

    i4->next = i5;

    instNode * i6 = new instNode();
    i6->lhsat=DIRECT; i6->lhs = 37; // t4
    i6->iType=ASSIGN_INST;          // =
    i6->op1at=DIRECT; i6->op1 = 0;  // a
    i6->oper = OP_PLUS;             // +
    i6->op2at=DIRECT; i6->op2 = 1;  // b
    i5->next = i6;

    instNode * i7 = new instNode();
    i7->lhsat=DIRECT; i7->lhs = 38;    // t5
    i7->iType=ASSIGN_INST;             // =
    i7->op1at=IMMEDIATE; i7->op1 = 4;  // address of x = 4 available
                                       // at compile time
    i7->oper = OP_PLUS;                // +
    i7->op2at=DIRECT; i7->op2 = 37;    // t5 (contains value of a+b

    i6->next = i7;

    instNode * i8 = new instNode();
    i8->lhsat=INDIRECT; i8->lhs = 38;  // x[a+b]
    i8->iType=ASSIGN_INST;             // =
    i8->op1at=DIRECT; i8->op1 = 3;     // d
    i8->oper = OP_NOOP;

    i7->next = i8;

    instNode * i9 = new instNode();
    i9->lhsat=DIRECT; i9->lhs = 39;    // t6 will contain address of x[3]
    i9->iType=ASSIGN_INST;             // =
    i9->op1at=IMMEDIATE; i9->op1 = 4;  // address of x = 4 available
                                       // at compile time
    i9->oper = OP_PLUS;                // +
    i9->op2at=IMMEDIATE; i9->op2 = 3;  // 3

    i8->next = i9;

    instNode * i10 = new instNode();
    i10->iType=OUTPUT_INST;              // OUTPUT
    i10->op1at=INDIRECT; i10->op1 = 39;  // x[3] by providing its
                                         // address indirectly through
                                         // t6

    i9->next = i10;


    instNode* code = i01;

    return code;
}

/* --- MAIN TASK HANDLERS --- */
