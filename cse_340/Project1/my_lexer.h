/*
 * CSE 340 Project 1 - my_lexer.h
 * Tyler Fichiera
 */
#ifndef __MY__LEXER__H__
#define __MY__LEXER__H__

#include <vector>
#include <string>
#include <set>

#include "lexer.h"
#include "structs.h"

using namespace std;

static bool operator<(const REG_node& nodeA, const REG_node& nodeB) { return nodeA.id < nodeB.id; }

class MyLexicalAnalyzer {
    public:
        // public vars
        vector<TokenREG> token_reg_list;
        string input_str;
        vector<Token> tokenList;
        vector<string> epsilonErrors;

        // main analyzer function called by parser
        void MyGetToken();

        // main functions for doing analysis
        int match(REG* r, string s, int p);
        set<REG_node> matchOneChar(set<REG_node> s, char c);
        
        // check for epsilon errors before doing lexical
        void checkEpsilonErrors();

        // support methods for match and matchOneChar
        bool isValidNode(set<REG_node> s, REG_node* r);
        bool compareNodeSets(set<REG_node> S1, set<REG_node> S2);

        // getters / setters
        int getCounter();
        void setInputStr(string);

    private:
        // private id to keep track of id used for REG_nodes
        int idCounter;
};

#endif  //__MY__LEXER__H__