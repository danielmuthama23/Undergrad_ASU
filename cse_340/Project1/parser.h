/*
 * CSE 340 Project 1 - parser.h
 * Tyler Fichiera
 */
#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>

#include "lexer.h"
#include "my_lexer.h"
#include "structs.h"

class Parser {
  public:
    bool hasSemanticError; // value to check if we need to display err msg
    void parse_input();
    void parse_Input();
  private:
    LexicalAnalyzer lexer;
    MyLexicalAnalyzer myLexer;
    Token expect(TokenType expected_type, bool from_regexp);
    void parse_tokens_section();
    void parse_token_list();
    void parse_token();
    REG* parse_expr();
};

#endif
