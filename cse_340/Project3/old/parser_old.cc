#include <iostream>
#include "parser.h"
#include "execute.h"

using namespace std;

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
    cout << "SYNTAX ERROR !!!\n";
    exit(1);
}

void Parser::add_var_addr(string id) {
    var_addr[id] = next_available++;
}

/* --- MAIN PARSE FUNCTIONS ---*/
// program → var section body inputs
InstructionNode* Parser::parse_program() {
    parse_var_section();
    parse_body();
    parse_inputs();
}

// var section → id list SEMICOLON
void Parser::parse_var_section() {
    parse_id_list();
    expect(SEMICOLON);
}

// id list → ID COMMA id list | ID
void Parser::parse_id_list() {
    Token t = expect(ID);
    add_var_addr(t.lexeme); // adds to map
    Token t2 = lexer.peek(1);
    if (t2.token_type == COMMA) {
        lexer.GetToken();
        return parse_id_list();
    } else if (t2.token_type == SEMICOLON)
        return;
}

// body → LBRACE stmt list RBRACE
InstructionNode* Parser::parse_body() {
    struct InstructionNode* in_begin = nullptr;
    struct InstructionNode* in_prev = nullptr;
    struct InstructionNode* in = nullptr;

    auto add_instruction = [&](struct InstructionNode * i)
    {
        if (in)
        {
            in_prev = in;
            in = i;
            in_prev->next = in;
        }
        else
        {
            in = i;
            in_begin = in;
        }

        if (i->next)
        {
            while (i->next)
            {
                if (i->type == CJMP)
                {
                    i = i->cjmp_inst.target;
                }
                else i = i->next;
            }
            in = i;
        }
    };

    // auto debug_skip_statement = [&]()
    // {
    //     std::shared_ptr<TokenBase> token;
    //     do
    //     {
    //         token = lexer.getToken();
    //     } while (token.token_type != TokenType::SEMICOLON);
    // };

    Token token = lexer.GetToken();
    if (token.token_type == LBRAC)
    {
        token = lexer.peek(1);
        // lexer.unGetToken();
        do {
            if (token.token_type == IF)
            {
                add_instruction(parse_if_stmt());
            }
            else if (token.token_type == WHILE)
            {
                add_instruction(parse_while_stmt());
            }
            else if (token.token_type == INPUT)
            {
                add_instruction(parse_input_stmt());
            }
            else if (token.token_type == OUTPUT)
            {
                add_instruction(parse_output_stmt());
            }
            else if (token.token_type == SWITCH)
            {
                add_instruction(parse_switch_stmt());
            }
            else if (token.token_type == FOR)
            {
                add_instruction(parse_for_stmt());
            }
            else
            {
                add_instruction(parse_body());
            }

            token = lexer.peek(1);
            // lexer.unGetToken();
        } while (token.token_type != RBRAC);
        token = lexer.GetToken();
    }

    return in_begin;
}

// stmt list → stmt stmt list | stmt
InstructionNode* Parser::parse_stmt_list() {

}

// stmt → assign stmt | while stmt | if stmt | switch stmt | for stmt
// stmt → output stmt | input stmt
InstructionNode* Parser::parse_stmt() {

}

// assign stmt → ID EQUAL primary SEMICOLON
// assign stmt → ID EQUAL expr SEMICOLON
InstructionNode* Parser::parse_assign_stmt() {

}

// expr → primary op primary
InstructionNode* Parser::parse_expr() {

}

// primary → ID | NUM
InstructionNode* Parser::parse_primary() {

}

// op → PLUS | MINUS | MULT | DIV
InstructionNode* Parser::parse_op() {

}

// output stmt → output ID SEMICOLON
InstructionNode* Parser::parse_output_stmt() {

}

// input stmt → input ID SEMICOLON
InstructionNode* Parser::parse_input_stmt() {

}

// while stmt → WHILE condition body
InstructionNode* Parser::parse_while_stmt() {

}

// if stmt → IF condition body
InstructionNode* Parser::parse_if_stmt() {

}

// condition → primary relop primary
InstructionNode* Parser::parse_condition() {

}

// relop → GREATER | LESS | NOTEQUAL
InstructionNode* Parser::parse_relop() {

}

// switch stmt → SWITCH ID LBRACE case list RBRACE
// switch stmt → SWITCH ID LBRACE case list default case RBRACE
InstructionNode* Parser::parse_switch_stmt() {

}

// for stmt → FOR LPAREN assign stmt condition SEMICOLON assign stmt RPAREN body
InstructionNode* Parser::parse_for_stmt() {

}

// case list → case case list | case
InstructionNode* Parser::parse_case_list() {

}

// case → CASE NUM COLON body
InstructionNode* Parser::parse_case() {

}

// default case → DEFAULT COLON body
InstructionNode* Parser::parse_default_case() {

}

// inputs → num list
InstructionNode* Parser::parse_inputs() {
    parse_num_list();
}

// num list → NUM
// num list → NUM num list
void Parser::parse_num_list() {
    Token t = expect(NUM);
    inputs.push_back(stoi(t.lexeme));

    Token t2 = lexer.peek(1);
    if (t2.token_type == NUM)
        parse_num_list();
    else if (t2.token_type == EOF)
        return;
}
/* --- MAIN PARSE FUNCTIONS ---*/



/* --- MAIN FUNCTION --- */
struct InstructionNode * parse_generate_intermediate_representation() {
    Parser p;
    return p.parse_program();
}
