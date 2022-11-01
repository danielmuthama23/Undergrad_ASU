#include <vector>
#include "execute.h"
#include "lexer.h"
#include "ast.h"
#include <map>

using namespace std;

/* --- DEFINITIONS FOR THE STACK --- */
enum NodeType { EXPR = 0, TERM };

typedef struct StackNode {
    ASTNode* expr;
    NodeType type;
    Token term;

    // constructors
    StackNode() {};
    StackNode(NodeType ty, ASTNode* ex, Token to) {
        type = ty;
        expr = ex;
        term = to;
    }
} StackNode;

class PPStack // for presendence parser
{
    public:
    vector<StackNode> stack; // define the stack

    // methods for the stack
    StackNode terminalTop();
    StackNode terminalPeek();
    StackNode pop();
    void push(StackNode&);
    void init();    
};
/* --- DEFINITIONS FOR THE STACK --- */

/* --- DEFINTIONS FOR THE PARSER --- */
enum LocationDef { l_SCALAR = 0, l_ARRAY };

typedef struct Location {
    int addr;
    string lex;
    LocationDef type;

    Location(int a, string le, LocationDef t) { addr = a; lex = le; type = t; }
} Location;

class Parser {
    public:
    LexicalAnalyzer lexer;
    PPStack stack;

    vector<string> arrays;
    vector<string> scalars;
    vector<ASTree> astrees;

    int first_i = 0;
    int second_i = 0;
    vector<Location> location_list;

    // the order from the table given in the pdf
    vector<TokenType> op_pres_order = {
        PLUS,
        MINUS,
        MULT,
        DIV,
        LPAREN,
        RPAREN,
        LBRAC,
        DOT,
        RBRAC,
        NUM,
        ID
    };

    // table rows and columns in same order as op_pres_order
    string table[12][12] = {
        { ">", ">", "<", "<", "<", ">", "<", "e", ">", "<", "<", ">" },
        { ">", ">", "<", "<", "<", ">", "<", "e", ">", "<", "<", ">" },
        { ">", ">", ">", ">", "<", ">", "<", "e", ">", "<", "<", ">" },
        { ">", ">", ">", ">", "<", ">", "<", "e", ">", "<", "<", ">" },
        { "<", "<", "<", "<", "<", "=", "<", "e", "<", "<", "<", "e" },
        { ">", ">", ">", ">", "e", ">", ">", "e", ">", "e", "e", ">" },
        { "<", "<", "<", "<", "<", ">", "<", "=", "=", "<", "<", "e" },
        { "e", "e", "e", "e", "e", "e", "e", "e", "=", "e", "e", "e" },
        { ">", ">", ">", ">", "e", ">", ">", "e", ">", "e", "e", ">" },
        { ">", ">", ">", ">", "e", ">", ">", "e", ">", "e", "e", ">" },
        { ">", ">", ">", ">", "e", ">", ">", "e", ">", "e", "e", ">" },
        { "<", "<", "<", "<", "<", "e", "<", "e", "e", "<", "<", "a" } 
    };

    // provided methods
    void parse_and_generate_AST();
    void parse_and_type_check();
    instNode* parse_and_generate_statement_list();

    void parse_program();
    void parse_decl_section();
    vector<string> parse_scalar_decl_section();
    vector<string> parse_array_decl_section();
    vector<string> parse_id_list();
    void parse_block();
    instNode* parse_stmt_list();
    instNode* parse_stmt();
    instNode* parse_assign_stmt();
    instNode* parse_output_stmt();
    ASTNode* parse_variable_access();
    ASTNode* parse_expr();
    // void parse_primary();

    TokenType peek(int);
    Token expect(TokenType);
    void syntax_error();

    instNode* append_to_end(instNode*, instNode*);
    string get_next_symbol();
    int get_order_of(TokenType);
    int rhs_rule_key(vector<StackNode>);
    StackNode reduce(vector<StackNode>, int);
    ASTNode* create_inst(ASTNode*);
    int get_location(string);
    OpType op_to_optype(Operator);

    // type checker
    vector<string> curr_scalars;
    vector<string> curr_arrays;
    vector<int> type_errors;
    vector<int> assign_errors;

    bool has_expr_type_err(ASTNode*);
    bool has_assign_type_err(ASTNode*);
    bool has_access_type_err(ASTNode*);
    void print_type_errors();
};
/* --- DEFINTIONS FOR THE PARSER --- */
