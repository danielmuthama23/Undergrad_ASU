/*
 * CSE 340 Project 1 - my_lexer.cc
 * Tyler Fichiera
 */
#include <iostream>
#include <istream>
#include <vector>
#include <string>
#include <cctype>
#include <sstream>
#include <set>
#include <algorithm>

#include "my_lexer.h"
#include "inputbuf.h"
#include "structs.h"

using namespace std;

// setter for input_str
void MyLexicalAnalyzer::setInputStr(string in) {
    this->input_str = in;
}

// main function used for lexical analysis
void MyLexicalAnalyzer::MyGetToken() {
    int start = 0; // position
    string lex = ""; // current token match

    // split input into a list of strings based on ' '
    vector<string> inputSplit;
    stringstream ss(input_str);
    string s;

    // go through all inputs
    while (getline(ss, s, ' ')) {
        start = 0;
        while (start != s.size()) {
            int max = 0;
            vector<TokenREG> tokens = token_reg_list;
            for (TokenREG tr : token_reg_list) {
                int lex_size = match(tr.reg_pointer, s, start);

                // find the longest lex
                if (lex_size > max) {
                    max = lex_size;
                    lex = tr.token_name;
                }
            }
            if (max == 0) {
                cout << "ERROR";
                return;
            }
            cout << lex << " , \"" << s.substr(start, max) << "\"" << endl;
            start += max;
        }
    }
}

// check for epsilon errors
void MyLexicalAnalyzer::checkEpsilonErrors() {
    // iterate through and if '_' (epsilon) matched
    // then add the token name to list to be printed
    // out later
    for (TokenREG tr : token_reg_list) {
        int lex_size = match(tr.reg_pointer, "_", 0);
        if (lex_size > 0)
            epsilonErrors.push_back(tr.token_name);
    }
}

// main match method as described in the pdf
int MyLexicalAnalyzer::match(REG* r, string s, int p){
    set<REG_node> s1;
    s1.insert(*r->start);

    set<REG_node> s2 = matchOneChar(s1, '_');

    // swap and insert
    s2.insert(s1.begin(), s1.end());
    s1.insert(s2.begin(), s2.end());

    int size = 0, len = 0;
    for (string::iterator it = s.begin() + p, end = s.end(); it != end; ++it) {
        size ++;

        s1 = matchOneChar(s1, *it);

        if(s1.find(*r->accept) != s1.end())
            len = size;
    }

    return len;
}

// match one character to a set as described in the pdf
set<REG_node> MyLexicalAnalyzer::matchOneChar(set<REG_node> s, char c) {
    set<REG_node> s1;
    set<REG_node> s2;

    //  find all nodes that can be reached from s by consuming c
    for (set<REG_node>::iterator it = s.begin(); it != s.end(); ++it) {
        if (it->first_label == c && !isValidNode(s1, it->first_neighbor)) {
            s1.insert(*it->first_neighbor);
        }
        if (it->second_label == c && !isValidNode(s1, it->second_neighbor)) {
            s1.insert(*it->second_neighbor);
        }
    }

    if (s1.empty()) {
        return s1;
    }

    // at this point, s1 is not empty and it contains nodes
    // that can be reached from s

    // find all nodes that can be reached from the resulting
    // set S' by consuming no input
    bool changed = true;
    while (changed) {
        changed = false;
        for (set<REG_node>::iterator it = s1.begin(); it != s1.end(); ++it) {
            s2.insert(*it);

            if(it->first_label == '_' && !isValidNode(s2, it->first_neighbor)){
                s2.insert(*it->first_neighbor);
            }
            if(it->second_label == '_' && !isValidNode(s2, it->second_neighbor)){
                s2.insert(*it->second_neighbor);
            }
        }
        if (!compareNodeSets(s1, s2)) {
            changed = true;
            s1.insert(s2.begin(), s2.end());
            set<REG_node> emptySet;
            s2 = emptySet;
        }
    }

    return s1;
}

// helper method for match one char
bool MyLexicalAnalyzer::isValidNode(set<REG_node> s, REG_node* r) {
    for (REG_node r1 : s) {
        if (r1.id == r->id)
            return true;
    }
    return false;
}

// getter to keep track of id for each reg node
int MyLexicalAnalyzer::getCounter() {
    idCounter++;
    return idCounter;
}

// compare the two vectors based on each elements id field
bool MyLexicalAnalyzer::compareNodeSets(set<REG_node> s1, set<REG_node> s2) {
    if (s1.size() != s2.size())
        return false;

    // add ids to their own int arrays
    int s1Ids[s1.size()];
    int s2Ids[s2.size()];
    int s1i = 0;
    int s2i = 0;

    for (REG_node r1 : s1) {
        s1Ids[s1i] = r1.id;
        s1i++;
    }

    for (REG_node r2 : s2) {
        s2Ids[s2i] = r2.id;
        s2i++;
    }

    // sort to prevent out of order issues
    sort(s1Ids, s1Ids + s1i);
    sort(s2Ids, s2Ids + s2i);

    // check to make sure they're the same
    for (int i = 0; i < s1i; i++) {
        if (s1Ids[i] != s2Ids[i])
            return false;
    }

    return true;
}
