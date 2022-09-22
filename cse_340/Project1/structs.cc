/*
 * CSE 340 Project 1 - structs.cc
 * Tyler Fichiera
 */
#include <iostream>
#include <cstdlib>

#include "structs.h"

using namespace std;

string reserved[] = { "END_OF_FILE",
    "LPAREN", "RPAREN", "HASH", "ID", "COMMA", "DOT", "STAR",
    "OR", "UNDERSCORE", "SYMBOL", "CHAR", "INPUT_TEXT", "ERROR"};

// print the token in correct format
void Token::Print() {
    cout << "{" << this->lexeme << " , "
         << reserved[(int) this->token_type] << " , "
         << this->line_no << "}\n";
}
