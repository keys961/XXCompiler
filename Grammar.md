# Grammar 

program: program_head SEMICOLON block DOT
    ;
program_head: PROGRAM ID
    ;
block: constant_definition_part 
    type_definition_part 
    variable_declaration_part 
    procedure_function_declaration_part 
    block_body_part
    ;
id_list: id_list COMMA ID 
    | ID
    ;

constant_definition_part: CONST constant_list
    |
    ;
constant_list: constant_list constant_definition
    | constant_definition
    ;
constant_definition: ID EQUAL constant_value SEMICOLON
    ;
constant_value: INTEGER
    | REAL
    | CHAR
    | STRING
    ;

type_definition_part: TYPE type_definition_list
    |
    ;
type_definition_list: type_definition_list type_definition
    | type_definition
    ;
type_definition: ID EQUAL type_denoter SEMICOLON
    ;
type_denoter: simple_type
    | range_type
    | array_type
    | record_type
    ;
simple_type: TYPE_INTEGER
    | TYPE_CHAR
    | TYPE_REAL
    | TYPE_STRING 
    | ID 
    | LP id_list RP
    | ID DOTDOT ID
    ;
range_type: constant_value DOTDOT constant_value
    ;
array_type: ARRAY LB range_type RB OF type_denoter
    ;
record_type: RECORD field_definition_list END
    ;
field_definition_list: field_definition_list SEMICOLON field_definition
    | field_definition
    ;
field_definition: id_list COLON type_denoter
    ;

variable_declaration_part: VAR variable_declaration_list SEMICOLON
    |
    ;
variable_declaration_list: variable_declaration_list SEMICOLON variable_declaration
    | variable_declaration
    ;
variable_declaration: id_list COLON type_denoter
    ;

procedure_function_declaration_part: procedure_function_declaration_part procedure_function_declaration
    | procedure_function_declaration
    |
    ;
procedure_function_declaration: procedure_declaration 
    | function_declaration
    ;
procedure_declaration: PROCEDURE ID parameters SEMICOLON block SEMICOLON
    ;
function_declaration: FUNCTION ID parameters COLON simple_type SEMICOLON block SEMICOLON
    ;
parameters: LP parameter_list RP
    | LP RP
    ;
parameter_list: parameter_list SEMICOLON parameter
    | parameter
    ;
parameter: id_list COLON simple_type
    ;

block_body_part: compound_statement
    ;
compound_statement: BEGIN_ statememt_list END
    ;
statememt_list: statememt_list SEMICOLON statememt
    | statememt SEMICOLON
    | 
    ;
label: STRING
    ;
statememt: label COLON stmt
    | stmt
    ;
stmt: assign_statememt
    | procedure_statement
    | if_statememt
    | repeat_statememt
    | for_statememt
    | while_statememt
    | case_statememt
    | goto_statememt
    | compound_statement
    ;

assign_statememt: variable_access ASSIGN expression
    ;
variable_access: ID
    | ID LB expression RB
    | ID DOT ID
    ;

procedure_statement: READ LP factor RP
    | WRITE LP expression RP
    | ID LP args RP
    | ID LP RP
    ;

if_statememt: IF expression THEN statememt ELSE statememt
    | IF expression THEN statememt
    ;

repeat_statememt: REPEAT statememt_list UNTIL expression
    ;

for_statememt: FOR ID ASSIGN expression direction expression DO statememt
    ;
direction: TO 
    | DOWNTO
    ;

while_statememt: WHILE expression DO statememt
    ;

case_statememt: CASE expression OF case_list END
    ;
case_list: case_list SEMICOLON case_item
    | case_item
    ;
case_item: constant_value COLON statememt
    ;

goto_statememt: GOTO label
    ;

expression: expression LT expr
    | expression LE expr
    | expression EQUAL expr
    | expression GE expr
    | expression GT expr
    | expression UNEQUAL expr
    | expr
    ;
expr: expr PLUS term
    | expr MINUS term
    | expr OR term
    | expr XOR term
    | term
    ;
term: term MULTIPLY factor
    | term DIVIDE factor
    | term MOD factor
    | term AND factor
    | factor
    ;
factor: ID
    | ID LP args RP
    | ID LB expression RB
    | ID DOT ID
    | constant_value
    | LP expression RP
    | MINUS factor
    | NOT factor
    ;
args: args COMMA expression
    | expression
    ;