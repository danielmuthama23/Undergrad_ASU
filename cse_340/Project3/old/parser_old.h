#include <iostream>
#include <vector>
#include <map>
#include "execute.h"
#include "lexer.h"

using namespace std;

class Parser {
    public:
    LexicalAnalyzer lexer;

    // key = variable name, value = variable address #
    map<string, int> var_addr;

    TokenType peek(int);
    Token expect(TokenType);
    void syntax_error();

    void add_var_addr(string);

    // MAIN PARSERS
    InstructionNode* parse_program();
    void parse_var_section();
    void parse_id_list();
    InstructionNode* parse_body();
    InstructionNode* parse_stmt_list();
    InstructionNode* parse_stmt();
    InstructionNode* parse_assign_stmt();
    InstructionNode* parse_expr();
    InstructionNode* parse_primary();
    InstructionNode* parse_op();
    InstructionNode* parse_output_stmt();
    InstructionNode* parse_input_stmt();
    InstructionNode* parse_while_stmt();
    InstructionNode* parse_if_stmt();
    InstructionNode* parse_condition();
    InstructionNode* parse_relop();
    InstructionNode* parse_switch_stmt();
    InstructionNode* parse_for_stmt();
    InstructionNode* parse_case_list();
    InstructionNode* parse_case();
    InstructionNode* parse_default_case();
    InstructionNode* parse_inputs();
    void parse_num_list();

    Parser() {}
};
