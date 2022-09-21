/*
 * Copyright (C) Rida Bazzi, 2019
 *
 * Do not share this file with anyone
 */
#ifndef __LEXER__H__
#define __LEXER__H__

#include <vector>
#include <string>

#include "inputbuf.h"

using namespace std;

struct REG; // forward declaration to prevent circular
            // dependency error

// ------- token types -------------------

typedef enum { END_OF_FILE = 0,
    LPAREN, RPAREN, HASH, ID, COMMA, DOT, STAR,
    OR, UNDERSCORE, SYMBOL, CHAR, INPUT_TEXT, ERROR
    } TokenType;

struct TokenREG {
  string token_name;
  int token_line_no;
  REG* reg_pointer;
};

class Token {
  public:
    void Print();

    string lexeme;
    TokenType token_type;
    int line_no;
};

class LexicalAnalyzer {
  public:
    Token GetToken();
    Token UngetToken();
    Token peek(int);
    LexicalAnalyzer();

    vector<TokenREG*> token_reg_list;
    string input_str;
    int p; // current position next character in the input str
    // my_LexicalAnalyzer(vector<TokenREG> list, string s);
    string match(REG r, string s, int p);
    Token my_GetToken();

  private:
    vector<Token> tokenList;
    Token GetTokenMain();
    int line_no;
    int index;
    Token tmp;
    InputBuffer input;

    bool SkipSpace();
    Token ScanIdOrChar();
    Token ScanSymbol();
    Token ScanInput();
};

// class my_LexicalAnalyzer {
//   public:
//     vector<TokenREG> token_reg_list;
//     string input_str;
//     int p; // current position next character in the input str
//     my_LexicalAnalyzer(vector<TokenREG> list, string s);
//     string match(REG r, string s, int p);
//     Token my_GetToken();
// };

#endif  //__LEXER__H__
