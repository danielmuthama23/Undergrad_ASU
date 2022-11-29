#include "lexer.h"
#include "execute.h"
#include <map>
#include <vector>

using namespace std;

struct SwitchCase {
    bool is_default;
    Token token;
    InstructionNode* body;
};

class Parser {
    public:
        // entry point
        InstructionNode* parse_program();
    private:
        LexicalAnalyzer lexer;
        map<string, int> var_addr_map; // key = var (string), value = addr (int)
        int current_memory_addr = 0;

        // header and footer (vars and inputs) parsers
        void parse_var_section();
        vector<string> parse_id_list(vector<string>);
        void parse_inputs();
        vector<int> parse_num_list(vector<int>);

        // main parse functions
        InstructionNode* parse_body();
        InstructionNode* parse_stmt_list();
        InstructionNode* parse_assign_stmt();
        InstructionNode* parse_output_stmt();
        InstructionNode* parse_input_stmt();
        InstructionNode* parse_while_stmt(); // needs some work
        InstructionNode* parse_if_stmt();
        InstructionNode* parse_switch_stmt();
        InstructionNode* parse_for_stmt();
        InstructionNode* parse_condition();

        Token parse_primary();
        vector<SwitchCase> parse_switch_cases();

        // helper functions
        int get_mem(Token);
        void append_to_end(InstructionNode*, InstructionNode*&);
        InstructionNode* create_noop();

        Token expect(TokenType);
};
