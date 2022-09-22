/*
 * CSE 340 Project 1 - lexer.h
 * Tyler Fichiera
 */
#ifndef __LEXER__H__
#define __LEXER__H__

#include <vector>
#include <string>

#include "inputbuf.h"
#include "structs.h"

class LexicalAnalyzer {
  public:
    Token GetToken();
    Token peek(int);
    LexicalAnalyzer();

  private:
    std::vector<Token> tokenList;
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

#endif  //__LEXER__H__
