/*
 * CSE 340 Project 1 - parser.cc
 * Tyler Fichiera
 */
#include <iostream>
#include <cstdlib>

#include "lexer.h"
#include "parser.h"

using namespace std;

// this function gets a token and checks if it is
// of the expected type. If it is, the token is
// returned, otherwise, synatx_error() is generated
// this function is particularly useful to match
// terminals in a right hand side of a rule.
// Written by Mohsen Zohrevandi
Token Parser::expect(TokenType expected_type, bool from_regexp = false) {
    Token t = lexer.GetToken();
    if (t.token_type != expected_type) {
        if (from_regexp)
            throw string("PARSING_SYNTAX_ERROR");
        cout << "SNYTAX ERORR" << endl;
        exit(1);
    }
    return t;
}

// parse the expression non-terminal based on the lang in the pdf
REG* Parser::parse_expr()
{
    Token t = lexer.GetToken();

    if (t.token_type == CHAR) {
        // expr -> CHAR
        REG* r1 = new REG();

        REG_node* startNode = new REG_node();
        REG_node* acceptNode = new REG_node();

        startNode->id = myLexer.getCounter();
        acceptNode->id = myLexer.getCounter();

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

        startNode->id = myLexer.getCounter();
        acceptNode->id = myLexer.getCounter();

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

            startNode->id = myLexer.getCounter();
            acceptNode->id = myLexer.getCounter();

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

            startNode->id = myLexer.getCounter();
            acceptNode->id = myLexer.getCounter();

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

            startNode->id = myLexer.getCounter();
            acceptNode->id = myLexer.getCounter();

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

// parse the token non-terminal based on the lang in the pdf
void Parser::parse_token()
{
    Token t = expect(ID);

    // check if token is already defined
    // if so, throw error and exit
    for (TokenREG tmp : myLexer.token_reg_list) {
        if (t.lexeme.compare(tmp.token_name) == 0) {
            this->hasSemanticError = true;
            cout << "Line " << t.line_no << ": " << t.lexeme << " already declared on line " << tmp.token_line_no << endl;
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

    myLexer.token_reg_list.push_back(*tokenReg);
}

// parse the token list non-terminal based on the lang in the pdf
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
        cout << "SNYTAX ERORR" << endl;
        exit(1);
    }
}

// parse the token section non-terminal based on the lang in the pdf
void Parser::parse_tokens_section()
{
    this->hasSemanticError = false;
    parse_token_list();

    if (this->hasSemanticError) exit(1);

    expect(HASH);
}

// parse the input non-terminal based on the lang in the pdf
void Parser::parse_input()
{
    parse_tokens_section();
    Token t = expect(INPUT_TEXT);
    std::string temp = t.lexeme.substr(1, t.lexeme.size() - 2);
    if(temp.at(0) == ' '){
        temp = temp.substr(1, temp.size());
    }
    if(temp.at(temp.size() - 1) == ' '){
        temp = temp.substr(0, temp.size() - 1);
    }

    myLexer.setInputStr(temp);
}

// main parse function called by main
void Parser::parse_Input()
{
    parse_input();
    expect(END_OF_FILE);

    myLexer.checkEpsilonErrors();

    if (myLexer.epsilonErrors.size() > 0) {
        cout << "EPSILON IS NOOOOOOOT A TOKEN !!!";
        for (string ee : myLexer.epsilonErrors) {
            cout << " " << ee;
        }
        cout << endl;
        exit(1);
    }

    myLexer.MyGetToken();
}

int main() {
    Parser parser;
    parser.parse_Input();
}
