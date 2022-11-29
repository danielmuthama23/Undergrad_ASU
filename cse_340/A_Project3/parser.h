#include "lexer.h"
#include "execute.h"
#include <map>
#include <vector>

using namespace std;

/* maybe delete later */
struct InstructionData
{
    Token                         token;
    std::string                 str_data;
    int                         int_data;
};

struct InstructionIntermediateData
{
    InstructionData token_assignment_data;
    InstructionData token_lhs_data;
    InstructionData token_rhs_data;
};

enum class SwitchCaseType
{
    CASE,
    DEFAULT
};

struct SwitchIntermediateData
{
    SwitchCaseType              Type;
    InstructionData             CaseNum;
    struct InstructionNode *    Body;
};
/* maybe delete later */

class Parser {
    public:
        InstructionNode* parse_program();
    private:
        LexicalAnalyzer lexer;
        map<string, int> var_addr_map; // key = var (string), value = addr (int)
        int current_memory_addr = 0;

        // parse functions
        void parse_var_section();
        vector<string> parse_id_list(vector<string>);
        InstructionNode* parse_body();
        InstructionNode* parse_stmt_list();
        InstructionNode* parse_assign_stmt();
        InstructionNode* parse_output_stmt();
        InstructionNode* parse_input_stmt();
        InstructionNode* parse_while_stmt(); // needs some work
        InstructionNode* parse_if_stmt();
        InstructionNode* parse_switch_stmt();
        InstructionNode* parse_for_stmt();

        Token parse_primary();
        InstructionNode* parse_condition();
        vector<SwitchIntermediateData> parse_switch_cases();

        // ?
        //InstructionNode* parse_instruction();
        int get_current_memory_addr();
        
        void parse_inputs();
        vector<int> parse_num_list(vector<int>);

        // helper functions
        int getMemoryAddress(const InstructionData&);
        InstructionData& compute_IID(InstructionData&);
        void addInstructionToEndOfInstructionList(InstructionNode * I, InstructionNode *& list);
        void sortOutCJMPOperator(InstructionNode * I, TokenType TT);

        Token expect(TokenType);
};
