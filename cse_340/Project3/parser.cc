/*
 * CSE 340 Project 3 - parser.cc
 * Tyler Fichiera
 */
#include "parser.h"
#include "execute.h"
#include <iostream>

using namespace std;

Token Parser::expect(TokenType expected_type) {
    Token t = lexer.GetToken();
    if (t.token_type != expected_type) {
        cout << "SYNTAX ERROR !!!\n";
        exit(1);
    }
    return t;
}

// program → var_section body inputs
InstructionNode* Parser::parse_program() {
    parse_var_section();
    InstructionNode* body = parse_body();
    parse_inputs();
    return body;
}

// var section → id_list SEMICOLON
void Parser::parse_var_section() {
    vector<string> parsed_ids;
    parsed_ids = parse_id_list(parsed_ids);
    
    for (string id : parsed_ids) {
        var_addr_map[id] = current_memory_addr++;
    }
}

// id_list → ID COMMA id_list | ID
vector<string> Parser::parse_id_list(vector<string> parsed_ids) {
    Token t = expect(ID);
    parsed_ids.push_back(t.lexeme);

    Token t2 = lexer.GetToken();
    if (t2.token_type != SEMICOLON) {
        return parse_id_list(parsed_ids);
    }

    return parsed_ids;
}

// body → LBRACE stmt_list RBRACE
InstructionNode* Parser::parse_body() {
    expect(LBRACE);
    InstructionNode* stmt_list = parse_stmt_list();
    expect(RBRACE);

    return stmt_list;
}

// stmt_list → stmt stmt_list | stmt
// stmt → assign_stmt | while_stmt | if_stmt | switch_stmt | for_stmt
// stmt → output_stmt | input_stmt
InstructionNode* Parser::parse_stmt_list() {
    InstructionNode* stmt_list = NULL;
    InstructionNode* stmt_head = NULL;

    Token token = lexer.peek(1);
    do {
        InstructionNode* new_inst;
        // stmt → while_stmt
        if (token.token_type == WHILE) {
            new_inst = parse_while_stmt();
        }
        // stmt → if_stmt
        else if (token.token_type == IF) {
            new_inst = parse_if_stmt();
        }
        // stmt → switch_stmt
        else if (token.token_type == SWITCH) {
            new_inst = parse_switch_stmt();
        }
        // stmt → for_stmt
        else if (token.token_type == FOR) {
            new_inst = parse_for_stmt();
        }
        // stmt → output_stmt | input_stmt
        else if (token.token_type == OUTPUT) {
            new_inst = parse_output_stmt();
        } else if (token.token_type == INPUT) {
            new_inst = parse_input_stmt();
        }
        // stmt → assign_stmt
        else {
            new_inst = parse_assign_stmt();
        }

        if (stmt_head) {
            auto tmp = stmt_head;
            stmt_head = new_inst;
            tmp->next = stmt_head;
        } else {
            stmt_head = new_inst;
            stmt_list = stmt_head;
        }

        if (new_inst->next) {
            while (new_inst->next) {
                if (new_inst->type == CJMP) {
                    new_inst = new_inst->cjmp_inst.target;
                } else {
                    new_inst = new_inst->next;
                }
            }
            stmt_head = new_inst;
        }

        token = lexer.peek(1);
    } while (token.token_type != RBRACE);

    return stmt_list;
}

// output_stmt → output ID SEMICOLON
InstructionNode* Parser::parse_output_stmt() {
    expect(OUTPUT);
    string id = expect(ID).lexeme;
    expect(SEMICOLON);

    InstructionNode* output_stmt = new InstructionNode;
    output_stmt->type = OUT;
    output_stmt->input_inst.var_index = var_addr_map[id];
    output_stmt->next = NULL;

    return output_stmt;
}

// input_stmt → input ID SEMICOLON
InstructionNode* Parser::parse_input_stmt() {
    expect(INPUT);
    string id = expect(ID).lexeme;
    expect(SEMICOLON);

    InstructionNode* input_stmt = new InstructionNode;
    input_stmt->type = IN;
    input_stmt->input_inst.var_index = var_addr_map[id];
    input_stmt->next = NULL;

    return input_stmt;
}

// while_stmt → WHILE condition body
InstructionNode* Parser::parse_while_stmt() {
    expect(WHILE);
    InstructionNode* condition = parse_condition();
    InstructionNode* body = parse_body();

    // add to end of instruction list
    condition->cjmp_inst.target = create_noop();
    condition->next = body;
    append_to_end(condition, body);

    return condition;
}

// if_stmt → IF condition body
InstructionNode* Parser::parse_if_stmt() {
    expect(IF);
    InstructionNode* condition = parse_condition();
    InstructionNode* body = parse_body();

    // create noop
    InstructionNode* noop = create_noop();

    // add to end of instruction list
    condition->cjmp_inst.target = noop;
    condition->next = body;
    append_to_end(noop, body);

    return condition;
}

// primary → ID | NUM
Token Parser::parse_primary() {
    Token token = lexer.peek(1);
    if (token.token_type == ID) {
        return expect(ID);
    }
    return expect(NUM);
}

// condition → primary relop primary
InstructionNode* Parser::parse_condition() {
    InstructionNode* condition = new InstructionNode;
    
    Token lhs = parse_primary();
    Token op = lexer.GetToken();
    Token rhs = parse_primary();

    condition->type = CJMP;

    if (op.token_type == NOTEQUAL)
        condition->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
    else if (op.token_type == GREATER)
        condition->cjmp_inst.condition_op = CONDITION_GREATER;
    else
        condition->cjmp_inst.condition_op = CONDITION_LESS; // risky

    condition->cjmp_inst.opernd1_index = get_mem(lhs);
    condition->cjmp_inst.opernd2_index = get_mem(rhs);

    return condition;
}

// switch_stmt → SWITCH ID LBRACE case_list RBRACE
// switch_stmt → SWITCH ID LBRACE case_list default_case RBRACE
InstructionNode* Parser::parse_switch_stmt() {
    expect(SWITCH);
    Token id = expect(ID);
    expect(LBRACE);
    vector<SwitchCase> cases = parse_switch_cases();
    expect(RBRACE);

    InstructionNode* end_noop = create_noop();
    InstructionNode* stmt = NULL;
    InstructionNode* tmp = NULL;

    bool has_default = false;
    for (SwitchCase c : cases) {
        if (!c.is_default) {
            InstructionNode* intermediate = new InstructionNode;
            int switch_case_mem = get_mem(c.token);
            append_to_end(end_noop, c.body);
            intermediate->type = CJMP;
            intermediate->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
            intermediate->cjmp_inst.target = c.body;
            intermediate->cjmp_inst.opernd1_index = get_mem(id);
            intermediate->cjmp_inst.opernd2_index = switch_case_mem;
            if (tmp != NULL) {
                tmp->next = intermediate;
            } else {
                stmt = intermediate;
            }
            tmp = intermediate;
        } else {
            has_default = true;
            tmp->next = c.body;
            append_to_end(end_noop, c.body);
        }
    }

    if (!has_default)
        append_to_end(end_noop, tmp);

    return stmt;
}

// case → CASE NUM COLON body
// default_case → DEFAULT COLON body
vector<SwitchCase> Parser::parse_switch_cases() {
    vector<struct SwitchCase> cases;
    Token t;

    do {
        Token token = lexer.peek(1);
        if (token.token_type == CASE) {
            expect(CASE);
            Token case_num = expect(NUM);
            expect(COLON);
            InstructionNode* body = parse_body();
            cases.push_back({ false, case_num, body });
        } else {
            expect(DEFAULT);
            expect(COLON);
            InstructionNode* body = parse_body();
            cases.push_back({ true, {}, body });
        }

        t = lexer.peek(1);
    } while (t.token_type == CASE || t.token_type == DEFAULT);

    return cases;
}

// for_stmt → FOR LPAREN assign_stmt condition SEMICOLON assign_stmt RPAREN body
InstructionNode* Parser::parse_for_stmt() {
    InstructionNode* for_stmt = new InstructionNode;

    expect(FOR);
    expect(LPAREN);

    InstructionNode* assign_1 = parse_assign_stmt();

    Token lhs = parse_primary();
    Token op = lexer.GetToken();
    Token rhs = parse_primary();

    int cmp_rhs_mem = get_mem(lhs);
    int cmp_lhs_mem = get_mem(rhs);

    expect(SEMICOLON);

    InstructionNode* assign_2 = parse_assign_stmt();
    
    expect(RPAREN);

    InstructionNode* for_body = parse_body();
    InstructionNode* cjmp_in = for_stmt;

    switch (op.token_type) {
        case NOTEQUAL:
            cjmp_in->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
            break;
        case GREATER:
            cjmp_in->cjmp_inst.condition_op = CONDITION_GREATER;
            break;
        case LESS:
            cjmp_in->cjmp_inst.condition_op = CONDITION_LESS;
            break;
    }

    cjmp_in->type = CJMP;
    cjmp_in->cjmp_inst.opernd1_index = cmp_rhs_mem;
    cjmp_in->cjmp_inst.opernd2_index = cmp_lhs_mem;
    for_stmt = assign_1;
    for_stmt->next = cjmp_in;

    append_to_end(assign_2, for_body);
    append_to_end(cjmp_in, for_body);

    cjmp_in->next = for_body;
    cjmp_in->cjmp_inst.target = create_noop();

    return for_stmt;
}

// assign_stmt → ID EQUAL primary SEMICOLON
// assign_stmt → ID EQUAL expr SEMICOLON
InstructionNode* Parser::parse_assign_stmt() {
    InstructionNode* assign_in = new InstructionNode;

    Token token_assignment = parse_primary();
    expect(EQUAL);
    Token token_lhs = parse_primary();
    Token token_operator = lexer.GetToken(); // could be operator or semicolon

    // assignments with arithmetic operations
    if (
        token_operator.token_type == PLUS ||
        token_operator.token_type == MINUS ||
        token_operator.token_type == DIV ||
        token_operator.token_type == MULT
    ) {
        Token token_rhs = parse_primary();

        int assignment_mem = get_mem(token_assignment);

        assign_in->type = ASSIGN;
        assign_in->assign_inst.left_hand_side_index = assignment_mem;
        assign_in->assign_inst.opernd1_index = get_mem(token_lhs);
        assign_in->assign_inst.opernd2_index = get_mem(token_rhs);
        switch (token_operator.token_type) {
            case PLUS:
                assign_in->assign_inst.op = OPERATOR_PLUS;
                break;
            case MINUS:
                assign_in->assign_inst.op = OPERATOR_MINUS;
                break;
            case DIV:
                assign_in->assign_inst.op = OPERATOR_DIV;
                break;
            case MULT:
                assign_in->assign_inst.op = OPERATOR_MULT;
                break;
            default:
                exit(1);
        }
        assign_in->next = NULL;
        expect(SEMICOLON);
    } else {
        assign_in->type = ASSIGN;
        assign_in->assign_inst.left_hand_side_index = get_mem(token_assignment);
        assign_in->assign_inst.opernd1_index = get_mem(token_lhs);
        assign_in->assign_inst.op = OPERATOR_NONE;
        assign_in->next = NULL;
    }

    return assign_in;
}

// inputs → num_list
void Parser::parse_inputs() {
    //vector<int> parsed_nums;
    inputs = parse_num_list(inputs);
}

// num_list → NUM
// num_list → NUM num_list
vector<int> Parser::parse_num_list(vector<int> parsed_nums) {
    Token t = expect(NUM);
    parsed_nums.push_back(stoi(t.lexeme));

    if (lexer.peek(1).token_type != END_OF_FILE) {
        return parse_num_list(parsed_nums);
    }

    return parsed_nums;
}

// helper functions
int Parser::get_mem(Token token) {
    int address;

    if (token.token_type == NUM) {
        address = current_memory_addr++;
        mem[address] = stoi(token.lexeme);
    } else {
        address = var_addr_map[token.lexeme];
    }

    return address;
}

void Parser::append_to_end(InstructionNode* in, InstructionNode*& list) {
    auto eol = list;
    while (eol->next != NULL) {
        if (eol->type == CJMP)
            eol = eol->cjmp_inst.target;
        else
            eol = eol->next;
    }
    eol->next = in;
}

InstructionNode* Parser::create_noop() {
    InstructionNode* noop = new InstructionNode;
    noop->type = NOOP;
    noop->next = NULL;
    return noop;
}

/* MAIN FUNCTION CALLED IN execute.cc */
InstructionNode* parse_generate_intermediate_representation() {
    Parser p;
    return p.parse_program();
}
