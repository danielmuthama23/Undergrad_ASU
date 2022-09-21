/*
 * Copyright (C) Rida Bazzi, 2020
 *
 * Do not share this file with anyone
 *
 * Do not post this file or derivatives of
 * of this file online
 *
 */
#include <iostream>
#include <cstdlib>

#include "parser.h"

using namespace std;

// void Parser::syntax_error()
// {
//     cout << "SYNTAX ERROR\n";
//     exit(1);
// }

// this function gets a token and checks if it is
// of the expected type. If it is, the token is
// returned, otherwise, synatx_error() is generated
// this function is particularly useful to match
// terminals in a right hand side of a rule.
// Written by Mohsen Zohrevandi
Token Parser::expect(TokenType expected_type, bool from_regexp = false)
{
    Token t = lexer.GetToken();
    if (t.token_type != expected_type) {
        if (from_regexp)
            throw string("PARSING_SYNTAX_ERROR");
        cout << "SYNTAX ERROR" << endl;
        exit(1);
    }
    return t;
}

bool Parser::isEpsilonToken(REG* reg) {
    return true;
}

REG* Parser::parse_expr()
{
    Token t = lexer.GetToken();
    // t.Print();

    if (t.token_type == CHAR) {
        // expr -> CHAR
        REG* r1 = new REG();

        REG_node* startNode = new REG_node();
        REG_node* acceptNode = new REG_node();

        startNode->first_label = *t.lexeme.c_str();
        startNode->first_neighbor = acceptNode;

        r1->start = startNode;
        r1->accept = acceptNode;

        return r1;
    } else if (t.token_type == UNDERSCORE) {
        // expr -> UNDERSCORE
        REG* r1 = new REG();

        REG_node* startNode = new REG_node();
        REG_node* acceptNode = new REG_node();

        startNode->first_label = '_';
        startNode->first_neighbor = acceptNode;

        r1->start = startNode;
        r1->accept = acceptNode;

        return r1;
    } else if (t.token_type == LPAREN) {
        // handle all three expr that start with LPAREN
        REG* r1 = parse_expr();
        expect(RPAREN, true);

        Token t2 = lexer.GetToken();

        if (t2.token_type == DOT) {
            // expr -> LPAREN expr RPAREN DOT LPAREN expr RPAREN
            expect(LPAREN, true);
            REG* r2 = parse_expr();
            expect(RPAREN, true);

            REG* mainReg = new REG();

            // follow data structure on page 12 of project guide
            REG_node* startNode = new REG_node();
            REG_node* acceptNode = new REG_node();

            startNode = r1->start;

            r1->accept->first_label = '_';
            r1->accept->first_neighbor = r2->start;

            /* Reset accepting state to r2 accepting */
            acceptNode = r2->accept;

            // create mainReg to return
            mainReg->start = startNode;
            mainReg->accept = acceptNode;

            return mainReg;
        } else if (t2.token_type == OR) {
            // expr -> LPAREN expr RPAREN OR LPAREN expr RPAREN
            expect(LPAREN, true);
            REG* r2 = parse_expr();
            expect(RPAREN, true);

            REG* mainReg = new REG();

            REG_node* startNode = new REG_node();
            REG_node* acceptNode = new REG_node();

            // point to both r1 and r2
            startNode->first_label = '_';
            startNode->second_label = '_';
            startNode->first_neighbor = r1->start;
            startNode->second_neighbor = r2->start;

            // point to accepting state
            r1->accept->first_label = '_';
            r1->accept->first_neighbor = acceptNode;
            r2->accept->first_label = '_';
            r2->accept->first_neighbor = acceptNode;

            // create mainReg to return
            mainReg->start = startNode;
            mainReg->accept = acceptNode;

            return mainReg;
        } else if (t2.token_type == STAR) {
            // expr -> LPAREN expr RPAREN STAR
            REG* mainReg = new REG();

            REG_node* startNode = new REG_node();
            REG_node* acceptNode = new REG_node();

            // allow there to be no elements (epsilon)
            startNode->second_label = '_';
            startNode->second_neighbor = acceptNode;
            // allow there to be infinite elements
            startNode->first_label = '_';
            startNode->first_neighbor = r1->start;

            // allow "recursion"
            r1->accept->first_label = '_';
            r1->accept->first_neighbor = r1->start;

            r1->accept->second_label = '_';
            r1->accept->second_neighbor = acceptNode;

            // create mainReg to return
            mainReg->accept = acceptNode;
            mainReg->start = startNode;

            return mainReg;
        } else {
            throw string("PARSING_SYNTAX_ERROR");
        }
    } else {
        throw string("PARSING_SYNTAX_ERROR");
    }
}

void Parser::parse_token()
{
    Token t = expect(ID);

    // check if token is already defined
    // if so, throw error and exit
    for (TokenREG* tmp : lexer.token_reg_list) {
        if (t.lexeme.compare(tmp->token_name) == 0) {
            cout << "Line " << t.line_no << ": " << t.lexeme << " already declared on line " << tmp->token_line_no << endl;
            break;
        }
    }

    REG* reg;
    try {
        reg = parse_expr();
    } catch (string s) {
        cout << "SYNTAX ERROR IN EXPRESSION OF " << t.lexeme << endl;
        exit(1);
    }

    TokenREG* tokenReg = new TokenREG();
    tokenReg->token_name = t.lexeme;
    tokenReg->token_line_no = t.line_no;
    tokenReg->reg_pointer = reg;

    lexer.token_reg_list.push_back(tokenReg);
}

void Parser::parse_token_list()
{
    parse_token();

    Token t = lexer.peek(1);

    if (t.token_type == HASH) {
        // cout << "herehash1" << endl;
        return; // end of tokens
    } else if (t.token_type == COMMA) {
        expect(COMMA);
        parse_token_list(); // recursive call back
    } else {
        // syntax_error(); // 
        cout << "SYNTAX ERROR" << endl;
        exit(1);
    }
}

void Parser::parse_tokens_section()
{
    parse_token_list();
    expect(HASH);
}

void Parser::parse_input()
{
    parse_tokens_section();
    expect(INPUT_TEXT);
}

void Parser::parse_Input()
{
    parse_input();
    expect(END_OF_FILE);
    // TODO: call lexer.my_getToken
}

// This function simply reads and prints all tokens
// I included it as an example. You should compile the provided code
// as it is and then run ./a.out < tests/test0.txt to see what this function does

void Parser::readAndPrintAllInput()
{
    Token t;

    // get a token
    t = lexer.GetToken();

    // while end of input is not reached
    while (t.token_type != END_OF_FILE) 
    {
        t.Print();         	// pringt token
        t = lexer.GetToken();	// and get another one
    }
        
    // note that you should use END_OF_FILE and not EOF
}

int main()
{
    // note: the parser class has a lexer object instantiated in it (see file
    // parser.h). You should not be declaring a separate lexer object. 
    // You can access the lexer object in the parser functions as shown in 
    // the example  method Parser::readAndPrintAllInput()
    // If you declare another lexer object, lexical analysis will 
    // not work correctly
    Parser parser;

    parser.parse_Input();
    // parser.readAndPrintAllInput();
}
