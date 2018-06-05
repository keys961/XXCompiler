%{
#define YYSTYPE TreeNode*
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <queue>
#include <set>
#include <string>
#include "tree.h"
#include "lexer.h"

class GlobalInfo;

extern char* yytext; // yytext
extern GlobalInfo globalInfo; // global info
extern std::ofstream grammarOut;
std::set<TreeNode*> createdNodes;
std::queue<int> intQueue; //store int values
std::queue<double> doubleQueue; //store double values
std::queue<std::string> stringQueue; //store string values
static int yylex(void);
static int hashCodeForString(const std::string& str);
static void showNodeInfo(const std::string& info);
static void updateLineNoForTreeNode(TreeNode* node);
int yyerror(const char *);

extern TreeNode* root;
%}
%token AND ARRAY BEGIN_ CASE CONST DO DOWNTO OR ELSE END
%token FOR FUNCTION GOTO IF NOT OF PROGRAM PROCEDURE READ RECORD
%token REPEAT THEN TO TYPE UNTIL VAR WHILE WRITE XOR TYPE_INTEGER
%token TYPE_REAL TYPE_STRING TYPE_CHAR NEWLINE
%token PLUS MINUS MULTIPLY DIVIDE MOD LT LE EQUAL UNEQUAL GE GT
%token DOT DOTDOT COMMA SEMICOLON COLON ASSIGN LB RB LP RP
%token INTEGER REAL CHAR STRING
%token ID
%right THEN ELSE
%%

program: program_head SEMICOLON block DOT
         {
             showNodeInfo("program -> program_head SEMICOLON block DOT");
             $$ = $3;
             $3->setName($1->getName());
             delete $1;

             root = $$;
         }
    ;
program_head: PROGRAM ID
              {
                  showNodeInfo("program_head -> PROGRAM ID");
                  $$ = new TreeNode();
                  $$->setName($2->getName());
                  updateLineNoForTreeNode($$);
                  delete $2;
              }
    ;
block: constant_definition_part 
    type_definition_part 
    variable_declaration_part 
    procedure_function_declaration_part 
    block_body_part
    {
        showNodeInfo("block -> constant_definition_part type_definition_part variable_declaration_part procedure_function_declaration_part block_body_part");
        $$ = new ProgramBodyTreeNode($1, $2, $3, $4, $5);
        createdNodes.insert($$);
        updateLineNoForTreeNode($$);
    }
    ;
id_list: id_list COMMA ID 
         {
             showNodeInfo("id_list -> id_list COMMA ID");
             $$ = $1;
             std::string name = $3->getName();
             TreeNode* node = new TreeNode();
             node->setName(name);
             updateLineNoForTreeNode(node);
             ((ListTreeNode*)$$)->insert(node);
             delete $3;
         }
    | ID 
      {
          showNodeInfo("id_list -> ID");
          std::string name = $1->getName();
          std::vector<TreeNode*> list;
          TreeNode* node = new TreeNode();
          updateLineNoForTreeNode(node);
          node->setName(name);
          list.push_back(node);
          delete $1;
          $$ = new ListTreeNode("id_list", list);
          createdNodes.insert($$);
          updateLineNoForTreeNode($$);
      }
    ;

constant_definition_part: CONST constant_list
                          {
                              showNodeInfo("constant_definition_part -> CONST constant_list");
                              $$ = $2;
                          }
    | {
         showNodeInfo("constant_definition_part ->");
         std::vector<TreeNode*> list;
         $$ = new ListTreeNode("constant_definition_part", list);
         createdNodes.insert($$);
         updateLineNoForTreeNode($$);
      }
    ;
constant_list: constant_list constant_definition
               {
                   showNodeInfo("constant_list -> constant_list constant_definition");
                   $$ = $1;
                   ((ListTreeNode*)$$)->insert($2);
               }
    | constant_definition
      {
          showNodeInfo("constant_list -> constant_definition");
          std::vector<TreeNode*> list;
          list.push_back($1);
          $$ = new ListTreeNode("constant_list", list);
          createdNodes.insert($$);
          updateLineNoForTreeNode($$);
      }
    ;
constant_definition: ID EQUAL constant_value SEMICOLON
                     {
                         showNodeInfo("constant_definition -> ID EQUAL constant_value SEMICOLON");
                         std::string name = $1->getName();
                         VariableTreeNode* varNode = new VariableTreeNode(name, nullptr, true);
                         updateLineNoForTreeNode(varNode);
                         BinaryExprTreeNode* binNode = new BinaryExprTreeNode(":=", varNode, $3);
                         $$ = binNode;
                         delete $1;
                         createdNodes.insert($$);
                         createdNodes.insert(varNode);
                         updateLineNoForTreeNode($$);
                     }
    ;
constant_value: INTEGER 
                {
                    showNodeInfo("constant_value -> INTEGER");
                    $$ = new LiteralTreeNode(yytext, "integer");
                    updateLineNoForTreeNode($$);
                    createdNodes.insert($$);
                }
    | REAL
      {
          showNodeInfo("constant_value -> REAL");
          $$ = new LiteralTreeNode(yytext, "real");
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | CHAR
      {
          showNodeInfo("constant_value -> CHAR");
          $$ = new LiteralTreeNode(yytext, "char");
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | STRING
      {
          showNodeInfo("constant_value -> STRING");
          $$ = new LiteralTreeNode(yytext, "string");
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    ;

type_definition_part: TYPE type_definition_list
                      {
                          showNodeInfo("type_definition_part -> TYPE type_definition_list");
                          $$ = $2;
                      }
    | {
         showNodeInfo("type_definition_part -> ");
         std::vector<TreeNode*> list;
         $$ = new ListTreeNode("type_definition_part", list);
         updateLineNoForTreeNode($$);
         createdNodes.insert($$);
      }
    ;
type_definition_list: type_definition_list type_definition
                      {
                          showNodeInfo("type_definition_list -> type_definition_list type_definition");
                          $$ = $1;
                          ((ListTreeNode*)$$)->insert($2);
                      }
    | type_definition
      {
          showNodeInfo("type_definition_list -> type_definition");
          std::vector<TreeNode*> list;
          list.push_back($1);
          $$ = new ListTreeNode("type_definition_list", list);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    ;
type_definition: ID EQUAL type_denoter SEMICOLON
                 {
                     showNodeInfo("type_definition -> ID EQUAL type_denoter SEMICOLON");
                     std::string name = $1->getName();
                     $$ = new CustomTypeTreeNode(name, $3);
                     updateLineNoForTreeNode($$);
                     delete $1;
                     createdNodes.insert($$);
                 }
    ;
type_denoter: simple_type
              {
                  showNodeInfo("type_denoter -> simple_type");
                  $$ = $1;
                  createdNodes.insert($$);
              }
    | range_type
      {
          showNodeInfo("type_denoter -> range_type");
          $$ = $1;
          createdNodes.insert($$);
      }
    | array_type
      {
          showNodeInfo("type_denoter -> array_type");
          $$ = $1;
          createdNodes.insert($$);
      }
    | record_type
      {
          showNodeInfo("type_denoter -> record_type");
          $$ = $1;
          createdNodes.insert($$);
      }
    ;
simple_type: TYPE_INTEGER
             {
                 showNodeInfo("simple_type -> TYPE_INTEGER");
                 $$ = new CommonTypeTreeNode("integer");
                 updateLineNoForTreeNode($$);
                 createdNodes.insert($$);
             }
    | TYPE_CHAR
      {
          showNodeInfo("simple_type -> TYPE_CHAR");
          $$ = new CommonTypeTreeNode("char");
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | TYPE_REAL
      {
          showNodeInfo("simple_type -> TYPE_REAL");
          $$ = new CommonTypeTreeNode("real");
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | TYPE_STRING 
      {
          showNodeInfo("simple_type -> TYPE_STRING");
          $$ = new CommonTypeTreeNode("string");
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | ID 
      {
          showNodeInfo("simple_type -> ID");
          $$ = new CustomTypeTreeNode($1->getName(), nullptr);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
          delete $1;
      }
    | LP id_list RP
      {
          showNodeInfo("simple_type -> LP id_list RP");
          $$ = new EnumTypeTreeNode($2, "enum_type");
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    ;
range_type: constant_value DOTDOT constant_value
            {
                showNodeInfo("range_type -> constant_value DOTDOT constant_value");
                $$ = new RangeTypeTreeNode((IDTreeNode*)$3, (IDTreeNode*)$1);
                updateLineNoForTreeNode($$);
                createdNodes.insert($$);
            }
    ;
array_type: ARRAY LB range_type RB OF type_denoter
            {
                showNodeInfo("array_type -> ARRAY LB range_type RB OF type_denoter");
                $$ = new ArrayTypeTreeNode((RangeTypeTreeNode*)$3, (CommonTypeTreeNode*)$6);
                createdNodes.insert($$);
                updateLineNoForTreeNode($$);
            }
    ;
record_type: RECORD field_definition_list END
             {
                 showNodeInfo("record_type -> RECORD field_definition_list END");
                 std::vector<TreeNode*> list = ((ListTreeNode*)$2)->getList();
                 $$ = new RecordTypeTreeNode(list);
                 updateLineNoForTreeNode($$);
                 createdNodes.insert($$);
             }
    ;
field_definition_list: field_definition_list SEMICOLON field_definition
                       {
                           showNodeInfo("field_definition_list -> field_definition_list SEMICOLON field_definition");
                           $$ = $1;
                           ((ListTreeNode*)$$)->insert($3);
                       }
    | field_definition
      {
          showNodeInfo("field_definition_list -> field_definition");
          std::vector<TreeNode*> list;
          list.push_back($1);
          $$ = new ListTreeNode("field_definition_list", list);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    ;
field_definition: ID COLON type_denoter
                  {
                      showNodeInfo("field_definition -> ID COLON type_denoter");
                      std::string name = $1->getName();
                      delete $1;
                      $$ = new VariableTreeNode(name, $3);
                      updateLineNoForTreeNode($$);
                      createdNodes.insert($$);
                  }
    ;

variable_declaration_part: VAR variable_declaration_list SEMICOLON
                           {
                               showNodeInfo("variable_declaration_part -> VAR variable_declaration_list SEMICOLON");
                               $$ = $2;
                           }
    | {
          showNodeInfo("variable_declaration_part ->");
          std::vector<TreeNode*> list;
          $$ = new ListTreeNode("variable_declaration_part", list);
          createdNodes.insert($$);
          updateLineNoForTreeNode($$);
      }
    ;
variable_declaration_list: variable_declaration_list SEMICOLON variable_declaration
                           {
                               showNodeInfo("variable_declaration_list -> variable_declaration_list SEMICOLON variable_declaration");
                               $$ = $1;
                               ((ListTreeNode*)$$)->insert($3);
                               createdNodes.insert($$);
                           }
    | variable_declaration
      {
          showNodeInfo("variable_declaration_list -> variable_declaration");
          std::vector<TreeNode*> list;
          list.push_back($1);
          $$ = new ListTreeNode("variable_declaration_list", list);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    ;
variable_declaration: ID COLON type_denoter
                      {
                          showNodeInfo("variable_declaration -> ID COLON type_denoter");
                          std::string name = $1->getName();
                          delete $1;
                          $$ = new VariableTreeNode(name, $3);
                          createdNodes.insert($$);
                          updateLineNoForTreeNode($$);
                      }
    ;

procedure_function_declaration_part: procedure_function_declaration_part procedure_function_declaration
                                     {
                                         showNodeInfo("procedure_function_declaration_part -> procedure_function_declaration_part procedure_function_declaration");
                                         $$ = $1;
                                         ((ListTreeNode*)$$)->insert($2);
                                     }
    | procedure_function_declaration
      {
          showNodeInfo("procedure_function_declaration_part -> procedure_function_declaration");
          std::vector<TreeNode*> list;
          list.push_back($1);
          $$ = new ListTreeNode("procedure_function_declaration_part", list);
          createdNodes.insert($$);
          updateLineNoForTreeNode($$);
      }
    | {
          showNodeInfo("procedure_function_declaration_part ->");
          std::vector<TreeNode*> list;
          $$ = new ListTreeNode("procedure_function_declaration_part", list);
          createdNodes.insert($$);
          updateLineNoForTreeNode($$);
      }
    ;
procedure_function_declaration: procedure_declaration 
                                {
                                    showNodeInfo("procedure_function_declaration -> procedure_declaration ");
                                    $$ = $1;
                                }
    | function_declaration
      {
          showNodeInfo("procedure_function_declaration -> function_declaration");
          $$ = $1;
      }
    ;
procedure_declaration: PROCEDURE ID parameters SEMICOLON block SEMICOLON
                       {
                           showNodeInfo("procedure_declaration -> PROCEDURE ID parameters SEMICOLON block SEMICOLON");
                           std::string name = $2->getName();
                           delete $2;
                           $$ = new FuncOrProcTreeNode(name, $3, $5);
                           createdNodes.insert($$);
                           updateLineNoForTreeNode($$);
                       }
    ;
function_declaration: FUNCTION ID parameters COLON simple_type SEMICOLON block SEMICOLON
                      {
                          showNodeInfo("function_declaration -> FUNCTION ID parameters COLON simple_type SEMICOLON block SEMICOLON");
                          std::string name = $2->getName();
                           delete $2;
                          $$ = new FuncOrProcTreeNode(name, $3, $7, $5, true);
                          createdNodes.insert($$);
                          updateLineNoForTreeNode($$);
                      }
    ;
parameters: LP parameter_list RP
            {
                showNodeInfo("parameters -> LP parameter_list RP");
                $$ = $2;
            }
    | LP RP
      {
          showNodeInfo("parameters -> LP RP");
          std::vector<TreeNode*> emptyList;
          $$ = new ListTreeNode("parameters", emptyList);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    ;
parameter_list: parameter_list SEMICOLON parameter
                {
                    showNodeInfo("parameter_list -> parameter_list SEMICOLON parameter");
                    $$ = $1;
                    ((ListTreeNode*)$$)->insert($3);
                }
    | parameter
      {
          showNodeInfo("parameter_list -> parameter");
          std::vector<TreeNode*> list;
          list.push_back($1);
          $$ = new ListTreeNode("parameter_list", list);
          createdNodes.insert($$);
          updateLineNoForTreeNode($$);
      }
    ;
parameter: ID COLON simple_type
           {
               showNodeInfo("parameter -> ID COLON simple_type");
               std::string name = $1->getName();
               delete $1;
               $$ = new VariableTreeNode(name, $3);
               createdNodes.insert($$);
               updateLineNoForTreeNode($$);
           }
    ;

block_body_part: compound_statement
                 {
                     showNodeInfo("block_body_part -> compound_statement");
                     std::vector<TreeNode*> body;
                     body.push_back($1);
                     $$ = new ListTreeNode("block_body_part", body);
                     createdNodes.insert($$);
                     updateLineNoForTreeNode($$);
                 }
    ;
compound_statement: BEGIN_ statememt_list END
                    {
                        showNodeInfo("compound_statement -> BEGIN_ statememt_list END");
                        $$ = new CompoundStmtTreeNode((ListTreeNode*)$2);
                        createdNodes.insert($$);
                        updateLineNoForTreeNode($$);
                    }
    ;
statememt_list: statememt_list statememt SEMICOLON
                {
                    showNodeInfo("statememt_list -> statememt_list statememt SEMICOLON");
                    $$ = $1;
                    ((ListTreeNode*)$$)->insert($2);
                }
    | 
      {
         showNodeInfo("statememt_list -> ");
         std::vector<TreeNode*> list;
         $$ = new ListTreeNode("statement_list", list);
         createdNodes.insert($$);
         updateLineNoForTreeNode($$);
      }
    ;
label: STRING
       {
           showNodeInfo("label -> STRING");
           std::string labelName = yytext;
           TreeNode* node = new TreeNode();
           node->setName(labelName);
           $$ = node;
       }
    ;
statememt: label COLON stmt
           {
               showNodeInfo("statement -> label COLON stmt");
               $$ = $3;
               const std::string labelName = $1->getName();
               ((StatementTreeNode*)$$)->setLabel(hashCodeForString(labelName));
               delete $1;
           }
    | stmt
      {
          showNodeInfo("statement -> stmt");
          $$ = $1;
      }
    ;
stmt: assign_statememt
      {
          showNodeInfo("stmt -> assign_statememt");
          $$ = $1;
      }
    | procedure_statement
      {
          showNodeInfo("stmt -> procedure_statement");
          $$ = $1;
      }
    | if_statememt
      {
          showNodeInfo("stmt -> if_statememt");
          $$ = $1;
      }
    | repeat_statememt
      {
          showNodeInfo("stmt -> repeat_statement");
          $$ = $1;
      }
    | for_statememt
      {
          showNodeInfo("stmt -> for_statememt");
          $$ = $1;
      }
    | while_statememt
      {
          showNodeInfo("stmt -> while_statememt");
          $$ = $1;
      }
    | case_statememt
      {
          showNodeInfo("stmt -> case_statememt");
          $$ = $1;
      }
    | goto_statememt
      {
          showNodeInfo("stmt -> goto_statememt");
          $$ = $1;
      }
    | compound_statement
      {
          showNodeInfo("stmt -> compound_statement");
          $$ = $1;
      }
    ;

assign_statememt: variable_access ASSIGN expression
                  {
                     showNodeInfo("assign_statememt -> variable_access ASSIGN expression");
                     $$ = new BinaryExprTreeNode(":=", $1, $3);
                     createdNodes.insert($$);
                     updateLineNoForTreeNode($$);
                  }
    ;
variable_access: ID
                 {
                     showNodeInfo("variable_access -> ID");
                     $$ = new VariableTreeNode($1->getName());
                     createdNodes.insert($$);
                     delete $1;
                     updateLineNoForTreeNode($$);
                 }
    | ID LB expression RB
      {
          showNodeInfo("variable_access -> ID LB expression RB");
          std::string arrayName = $1->getName();
          $$ = new ArrayElemTreeNode(arrayName, $3);
          createdNodes.insert($$);
          updateLineNoForTreeNode($$);
      }
    | ID DOT ID
      {
          showNodeInfo("variable_access -> ID DOT ID");
          $$ = new RecordElemTreeNode($1->getName(), $3->getName());
          createdNodes.insert($$);
          delete $1;
          delete $3;
          updateLineNoForTreeNode($$);
      }
    ;

procedure_statement: READ LP factor RP
                     {
                         showNodeInfo("procedure_statement -> READ LP factor RP");
                         // You need to release it and make it NULL
                         std::vector<TreeNode*>* list = new std::vector<TreeNode*>;
                         list->push_back($3);
                         $$ = new CallExprTreeNode("read", list, false);
                         createdNodes.insert($$);
                         updateLineNoForTreeNode($$);
                     }
    | WRITE LP expression RP
      {
          showNodeInfo("procedure_statement -> WRITE LP expression RP");
          std::vector<TreeNode*>* list = new std::vector<TreeNode*>;
          list->push_back($3);
          $$ = new CallExprTreeNode("write", list, false);
          createdNodes.insert($$);
          updateLineNoForTreeNode($$);
      }
    | ID LP args RP
      {
          showNodeInfo("procedure_statement -> ID LP args RP");
          std::string procName = $1->getName();
          delete $1;
          $$ = new CallExprTreeNode(procName, &(((ListTreeNode*)$3)->getList()), 
            false);
          createdNodes.insert($$);
          updateLineNoForTreeNode($$);
      }
    | ID LP RP
      {
          showNodeInfo("procedure_statement -> ID");
          std::string procName = $1->getName();
          delete $1;
          $$ = new CallExprTreeNode(procName, nullptr, false);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    ;

if_statememt: IF expression THEN statememt ELSE statememt
              {
                  showNodeInfo("if_statememt -> IF expression THEN statememt ELSE statememt");
                  $$ = new IfStmtTreeNode((ExprTreeNode*)$2, (StatementTreeNode*)$4, (StatementTreeNode*)$6);
                  createdNodes.insert($$);
                  updateLineNoForTreeNode($$);
              }
    | IF expression THEN statememt
      {
          showNodeInfo("if_statememt -> IF expression THEN statememt");
          $$ = new IfStmtTreeNode((ExprTreeNode*)$2, (StatementTreeNode*)$4, nullptr);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    ;

repeat_statememt: REPEAT statememt_list UNTIL expression
                  {
                      showNodeInfo("repeat_statememt -> REPEAT statememt_list UNTIL expression");
                      $$ = new RepeatStmtTreeNode((ExprTreeNode *)$4, (StatementTreeNode *)$2);
                      createdNodes.insert($$);
                      updateLineNoForTreeNode($$);
                  } 
    ;

for_statememt: FOR ID { stringQueue.push(yytext); } ASSIGN expression direction expression DO statememt
               {
                   showNodeInfo("for_statement -> FOR ID ASSIGN expression direction expression DO statememt");
                   std::string variableId = $2->getName();
                   delete $2;
                   VariableTreeNode* varNode = new VariableTreeNode(variableId);
                   updateLineNoForTreeNode(varNode);
                   BinaryExprTreeNode* exprNode = new BinaryExprTreeNode(":=", varNode, $5);
                   updateLineNoForTreeNode(exprNode);
                   std::string direction = $6->getName();
                   $$ = new ForStmtTreeNode(exprNode, direction, $7, (StatementTreeNode *)$9);
                   updateLineNoForTreeNode($$);
                   delete $6;
                   createdNodes.insert($$);
                   createdNodes.insert(varNode);
                   createdNodes.insert(exprNode);
               }
    ;
direction: TO 
           {
               showNodeInfo("direction -> TO");
               $$ = new TreeNode();
               $$->setName("to");
           }
    | DOWNTO
      {
          showNodeInfo("direction -> DOWNTO");
          $$ = new TreeNode();
          $$->setName("downto");
      }
    ;

while_statememt: WHILE expression DO statememt
                 {
                     showNodeInfo("while_statement -> WHILE expression DO statement");
                     $$ = new WhileStmtTreeNode((ExprTreeNode *)$2, (StatementTreeNode *)$4);
                     createdNodes.insert($$);
                     updateLineNoForTreeNode($$);
                 }
    ;

case_statememt: CASE expression OF case_list END
                {
                    showNodeInfo("case_statement -> CASE expresion OF case_list END");
                    $$ = new SwitchStmtTreeNode((ExprTreeNode *)$2, (ListTreeNode *)$4);
                    createdNodes.insert($$);
                    updateLineNoForTreeNode($$);
                }
    ;
case_list: case_list SEMICOLON case_item
           {
               showNodeInfo("case_list -> case_list SEMICOLON case_item");
               $$ = $1;
               ((ListTreeNode*)$$)->insert($3);
           }
    | case_item
      {
          showNodeInfo("case_list -> case_item");
          std::vector<TreeNode*> list;
          list.push_back($1);
          $$ = new ListTreeNode("case_list", list);
          createdNodes.insert($$);
          updateLineNoForTreeNode($$);
      }
    ;
case_item: constant_value COLON statememt
           {
               showNodeInfo("case_item -> constant_value COLON statement");
               $$ = new CaseExprTreeNode((IDTreeNode *)$1, (StatementTreeNode *)$3);
               createdNodes.insert($$);
               updateLineNoForTreeNode($$);
           }
    ;

goto_statememt: GOTO label
                {
                    showNodeInfo("goto_statememt -> GOTO label");
                    std::string labelName = $2->getName();
                    // you need to hash the labelName 
                    $$ = new GotoStmtTreeNode(labelName);
                    updateLineNoForTreeNode($$);
                    // remove tree node created for label
                    delete $2;
                    createdNodes.insert($$);
                }
    ;

expression: expression LT expr
            {
                showNodeInfo("expression -> expression LT expr");
                $$ = new BinaryExprTreeNode("<", $1, $3);
                updateLineNoForTreeNode($$);
                createdNodes.insert($$);
            }
    | expression LE expr
      {
          showNodeInfo("expression -> expression LE expr");
          $$ = new BinaryExprTreeNode("<=", $1, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | expression EQUAL expr
      {
          showNodeInfo("expression -> expression EQUAL expr");
          $$ = new BinaryExprTreeNode("=", $1, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | expression GE expr
      {
          showNodeInfo("expression -> expression GE expr");
          $$ = new BinaryExprTreeNode(">=", $1, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | expression GT expr
      {
          showNodeInfo("expression -> expression GT expr");
          $$ = new BinaryExprTreeNode(">", $1, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | expression UNEQUAL expr
      {
          showNodeInfo("expression -> expression UNEQUAL expr");
          $$ = new BinaryExprTreeNode("!=", $1, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | expr
      {
          showNodeInfo("expression -> expr");
          $$ = $1;
      }
    ;
expr: expr PLUS term
      {
          showNodeInfo("expr -> expr PLUS term");
          $$ = new BinaryExprTreeNode("+", $1, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | expr MINUS term
      {
          showNodeInfo("expr -> expr MNUS term");
          $$ = new BinaryExprTreeNode("-", $1, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | expr OR term
      {
          showNodeInfo("expr -> expr OR term");
          $$ = new BinaryExprTreeNode("or", $1, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | expr XOR term
      {
          showNodeInfo("expr -> expr XOR term");
          $$ = new BinaryExprTreeNode("xor", $1, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | term
      {
          showNodeInfo("expr -> term");
          $$ = $1;
      }
    ;
term: term MULTIPLY factor
      {
          showNodeInfo("term -> term MULTIPLY factor");
          $$ = new BinaryExprTreeNode("*", $1, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | term DIVIDE factor
      {
          showNodeInfo("term -> term DIVIDE factor");
          $$ = new BinaryExprTreeNode("/", $1, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | term MOD factor
      {
          showNodeInfo("term -> term MOD factor");
          $$ = new BinaryExprTreeNode("%", $1, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | term AND factor
      {
          showNodeInfo("term -> term AND factor");
          $$ = new BinaryExprTreeNode("and", $1, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | factor
      {
          showNodeInfo("term -> factor");
          $$ = $1;
      }
    ;
factor: ID 
        { 
          // Simple variable
          showNodeInfo("factor -> ID");
          $$ = new VariableTreeNode($1->getName());
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
          delete $1;
        }
    | ID LP args RP 
      { 
          // Function value
          showNodeInfo("factor -> ID LP args RP"); 
          std::string functionName = $1->getName();
          delete $1;
          $$ = new CallExprTreeNode(functionName,
            &(((ListTreeNode*)$3)->getList()));
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | ID LB expression RB
      {
          // Array Element
          showNodeInfo("factor -> ID LB expression RB");
          std::string arrayName = $1->getName();
          delete $1;
          $$ = new ArrayElemTreeNode(arrayName, $3);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | ID DOT ID
      {
          // Record element
          showNodeInfo("factor -> ID DOT ID");
          $$ = new RecordElemTreeNode($1->getName(), $3->getName());
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
          delete $1;
          delete $3;
      }
    | constant_value
      {
          showNodeInfo("factor -> constant_value");
          $$ = $1;
      }
    | LP expression RP
      {
          showNodeInfo("factor -> LP expression RP");
          $$ = $2;
      }
    | MINUS factor
      {
          // Negative value
          showNodeInfo("factor -> MINUS factor");
          $$ = new UnaryExprTreeNode("-", $2);
          updateLineNoForTreeNode($$);
          createdNodes.insert($$);
      }
    | NOT factor
      {
          // Not value for bit..
          showNodeInfo("factor -> NOT factor");
          $$ = new UnaryExprTreeNode("not", $2);
          createdNodes.insert($$);
          updateLineNoForTreeNode($$);
      }
    ;
args: args COMMA expression
      {
          showNodeInfo("args -> args COMMA expression)");
          $$ = $1;
          ((ListTreeNode*)$$)->insert($3);
      }
    | expression 
      { 
          showNodeInfo("args -> expression");
          std::vector<TreeNode*> expressionList;
          expressionList.push_back($1);
          $$ = new ListTreeNode("args", expressionList);
          createdNodes.insert($$);
          updateLineNoForTreeNode($$);
      }
    ;
%%

static int yylex(void)
{
    return getCurrentToken();
}

static int hashCodeForString(const std::string& str)
{
    int h = 0;
    for(int i = 0; i < str.length(); i++)
        h = 31 * h + (str[i] & 0xff);
    
    return h;
}

static void showNodeInfo(const std::string& info)
{
    grammarOut << "At line " << globalInfo.currentLineIndex
        << ": " << info << std::endl; 
}

static void updateLineNoForTreeNode(TreeNode* node)
{
    node->setLineNum(globalInfo.currentLineIndex);
}

int yyerror(const char* str)
{
    printf("At line %ld:%ld: Token: %s.\n", globalInfo.currentLineIndex,
        globalInfo.currentTokenIndex, globalInfo.currentToken.c_str());
    printf("\tError message: %s\n", str);
    printf("Starting to clean garbage...\n");
    for(auto& it : createdNodes)
        delete it;
    printf("Cleaning finished.\n");
    root = nullptr;
    return 1;
}

int yywrap()
{
    return 1;
}