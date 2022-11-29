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
        var_addr_map[id] = get_current_memory_addr();
    }
}

// id_list → ID COMMA id_list | ID
vector<string> Parser::parse_id_list(vector<string> parsed_ids) {
    Token t = expect(ID);
    parsed_ids.push_back(t.lexeme);

    // TokenType t2 = peek(1);
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
    InstructionNode * stmt_list = nullptr;
    InstructionNode * stmt_head = nullptr;

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

    InstructionNode* while_node = new InstructionNode;
    InstructionIntermediateData IID;

    InstructionData lhs = compute_IID(IID.token_lhs_data);
    Token op = lexer.GetToken();
    InstructionData rhs = compute_IID(IID.token_rhs_data);

    while_node->type = CJMP;
    sortOutCJMPOperator(while_node, op.token_type);

    while_node->cjmp_inst.opernd1_index = getMemoryAddress(lhs);
    while_node->cjmp_inst.opernd2_index = getMemoryAddress(rhs);

    InstructionNode* while_body = parse_body();

    InstructionNode* noop = new InstructionNode;
    noop->type = NOOP;
    noop->next = NULL;

    while_node->cjmp_inst.target = noop;
    while_node->next = while_body;

    // Find end of IF_WHILE
    addInstructionToEndOfInstructionList(while_node, while_body);

    return while_node;
}

// if_stmt → IF condition body
InstructionNode* Parser::parse_if_stmt() {
    struct InstructionNode * IN_IF = new InstructionNode{};

    expect(IF);

    InstructionIntermediateData IID;

    auto lhs = compute_IID(IID.token_lhs_data);
    auto op = lexer.GetToken();
    auto rhs = compute_IID(IID.token_rhs_data);

    IN_IF->type = CJMP;
    sortOutCJMPOperator(IN_IF, op.token_type);

    IN_IF->cjmp_inst.opernd1_index = getMemoryAddress(lhs);
    IN_IF->cjmp_inst.opernd2_index = getMemoryAddress(rhs);
    auto if_body = parse_body();

    struct InstructionNode * IN_NOOP = new InstructionNode{};
    IN_NOOP->type = NOOP;
    IN_NOOP->next = nullptr;

    IN_IF->cjmp_inst.target = IN_NOOP;                      
    IN_IF->next = if_body;

    // Find end of IF_BODY
    addInstructionToEndOfInstructionList(IN_NOOP, if_body);

    return IN_IF;
}

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
    
    Token rhs = parse_primary();
}

// switch_stmt → SWITCH ID LBRACE case_list RBRACE
// switch_stmt → SWITCH ID LBRACE case_list default_case RBRACE
InstructionNode* Parser::parse_switch_stmt() {
    InstructionIntermediateData IID;

    auto token = lexer.GetToken();
    if (token.token_type != SWITCH)
        assert(false);

    auto switch_var = compute_IID(IID.token_assignment_data);
    int switch_var_mem = getMemoryAddress(switch_var);

    token = lexer.GetToken();
    if (token.token_type != LBRACE)
        assert(false);

    auto cases = parse_switch_cases();

    token = lexer.GetToken();
    if (token.token_type != RBRACE)
        assert(false);

    // This is the escape noop
    struct InstructionNode * IN_END_NOOP = new InstructionNode{};
    IN_END_NOOP->type = NOOP;
    IN_END_NOOP->next = nullptr;
    
    bool default_found = false;
    struct InstructionNode * BEGIN_IN = nullptr;
    struct InstructionNode * PREV_IN = nullptr;
    for (auto & v : cases)
    {
        switch (v.Type)
        {
        case SwitchCaseType::CASE:
        {
            struct InstructionNode * IN_IF = new InstructionNode{};
            int switch_case_mem = getMemoryAddress(v.CaseNum);
            addInstructionToEndOfInstructionList(IN_END_NOOP, v.Body);
            IN_IF->type = CJMP;
            IN_IF->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
            IN_IF->cjmp_inst.target = v.Body;
            IN_IF->cjmp_inst.opernd1_index = switch_var_mem;
            IN_IF->cjmp_inst.opernd2_index = switch_case_mem;
            if (PREV_IN)
            {
                PREV_IN->next = IN_IF;
            }
            else BEGIN_IN = IN_IF;
            PREV_IN = IN_IF;
            break;
        }
        case SwitchCaseType::DEFAULT:
            PREV_IN->next = v.Body;
            addInstructionToEndOfInstructionList(IN_END_NOOP, v.Body);
            default_found = true;
            break;
        }  
    }

    if (!default_found)
    {
        addInstructionToEndOfInstructionList(IN_END_NOOP, PREV_IN);
    }

    return BEGIN_IN;
}

vector<SwitchIntermediateData> Parser::parse_switch_cases() {
    InstructionIntermediateData IID;
    std::vector<struct SwitchIntermediateData> Cases;
    Token token;

    do
    {
        token = lexer.GetToken();
        switch (token.token_type) {
        case CASE:
        {
            auto switch_case_num = compute_IID(IID.token_assignment_data);
            lexer.GetToken(); // ignore :
            auto case_body = parse_body();
            Cases.push_back({ SwitchCaseType::CASE, switch_case_num , case_body });
            break;
        }
        case DEFAULT:
        {
            lexer.GetToken(); // ignore :
            auto default_body = parse_body(); // ignore body.
            Cases.push_back({ SwitchCaseType::DEFAULT, {}, default_body });
            break;
        }
        default:
            assert(false);
        }

        token = lexer.peek(1);
    } while (token.token_type == CASE || token.token_type == DEFAULT);

    return Cases;
}

// for_stmt → FOR LPAREN assign_stmt condition SEMICOLON assign_stmt RPAREN body
InstructionNode* Parser::parse_for_stmt() {
    struct InstructionNode * IN_FOR = new InstructionNode{};

    auto token = lexer.GetToken();

    if (token.token_type != FOR)
        assert(false);

    InstructionIntermediateData IID;
    token = lexer.GetToken();

    if (token.token_type != LPAREN)
        assert(false);

    auto assignment1 = parse_assign_stmt();
    auto cmp_lhs = compute_IID(IID.token_lhs_data);
    auto cmp_op = lexer.GetToken();
    auto cmp_rhs = compute_IID(IID.token_rhs_data);
    int cmp_rhs_mem = getMemoryAddress(cmp_lhs);
    int cmp_lhs_mem = getMemoryAddress(cmp_rhs);
    token = lexer.GetToken(); // ignore ;
    auto assignment2 = parse_assign_stmt();
    token = lexer.GetToken();

    if (token.token_type != RPAREN)
        assert(false);

    struct InstructionNode * IN_NOOP = new InstructionNode{};
    IN_NOOP->type = NOOP;
    IN_NOOP->next = nullptr;

    auto for_instructions = parse_body();

    auto cjmp_i = IN_FOR;
    IN_FOR = assignment1;
    IN_FOR->next = cjmp_i;

    cjmp_i->type = CJMP;
    sortOutCJMPOperator(cjmp_i, cmp_op.token_type);
    cjmp_i->cjmp_inst.opernd1_index = cmp_rhs_mem;
    cjmp_i->cjmp_inst.opernd2_index = cmp_lhs_mem;

    addInstructionToEndOfInstructionList(assignment2, for_instructions);
    addInstructionToEndOfInstructionList(cjmp_i, for_instructions);

    cjmp_i->next = for_instructions;
    cjmp_i->cjmp_inst.target = IN_NOOP;

    return IN_FOR;
}

InstructionNode* Parser::parse_assign_stmt() {
    struct InstructionNode * IN = new InstructionNode{};
    InstructionIntermediateData IID;

    auto token_assignment = compute_IID(IID.token_assignment_data);
    auto token_equals = lexer.GetToken();
    auto token_lhs = compute_IID(IID.token_lhs_data);
    auto token_operator = lexer.GetToken();

    if (token_operator.token_type == PLUS ||
        token_operator.token_type == MINUS ||
        token_operator.token_type ==  DIV ||
        token_operator.token_type == MULT )
    {
        // Assignment with math a = b + c, a = b - c, a = b * c, a = b / c
        auto token_rhs = compute_IID(IID.token_rhs_data);

        // Compute memory
        int assignment_mem = getMemoryAddress(token_assignment);
        int rhs_mem = getMemoryAddress(token_lhs);
        int lhs_mem = getMemoryAddress(token_rhs);

        IN->type = ASSIGN;
        IN->assign_inst.left_hand_side_index = assignment_mem;
        IN->assign_inst.opernd1_index = rhs_mem;
        IN->assign_inst.opernd2_index = lhs_mem;
        switch (token_operator.token_type)
        {
        case PLUS:
            IN->assign_inst.op = OPERATOR_PLUS;
            break;
        case MINUS:
            IN->assign_inst.op = OPERATOR_MINUS;
            break;
        case DIV:
            IN->assign_inst.op = OPERATOR_DIV;
            break;
        case MULT:
            IN->assign_inst.op = OPERATOR_MULT;
            break;
        default:
            assert(false);
        }
        IN->next = nullptr;
        lexer.GetToken(); // Ignore ;
    }
    else
    {
        int lhs_mem = getMemoryAddress(token_assignment);
        int rhs_mem = getMemoryAddress(token_lhs);

        IN->type = ASSIGN;
        IN->assign_inst.left_hand_side_index = lhs_mem;
        IN->assign_inst.op = OPERATOR_NONE;
        IN->assign_inst.opernd1_index = rhs_mem;
        IN->next = nullptr;
    }
    return IN;
}

int Parser::get_current_memory_addr() {
    return current_memory_addr++;
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
int Parser::getMemoryAddress(const InstructionData & ID)
{
    int address = -1;

    if (ID.token.token_type == NUM)
    {
        address = get_current_memory_addr();
        mem[address] = ID.int_data;
    }
    else
    {
        address = var_addr_map[ID.str_data];
    }
    return address;
}

InstructionData& Parser::compute_IID(InstructionData & ID) {
    Token token = lexer.GetToken();

    ID.token = token;
    if (token.token_type == NUM) {
        ID.int_data = stoi(token.lexeme);
    } else {
        ID.str_data = token.lexeme;
    }

    return ID;
}

void Parser::addInstructionToEndOfInstructionList(InstructionNode * I, InstructionNode *& list) {
    auto if_body_end = list;
    while (if_body_end->next) {
        if (if_body_end->type == CJMP) {
            if_body_end = if_body_end->cjmp_inst.target;
        }
        else if_body_end = if_body_end->next;
    }
    if_body_end->next = I;
}

void Parser::sortOutCJMPOperator(InstructionNode * I, TokenType TT) {
    switch (TT) {
    case NOTEQUAL:
        I->cjmp_inst.condition_op = CONDITION_NOTEQUAL;
        break;
    case GREATER:
        I->cjmp_inst.condition_op = CONDITION_GREATER;
        break;
    case LESS:
        I->cjmp_inst.condition_op = CONDITION_LESS;
        break;
    };
}

/* MAIN FUNCTION CALLED IN execute.cc */
InstructionNode* parse_generate_intermediate_representation() {
    Parser p;
    return p.parse_program();
}
