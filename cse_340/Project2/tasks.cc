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
    scalars = parse_scalar_decl_section();
    arrays = parse_array_decl_section();
    reverse(scalars.begin(), scalars.end());
    reverse(arrays.begin(), arrays.end());

    checker.set_declarations(arrays, scalars); 

    for (string s : scalars) {
        location_list.push_back(Location(next_index, s, l_SCALAR));
        next_index++;
    }
    for (string a : arrays) {
        location_list.push_back(Location(next_index, a, l_ARRAY));
        next_index++;
    }

    last_index = next_index;
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
    if (peek(1) == ID) {
        parsed_ids = parse_id_list();
        parsed_ids.push_back(id);
    } else if (peek(1) == ARRAY || peek(1) == LBRACE) {
        parsed_ids.push_back(id);
    } else {
        syntax_error();
    }
    return parsed_ids;
}

void Parser::parse_block() {
    expect(LBRACE);
    parse_stmt_list();
    expect(RBRACE);
}

instNode* Parser::parse_stmt_list() {
    instNode* i = parse_stmt();
    
    TokenType t = peek(1);
    if (t == ID || t == OUTPUT) {
        append_to_end(i, parse_stmt_list());
        return i;
    } else if (t == RBRACE) {
        return i;
    } else {
        syntax_error();
    }
}

instNode* Parser::parse_stmt() {
    instNode* i;

    TokenType t = peek(1);
    if (t == ID) {
        i = parse_assign_stmt();
        return i;
    } else if (t == OUTPUT) {
        i = parse_output_stmt();
        return i;
    } else {
        syntax_error();
    }
}

// LOGIC frr!!
instNode* Parser::parse_assign_stmt() {
    ASTNode *lhs = parse_variable_access();
    int ln = expect(EQUAL).line_no;
    ASTNode *rhs = parse_expr();
    astrees.push_back(ASTree(new ASTNode(rhs, lhs, "="), expect(SEMICOLON).line_no));
    checker.type_check_assignment_stmt(rhs, lhs, ln);

    instNode *node = rhs->instN;
    while (node->next != nullptr)
    {
        node = node->next;
    }

    instNode *node2 = lhs->instN;
    while (node2->next != nullptr)
    {
        node2 = node2->next;
    }

    instNode *i = new instNode();
    i->lhsat = (node2->lhs > last_index) ? INDIRECT : DIRECT;
    i->lhs = node2->lhs;
    i->iType = ASSIGN_INST;
    i->op1at = node->lhsat;
    i->op1 = node->lhs;
    i->oper = OP_NOOP;

    instNode * l = create_inst(lhs)->instN;
    instNode * r = create_inst(rhs)->instN;

    instNode *rt_me = i;

    if (lhs->instN->op1 != -1 && rhs->instN->op1 != -1)
    {
        append_to_end(lhs->instN, rhs->instN);
        append_to_end(lhs->instN, i);
        rt_me = lhs->instN;
    }
    else if (rhs->instN->op1 == -1 && lhs->instN->op1 != -1)
    {
        append_to_end(lhs->instN, i);
        rt_me = lhs->instN;
    }
    else if (rhs->instN->op1 != -1 && lhs->instN->op1 == -1)
    {
        append_to_end(rhs->instN, i);
        rt_me = rhs->instN;
    }

    return rt_me;
}

instNode* Parser::parse_output_stmt() {
    int lo = expect(OUTPUT).line_no;
    ASTNode* var_acc = parse_variable_access();
    checker.type_check_output_stmt(var_acc, lo);
    expect(SEMICOLON);

    instNode* n = var_acc->instN;
    while (n->next != nullptr) {
        n = n->next;
    }

    // LOGIC @!!!@!!
    instNode *i = new instNode();
    i->iType = OUTPUT_INST;
    i->op1at = (n->lhs > last_index) ? INDIRECT : DIRECT;
    i->op1 = n->lhs;

    if (var_acc->instN->op1 != -1) {
        var_acc->instN = append_to_end(var_acc->instN, i);
        return var_acc->instN;
    } else {
        return i;
    }
}

ASTNode* Parser::parse_variable_access() {
    StackNode e = reduce({StackNode(TERM, NULL, expect(ID))}, {"primary"});
    TokenType t = peek(1);
    if (t == LBRAC) {
        stack.push(e);
        return parse_expr();
    } else if (
        t == EQUAL ||
        t == SEMICOLON
    ) {
        return e.expr;
    } else {
        syntax_error();
    }
}

ASTNode* Parser::parse_expr() {
    instNode* head = NULL;
    
    while (1) {
        if (
            stack.terminalPeek().term.lexeme == "$" &&
            get_next_symbol() == "$"
        ) {
            StackNode s = stack.pop();
            if (head != NULL) {
                instNode* n = head;
                while (n->next != nullptr) {
                    n = n->next;
                }
                s.expr->instN = head;
            }
            return s.expr;
        } else {
            Token t = lexer.peek(1);
            int r = index_of(stack.terminalPeek().term.token_type);
            int c = index_of(t.token_type);

            string oper = table[r][c];

            // cout << "c: " << c << "r: " << r << endl;
            
            if (oper == "<" || oper == "=") {
                t = lexer.GetToken();

                // NAMES
                StackNode s_node;
                s_node.type = TERM;
                s_node.expr = NULL;
                s_node.term = t;

                stack.push(s_node);
            } else if (oper == ">") { 
                // LOGIC / NAMES !! all of this
                vector<string> RHS = {};
                vector<StackNode> reduce_me = {};
                StackNode lpt = {};
                bool lpt_set = false;
                while (1)
                {
                    StackNode s = stack.pop();
                    if (s.type == TERM)
                    {
                        lpt_set = true;
                        lpt = s;
                    }
                    reduce_me.push_back(s);
                    RHS.push_back(get_rhs(s));
                    if (
                        lpt_set &&
                        stack.terminalTop().type == TERM &&
                        table[index_of(stack.terminalPeek().term.token_type)][index_of(lpt.term.token_type)] == "<"
                    )
                        break;
                }
                reverse(RHS.begin(), RHS.end());
                reverse(reduce_me.begin(), reduce_me.end());

                if (is_valid_rule(RHS))
                {
                    StackNode E = reduce(reduce_me, RHS);
                    stack.push(E);

                    if (
                        (E.expr->instN->oper == OP_PLUS ||
                        E.expr->instN->oper == OP_MULT ||
                        E.expr->instN->oper == OP_DIV ||
                        E.expr->instN->oper == OP_MINUS) &&
                        E.expr->wrapped == false
                    ) {
                        head = append_to_end(head, E.expr->instN);
                    }
                } else {
                    syntax_error();
                }
            } else {
                syntax_error();
            }
        }
    }
}

void Parser::parse_primary() {}

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

instNode* Parser::append_to_end(instNode* head, instNode* tail) {
    if (head == NULL) {
        head = tail;
    } else {
        instNode* n = head;
        while (n->next) {
            n = n->next;
        }
        n->next = tail;
    }
    return head;
}

// LOGIC
string Parser::get_next_symbol() {
    TokenType t = peek(1);
    TokenType t2 = peek(2);
    if (t == EQUAL || t == SEMICOLON) {
        return "$";
    } else if (t == RBRAC) {
        if (t2 == EQUAL) {
            return "$";
        }
    } else {
        return lexer.peek(1).lexeme;
    }
}

string Parser::get_rhs(StackNode s)
{
    string lexeme;
    if (s.type == TERM)
    {
        if (s.term.token_type == NUM || s.term.token_type == ID)
            lexeme = "primary";
        else if (s.term.token_type == PLUS)
            lexeme = "PLUS";
        else if (s.term.token_type == MINUS)
            lexeme = "MINUS";
        else if (s.term.token_type == MULT)
            lexeme = "MULT";
        else if (s.term.token_type == DIV)
            lexeme = "DIV";
        else if (s.term.token_type == LPAREN)
            lexeme = "LPAREN";
        else if (s.term.token_type == RPAREN)
            lexeme = "RPAREN";
        else if (s.term.token_type == RBRAC)
            lexeme = "RBRAC";
        else if (s.term.token_type == LBRAC)
            lexeme = "LBRAC";
        else if (s.term.token_type == DOT)
            lexeme = "DOT";
    }
    else
        lexeme = "expr";
    return lexeme;
}

// LOGIC !!
int Parser::index_of(TokenType key)
{
    switch (key)
    {
    case PLUS:
        return 0;
    case MINUS:
        return 1;
    case MULT:
        return 2;
    case DIV:
        return 3;
    case LPAREN:
        return 4;
    case RPAREN:
        return 5;
    case LBRAC:
        return 6;
    case DOT:
        return 7;
    case RBRAC:
        return 8;
    case NUM:
        return 9;
    case ID:
        return 10;
    default:
        return 11;
    }
}

// LOGIC / NAMES
bool Parser::is_valid_rule(vector<string> rule) {
    for (auto &expr : expr_rules) {
        if (expr.second == rule)
            return true;
    }
    return false;
}

StackNode Parser::reduce(vector<StackNode> stk, vector<string> rhs) {
    StackNode node;
    node.type = EXPR;
    ASTNode *tnode;
    instNode *instN = new instNode();
    if (rhs == vector<string>({"expr", "MINUS", "expr"}))
    {
        tnode = new ASTNode(stk[2].expr, stk[0].expr, t_ARRAY, o_MINUS, "-", "-");

        instN->lhsat = DIRECT;
        instN->lhs = next_index++;
        instN->iType = ASSIGN_INST;
        instN->op1at = stk[0].expr->instN->lhsat;
        instN->op1 = stk[0].expr->instN->lhs;
        instN->oper = OP_MINUS;
        instN->op2at = stk[2].expr->instN->lhsat;
        instN->op2 = stk[2].expr->instN->lhs;
    }
    else if (rhs == vector<string>({"expr", "PLUS", "expr"}))
    {
        tnode = new ASTNode(stk[2].expr, stk[0].expr, t_ARRAY, o_PLUS, "+", "+");

        instN->lhsat = DIRECT;
        instN->lhs = next_index++;
        instN->iType = ASSIGN_INST;
        instN->op1at = stk[0].expr->instN->lhsat;
        instN->op1 = stk[0].expr->instN->lhs;
        instN->oper = OP_PLUS;
        instN->op2at = stk[2].expr->instN->lhsat;
        instN->op2 = stk[2].expr->instN->lhs;
    }
    else if (rhs == vector<string>({"expr", "MULT", "expr"}))
    {
        tnode = new ASTNode(stk[2].expr, stk[0].expr, t_ARRAY, o_MULT, "*", "*");

        instN->lhsat = DIRECT;
        instN->lhs = next_index++;
        instN->iType = ASSIGN_INST;
        instN->op1at = stk[0].expr->instN->lhsat;
        instN->op1 = stk[0].expr->instN->lhs;
        instN->oper = OP_MULT;
        instN->op2at = stk[2].expr->instN->lhsat;
        instN->op2 = stk[2].expr->instN->lhs;
    }
    else if (rhs == vector<string>({"expr", "DIV", "expr"}))
    {
        tnode = new ASTNode(stk[2].expr, stk[0].expr, t_ARRAY, o_DIV, "/", "/");

        instN->lhsat = DIRECT;
        instN->lhs = next_index++;
        instN->iType = ASSIGN_INST;
        instN->op1at = stk[0].expr->instN->lhsat;
        instN->op1 = stk[0].expr->instN->lhs;
        instN->oper = OP_DIV;
        instN->op2at = stk[2].expr->instN->lhsat;
        instN->op2 = stk[2].expr->instN->lhs;
    }
    else if (rhs == vector<string>({"LPAREN", "expr", "RPAREN"}))
    {
        tnode = stk[1].expr;
        tnode->wrapped = true;

        instN = stk[1].expr->instN;
    }
    else if (rhs == vector<string>({"expr", "LBRAC", "expr", "RBRAC"}))
    {
        tnode = new ASTNode(stk[2].expr, stk[0].expr, t_ARRAY, o_EXPR, "[]", "[]");

        instN->lhsat = DIRECT;
        instN->lhs = next_index++;
        instN->iType = ASSIGN_INST;
        instN->op1at = IMMEDIATE;
        instN->op1 = stk[0].expr->instN->lhs;
        instN->oper = OP_PLUS;
        instN->op2at = stk[2].expr->instN->lhsat;
        instN->op2 = stk[2].expr->instN->lhs;
    }
    else if (rhs == vector<string>({"expr", "LBRAC", "DOT", "RBRAC"}))
    {
        tnode = new ASTNode(NULL, stk[0].expr, t_ARRAY, o_DOT, "[.]", "[.]");

        instN->lhsat = DIRECT;
        instN->lhs = next_index++;
        instN->iType = ASSIGN_INST;
        instN->op1at = IMMEDIATE;
        instN->op1 = stk[0].expr->instN->lhs;
        instN->oper = OP_NOOP;
    }
    else
    { // primary
        tnode = new ASTNode(NULL, NULL, t_ARRAY, o_NOOP, ((stk[0].term.token_type == NUM) ? ("NUM \"" + stk[0].term.lexeme + "\"") : ("ID \"" + stk[0].term.lexeme + "\"")), stk[0].term.lexeme);
        if (stk[0].term.token_type == NUM)
        {
            tnode->is_num = true;
            instN->lhsat = IMMEDIATE;
            instN->lhs = stoi(stk[0].term.lexeme);
        }
        else
        {
            instN->lhsat = DIRECT;
            instN->lhs = get_location(stk[0].term.lexeme);
        }
    }
    tnode->instN = instN;
    node.expr = tnode;
    return node;
}

ASTNode* Parser::create_inst(ASTNode* node) {
    ASTNode *rt_me = new ASTNode();
    instNode *instN = new instNode();

    if (node == NULL) return rt_me;
    if (node->left == NULL && node->right == NULL)
    {
        if (node->type == t_SCALAR || node->type == t_ARRAY)
        {
            instN->lhs = get_location(node->raw_value);
            instN->lhsat = DIRECT;
            rt_me->instN = instN;
            return rt_me;
        }
        else if (node->is_num)
        {
            instN->lhs = stoi(node->raw_value);
            instN->lhsat = IMMEDIATE;
            rt_me->instN = instN;
            return rt_me;
        }
    }
    else
    {
        ASTNode *right = create_inst(node->right);
        ASTNode *left = create_inst(node->left);
        if ((right->type == t_SCALAR && left->type == t_SCALAR) && (node->oper == o_PLUS || node->oper == o_MINUS || node->oper == o_MULT || node->oper == o_DIV))
        {
            instN->lhsat = DIRECT;
            instN->lhs = next_index++;
            instN->iType = ASSIGN_INST;
            instN->op1at = left->instN->lhsat;
            instN->op1 = left->instN->lhs;
            instN->op2at = right->instN->lhsat;
            instN->op2 = right->instN->lhs;
            switch (node->oper)
            {
            case o_PLUS:
                instN->oper = OP_PLUS;
                break;
            case o_MINUS:
                instN->oper = OP_MINUS;
                break;
            case o_MULT:
                instN->oper = OP_MULT;
                break;
            case o_DIV:
                instN->oper = OP_DIV;
                break;
            default:
                cout << "invalid operation type !!!!\n";
                break;
            }
            rt_me->instN = instN;
            return rt_me;
        }else if(left->type == t_ARRAY && right->type == t_SCALAR && (node->oper == o_EXPR)){
            // add undefined part
            instN->lhsat = DIRECT;
            instN->lhs = next_index++;
            instN->iType = ASSIGN_INST;
            instN->op1at = IMMEDIATE;
            instN->op1 = left->instN->lhs;
            instN->oper = OP_PLUS;
            instN->op2at = right->instN->lhsat;
            instN->op2 = right->instN->lhs;
            rt_me->instN = instN;
            return rt_me;
        }else if((right->oper == o_DOT && left->oper == o_DOT) && (left->type == t_ARRAY && right->type == t_ARRAY) && (node->oper == o_PLUS || node->oper == o_MINUS || node->oper == o_MULT)){
            instNode * head = new instNode(), *prev = new instNode();
            switch (node->oper)
            {
            case o_PLUS:
                instN->oper = OP_PLUS;

                

                for(int i = 0; i < 10; i++){
                    if(i == 0){
                        head->lhsat = DIRECT;
                        head->lhs = next_index++; // c[i]
                        head->iType = ASSIGN_INST;
                        head->op1at = IMMEDIATE;
                        head->op1 = left->instN->lhs;
                        head->oper = OP_PLUS;
                        head->op2at = IMMEDIATE;
                        head->op2 = i;
                    }else{
                        prev->lhsat = DIRECT;
                        prev->lhs = next_index++; // c[i]
                        prev->iType = ASSIGN_INST;
                        prev->op1at = IMMEDIATE;
                        prev->op1 = left->instN->lhs;
                        prev->oper = OP_PLUS;
                        prev->op2at = IMMEDIATE;
                        prev->op2 = i;
                        head = append_to_end(head, prev);
                    }
                    instN = head;


                }

                break;
            case o_MINUS:
                instN->oper = OP_MINUS;
                break;
            case o_MULT:
                instN->oper = OP_MULT;
                break;
            default:
                cout << "invalid operation type !!!?!\n";
                break;
            }

            rt_me->instN = instN;
            return rt_me;


        }
    }
}

int Parser::get_location(string lex) {
    for (const auto &l : location_list) {
        if (l.lex == lex) {
            return l.addr;
        }
    }
    return -1;
}

/* --- MAIN TASK HANDLERS --- */

// Task 1
void Parser::parse_and_generate_AST()
{
    parse_program();
    ASTNode* root = astrees[0].root;
    int h = astrees[0].tree_height(root);
    for (int i = 1; i <= h; i++)
    {
        astrees[0].print_tree(root, i);
    }
}

// Task 2
void Parser::parse_and_type_check()
{
    parse_program();
    checker.print_type_errors();
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

bool in_vector(vector<string> vec, string value)
{
    return count(vec.begin(), vec.end(), value);
}

int TypeChecker::type_check_expr(ASTNode *node)
{
    // 1 = good , 2 = type error, 3 = assign error
    int result = 1;
    if (node->left == NULL && node->right == NULL)
    {
        if (in_vector(scalars, node->raw_value)) // rule 1
        {
            node->type = t_SCALAR;
        }
        else if (in_vector(arrays, node->raw_value))
        {
            node->type = t_ARRAY_DECL;
        }
        else if (node->is_num) // rule 2
        {

            node->type = t_SCALAR;
        }
        else if (!in_vector(scalars, node->raw_value) && !in_vector(arrays, node->raw_value)) // rule 14
        {
            node->type = t_ERROR;
            result = 2;
        }
        else // rule 15
        {
            node->type = t_ERROR;
            result = 2;
        }
    }
    else
    {
        int ls = type_check_expr(node->left);
        int rs = (node->value != "[.]" ? type_check_expr(node->right) : 1);
        if (node->value == "[]" && node->left->type == t_ARRAY_DECL && node->right->type == t_SCALAR) // rule 4
        {
            node->type = t_SCALAR;
        }
        else if (node->value == "[.]" && node->left->type == t_ARRAY_DECL && node->right == NULL) // rule 3
        {
            node->type = t_ARRAY;
            // cout << "hi\n";
        }
        else if ((node->value == "+" || node->value == "-" || node->value == "*" || node->value == "/") && node->left->type == t_SCALAR && node->right->type == t_SCALAR)
        {
            node->type = t_SCALAR; // rule 5
        }
        else if ((node->value == "+" || node->value == "-") && node->left->type == t_ARRAY && node->right->type == t_ARRAY) // rule 6
        {
            node->type = t_ARRAY;
        }
        else if (node->value == "*" && node->left->type == t_ARRAY && node->right->type == t_ARRAY) // rule 7
        {
            node->type = t_SCALAR;
        }
        else if (node->value == "[]" && node->left->type == t_ARRAY && node->right->type == t_SCALAR) // rule 8
        {
            node->type = t_SCALAR;
        }
        else if (node->value == "[.]" && node->left->type == t_SCALAR && node->right == NULL) // rule 9
        {
            node->type = t_ARRAY;
        }
        else if (node->value == "[]" && ((node->left->type == t_SCALAR && node->left->type == t_ERROR) || (node->right->type != t_SCALAR)))
        { // rule 10 and 11
            node->type = t_ERROR;
            result = 2;
        }
        else if ((node->value == "+" || node->value == "-" || node->value == "*" || node->value == "/") && (node->left->type != node->right->type))
        { // rule 12
            node->type = t_ERROR;
            result = 2;
        }
        else if (node->value == "/" && node->left->type == t_ARRAY && node->right->type == t_ARRAY)
        { // rule 13
            node->type = t_ERROR;
            result = 2;
        }
        else // rule 15
        {
            node->type = t_ERROR;
            result = 2;
        }

        result = ((ls == 2 || rs == 2) ? 2 : result);
    }

    return result;
}

int TypeChecker::type_check_assignment(ASTNode *node)
{
    // 1 = good , 2 = type error, 3 = assign error
    int result = 1;
    if (!(node->left == NULL && node->right == NULL))
    {
        if (node->left->type == node->right->type)
        {
            node->type = node->left->type;
        }
        else if (node->left->type == t_ARRAY && node->right->type == t_SCALAR)
        {
            node->type = t_ARRAY;
        }
        else
        {
            node->type = t_ERROR;
            result = 2;
        }
    }
    return result;
}

int TypeChecker::type_check_var_access(ASTNode *node)
{
    // 1 = good , 2 = type error, 3 = assign error
    int result = 1;
    if (node->left == NULL && node->right == NULL)
    {
        if (in_vector(scalars, node->raw_value)) // rule 1
        {
            node->type = t_SCALAR;
        }
        else // rule 4
        {
            node->type = t_ERROR;
            result = 2;
        }
    }
    else
    {
        int expr = 1;
        if (node->value != "[.]")
        {
            expr = type_check_expr(node->right);
        }

        if (node->value == "[]" && in_vector(arrays, node->left->raw_value) && node->right->type == t_SCALAR) // rule 2
        {
            node->type = t_SCALAR;
        }
        else if (node->value == "[.]" && in_vector(arrays, node->left->raw_value)) // rule 3
        {
            node->type = t_ARRAY;
        }
        else if (node->value == "[.]" && in_vector(arrays, node->left->raw_value)) // rule 5
        {
            node->type = t_ERROR;
            result = 2;
        }
        else if (node->value == "[]" && in_vector(arrays, node->left->raw_value)) // rule 6
        {
            node->type = t_ERROR;
            result = 2;
        }
        else
        {
            node->type = t_ERROR;
            result = 2;
        }

        result = ((expr == 2) ? 2 : result);
    }

    return result;
}

void TypeChecker::set_declarations(vector<string> a, vector<string> s)
{
    arrays = a;
    scalars = s;
}

void TypeChecker::type_check_assignment_stmt(ASTNode *rhs, ASTNode *lhs, const int ln)
{
    int e = type_check_expr(rhs);
    int v = type_check_var_access(lhs);

    if (e == 2)
    {
        type_errors.push_back(ln);
    }
    else if (v == 2)
    {
        type_errors.push_back(ln);
    }

    int assn = type_check_assignment(new ASTNode(rhs, lhs, "="));
    if (assn == 2)
    {
        assign_errors.push_back(ln);
    }
}

void TypeChecker::type_check_output_stmt(ASTNode *va, const int ln)
{
    if (type_check_var_access(va) == 2)
    {
        type_errors.push_back(ln);
    }
}

void TypeChecker::print_type_errors()
{
    if (type_errors.empty())
    {
        if (assign_errors.empty())
        {
            cout << "Amazing! No type errors here :)\n";
        }
        else
        {
            cout << "The following assignment(s) is/are invalid :(\n\n";
            for (auto line : assign_errors)
            {
                cout << "Line " << line << "\n";
            }
        }
    }
    else
    {
        cout << "Disappointing expression type error :(\n\n";
        for (auto line : type_errors)
        {
            cout << "Line " << line << "\n";
        }
    }
}