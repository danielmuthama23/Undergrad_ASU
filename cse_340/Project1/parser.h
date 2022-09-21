/*
 * Copyright (C) Rida Bazzi, 2019
 *
 * Do not share this file with anyone
 */
#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include "lexer.h"

struct REG_node {
  struct REG_node* first_neighbor;
  char first_label;
  struct REG_node* second_neighbor;
  char second_label;
};

struct REG {
  struct REG_node* start;
  struct REG_node* accept;
};

class Parser {
  public:
    void parse_input();
    void parse_Input();
    void readAndPrintAllInput();
  private:
    LexicalAnalyzer lexer;
    Token expect(TokenType expected_type, bool from_regexp);
    void parse_tokens_section();
    void parse_token_list();
    void parse_token();
    REG* parse_expr();
    bool isEpsilonToken(REG*);
};

#endif
