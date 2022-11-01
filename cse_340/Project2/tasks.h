#include <vector>
#include "execute.h"
#include "lexer.h"
#include "ast.h"
#include <map>

using namespace std;


// tmp
class TypeChecker
{
private:
    vector<string> scalars;
    vector<string> arrays;
    vector<int> type_errors;
    vector<int> assign_errors;

    int type_check_expr(ASTNode *node);
    int type_check_assignment(ASTNode *node);
    int type_check_var_access(ASTNode *node);

public:
    void set_declarations(vector<string> a, vector<string> s);
    void type_check_assignment_stmt(ASTNode *rhs, ASTNode *lhs, const int ln);
    void type_check_output_stmt(ASTNode *va, const int ln);
    void print_type_errors();
};

/* --- DEFINITIONS FOR THE STACK --- */
enum NodeType { EXPR = 0, TERM };

typedef struct StackNode
{
    ASTNode* expr;
    NodeType type;
    Token term;

    // constructors
    StackNode() {};
    StackNode(NodeType ty, ASTNode* ex, Token to)
    {
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

typedef struct Location
{
    int addr;
    string lex;
    LocationDef type;

    Location(int a, string le, LocationDef t)
    {
        addr = a;
        lex = le;
        type = t;
    }
} Location;

class Parser
{
    public:
    LexicalAnalyzer lexer;
    PPStack stack;
    TypeChecker checker;

    vector<string> arrays;
    vector<string> scalars;
    vector<ASTree> astrees;

    // LOGIC / NAMES
    int next_index = 0;
    int last_index = 0;
    vector<Location> location_list;

    // NAMES / LOGIC
    map<string, vector<string>> expr_rules = {
        {"1", {"expr", "MINUS", "expr"}},
        {"2", {"expr", "PLUS", "expr"}},
        {"3", {"expr", "MULT", "expr"}},
        {"4", {"expr", "DIV", "expr"}},
        {"5", {"LPAREN", "expr", "RPAREN"}},
        {"6", {"expr", "LBRAC", "expr", "RBRAC"}},
        {"7", {"expr", "LBRAC", "DOT", "RBRAC"}},
        {"8", {"primary"}}};

    // NAMES / LOGIC
    string table[12][12] = {
        // 0    1    2    3    4    5    6    7    8    9    10   11
        { ">", ">", "<", "<", "<", ">", "<", "e", ">", "<", "<", ">" }, // 0
        { ">", ">", "<", "<", "<", ">", "<", "e", ">", "<", "<", ">" }, // 1
        { ">", ">", ">", ">", "<", ">", "<", "e", ">", "<", "<", ">" }, // 2
        { ">", ">", ">", ">", "<", ">", "<", "e", ">", "<", "<", ">" }, // 3
        { "<", "<", "<", "<", "<", "=", "<", "e", "<", "<", "<", "e" }, // 4
        { ">", ">", ">", ">", "e", ">", ">", "e", ">", "e", "e", ">" }, // 5
        { "<", "<", "<", "<", "<", ">", "<", "=", "=", "<", "<", "e" }, // 6
        { "e", "e", "e", "e", "e", "e", "e", "e", "=", "e", "e", "e" }, // 7
        { ">", ">", ">", ">", "e", ">", ">", "e", ">", "e", "e", ">" }, // 8
        { ">", ">", ">", ">", "e", ">", ">", "e", ">", "e", "e", ">" }, // 9
        { ">", ">", ">", ">", "e", ">", ">", "e", ">", "e", "e", ">" }, // 10
        { "<", "<", "<", "<", "<", "e", "<", "e", "e", "<", "<", "a" }  // 11
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
    void parse_primary();

    TokenType peek(int);
    Token expect(TokenType);
    void syntax_error();

    instNode* append_to_end(instNode*, instNode*);
    string get_next_symbol();
    int index_of(TokenType);
    string get_rhs(StackNode);
    bool is_valid_rule(vector<string>);
    StackNode reduce(vector<StackNode>, vector<string>);
    ASTNode* create_inst(ASTNode*);
    int get_location(string);
};
/* --- DEFINTIONS FOR THE PARSER --- */
