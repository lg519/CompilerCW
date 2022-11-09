%code requires{
  #include "../ast_hpp/ast.hpp"

  #include <cassert>

  extern translation_unit *g_root; // A way of getting the AST out

  // This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

%define parse.error verbose

// Represents the value associated with any kind of
// AST node. (possible types of yylval)
%union{
  double number;
  std::string* stringptr;
  node* nodeptr;
}

//tokens declarations
%token RETURN
%token INT
%token IDENTIFIER CONSTANT
%token LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP INC_OP DEC_OP
%token MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%token IF ELSE WHILE DO FOR BREAK CONTINUE SWITCH CASE DEFAULT

//type of the tokens (yylval)
%type <number> CONSTANT
%type <stringptr> IDENTIFIER INT RETURN '+' '-' '*' '/' '%' '&' '!' '~' '|' '^' '<' '>' unary_operator IF ELSE DO WHILE FOR
%type <stringptr> LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP INC_OP DEC_OP
%type <stringptr> MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN XOR_ASSIGN OR_ASSIGN
%type <nodeptr> translation_unit external_declaration function_definition declaration_specifiers type_specifier declarator direct_declarator compound_statement statement_list statement jump_statement 
%type <nodeptr> expression additive_expression multiplicative_expression cast_expression unary_expression postfix_expression primary_expression
%type <nodeptr> shift_expression relational_expression logical_or_expression logical_and_expression inclusive_or_expression exclusive_or_expression equality_expression and_expression conditional_expression constant_expression
%type <nodeptr> init_declarator_list declaration init_declarator declaration_list 
%type <nodeptr> assignment_expression expression_statement
%type <stringptr> assignment_operator '='
%type <nodeptr> initializer
%type <nodeptr> selection_statement iteration_statement
%type <nodeptr> parameter_declaration parameter_list parameter_type_list argument_expression_list
%type <nodeptr> labeled_statement
//top level
%start translation_unit 

//associativity rules

%%

translation_unit
	: external_declaration									{ g_root = new translation_unit($1); }					
	| translation_unit external_declaration					{ g_root->add_node($2); }
	;    


external_declaration
	: function_definition	 								{ $$ = $1; }
	| declaration  											{ $$ = $1; }
	;


/* declaration_list is removed as K&R declarations are not supported */
/* declarator compound_statement is removed because it's not supported */
function_definition
/*	: declaration_specifiers declarator declaration_list compound_statement */
	: declaration_specifiers declarator compound_statement	{ $$ = new function( dynamic_cast<Type_Specifier*>($1), dynamic_cast<function_id_args*>($2), dynamic_cast<compound_statement*>($3)); }
/*	| declarator declaration_list compound_statement */
/*	| declarator compound_statement */
	;

/*change this rule for function declaration. Need to be able to int foo(int x, int y);*/
/*add if dynamic_cast to check wether function_declaration or normal declaration*/
declaration
	: declaration_specifiers ';'									{$$ = $1;}					
	| declaration_specifiers init_declarator_list ';' 				{ $$ = new declaration(dynamic_cast<Type_Specifier*>($1),dynamic_cast<expression*>($2));}
	;



/* storage_class_specifier is removed as TYPEDEF is an advanced feature */
/* type_qualifier is removed as CONST is not supported */
/* type_specifier declaration_specifiers is removed as I don't understand it */
declaration_specifiers
/*	: storage_class_specifier */
/*	| storage_class_specifier declaration_specifiers */
	: type_specifier										{ $$ = $1; }
/*	| type_specifier declaration_specifiers */  
/*	| type_qualifier */
/*	| type_qualifier declaration_specifiers */
	;


init_declarator_list
	: init_declarator										{ $$ = $1; }		

	;


init_declarator
	: declarator											{ $$ = $1; }
    | declarator '=' initializer 						    { $$ = new assignment_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}					
	;


/*initializer_list is removed as arrays are an intermediate feature */
initializer
	: assignment_expression									{$$ = $1;}
	/*| '{' initializer_list '}'*/
	/*| '{' initializer_list ',' '}'*/
	;

/* TYPE_NAME is removed as TYPEDEF is an advanced feature */
/* types other than INT are removed as they are an advanced feature */
type_specifier
/*	: VOID */
/*	| CHAR */
/*	| SHORT */
  	: INT													{ $$ = new Type_Specifier(*$1); }
/*	| LONG */
/*	| FLOAT */
/*	| DOUBLE */
/*	| SIGNED */
/*	| UNSIGNED */
/*	| struct_or_union_specifier */
/*	| enum_specifier */
/*	| TYPE_NAME */
	;



/* pointer is removed as pointers are an advanced feature */		
declarator
/*	: pointer direct_declarator */
	: direct_declarator										{ $$ = $1; }
	;


/* [] are removed as arrays are an advanced feature */
/* parameter_type_list is removed as function declaration with arguments is an intermidiate feature */
/* identifier_list is removed  as function_calls are an intermediate feature */
direct_declarator
	: IDENTIFIER											{ $$ = new Identifier(*$1); } 				
	| '(' declarator ')'                                    { $$ = $2; }
	| direct_declarator '[' constant_expression ']' 		{ $$ = new Array(dynamic_cast<Identifier*>($1),dynamic_cast<expression*>($3));}
/*	| direct_declarator '[' ']' */
	| direct_declarator '(' parameter_type_list ')' 		{ $$ = new function_id_args(dynamic_cast<Identifier*>($1),dynamic_cast<parameter_list*>($3));} 
/*	| direct_declarator '(' identifier_list ')' */
	| direct_declarator '(' ')'								{ $$ = new function_id_args(dynamic_cast<Identifier*>($1),NULL); }
	;


parameter_type_list
	: parameter_list										{$$ = $1;}
/*	| parameter_list ',' ELLIPSIS */
	;

parameter_list
	: parameter_declaration									{$$ = new parameter_list( dynamic_cast<declaration*>($1));}
	| parameter_list ',' parameter_declaration				{dynamic_cast<parameter_list*>($$)->add_declaration( dynamic_cast<declaration*>($3)); }
	;

parameter_declaration
	: declaration_specifiers declarator						{$$ = new declaration(dynamic_cast<Type_Specifier*>($1),dynamic_cast<expression*>($2));}
/*	| declaration_specifiers abstract_declarator */
/*	| declaration_specifiers */
	;


compound_statement
	: '{' '}' 											    { $$ = new compound_statement( );  }
	| '{' statement_list '}'								{ $$ = new compound_statement( dynamic_cast<statement_list*>($2));  dynamic_cast<compound_statement*>($$)->update_local_scope();}
	| '{' declaration_list '}' 								{ $$ = new compound_statement( dynamic_cast<declaration_list*>($2)); dynamic_cast<compound_statement*>($$)->update_local_scope();}	
	| '{' declaration_list statement_list '}'				{ $$ = new compound_statement( dynamic_cast<declaration_list*>($2),dynamic_cast<statement_list*>($3)); dynamic_cast<compound_statement*>($$)->update_local_scope(); }
	;


declaration_list
	: declaration											{ $$ = new declaration_list( dynamic_cast<declaration*>($1)); }
	| declaration_list declaration							{ dynamic_cast<declaration_list*>($$)->add_declaration( dynamic_cast<declaration*>($2)); }
	;

statement_list
	: statement												{ $$ = new statement_list( dynamic_cast<statement*>($1)); }
	| statement_list statement								{ dynamic_cast<statement_list*>($$)->add_statement( dynamic_cast<statement*>($2)); }
	;


/* labeled_statement is removed as switch statement is an advanced feature */
/* iteration_statement is removed as for statements are intermidiate features */
statement
	: labeled_statement 									{ $$ = $1; }
	| compound_statement									{ $$ = $1; }
	| expression_statement 									{ $$ = $1; }
	| selection_statement 									{ $$ = $1; }
	| iteration_statement 									{ $$ = $1; }
	| jump_statement										{ $$ = $1; }					
	;

labeled_statement
	/*: IDENTIFIER ':' statement*/
	: CASE constant_expression ':' statement				{ $$ = new Case_statement(dynamic_cast<expression*>($2),dynamic_cast<statement*>($4),false);} 
	| DEFAULT ':' statement									{ $$ = new Case_statement(dynamic_cast<statement*>($3),true); }
	;

expression_statement
	: ';'													{}
	| expression ';'										{ $$ = new expression_statement(dynamic_cast<expression*>($1)); }
	;

/* SWITCH is removed as switch statement is an intermidiate feature */
 selection_statement 
	: IF '(' expression ')' statement 						{ $$ = new If_statement(dynamic_cast<expression*>($3),dynamic_cast<statement*>($5)); }
	| IF '(' expression ')' statement ELSE statement 		{ $$ = new If_statement(dynamic_cast<expression*>($3),dynamic_cast<statement*>($5),dynamic_cast<statement*>($7) ); }
	| SWITCH '(' expression ')' statement 					{ $$ = new Switch_statement(dynamic_cast<expression*>($3),dynamic_cast<statement*>($5));}
	; 


iteration_statement
	: WHILE '(' expression ')' statement					{ $$ = new While_statement(dynamic_cast<expression*>($3),dynamic_cast<statement*>($5)); } 
	| DO statement WHILE '(' expression ')' ';'				{ $$ = new While_statement(dynamic_cast<expression*>($5),dynamic_cast<statement*>($2),true); } 
/*	| FOR '(' expression_statement expression_statement ')' statement	*/
	| FOR '(' expression_statement expression_statement expression ')' statement  { $$ = new For_statement(dynamic_cast<expression_statement*>($3),dynamic_cast<expression_statement*>($4),dynamic_cast<expression*>($5),dynamic_cast<statement*>($7)); }
	;

/* GOTO statement is removed as it is not supported */
/* CONTINUE and BREAK are removed as they are an intermidiate feature */
/* RETURN ';' is removed as it is a beginner feature */
jump_statement
/*	: GOTO IDENTIFIER ';' */
	: CONTINUE ';' 											{ $$ = new Continue();}
	| BREAK ';' 											{ $$ = new Break();}
/*  | RETURN ';'	*/										
	| RETURN expression ';'									{   $$ = new Return( dynamic_cast<expression *>($2)); }
	;



expression
	: assignment_expression									{$$ = $1;}
	;

assignment_expression
	: conditional_expression								{ $$ = $1;}
	| unary_expression assignment_operator assignment_expression  {$$ = new assignment_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	;

assignment_operator
	: '='													{$$ = $1;}
	| MUL_ASSIGN											{$$ = $1;}
	| DIV_ASSIGN											{$$ = $1;}
	| MOD_ASSIGN											{$$ = $1;}
	| ADD_ASSIGN											{$$ = $1;}
	| SUB_ASSIGN											{$$ = $1;}
	| LEFT_ASSIGN											{$$ = $1;}
	| RIGHT_ASSIGN											{$$ = $1;}
	| AND_ASSIGN											{$$ = $1;}
	| XOR_ASSIGN											{$$ = $1;}
	| OR_ASSIGN												{$$ = $1;}
	;

constant_expression
	: conditional_expression								{$$ = $1;}
	;


/* ternary operator is removed as it is an intermidiate feature */
conditional_expression
	: logical_or_expression									{$$ = $1;}
/*	| logical_or_expression '?' expression ':' conditional_expression  */
	;

logical_or_expression
	: logical_and_expression								{$$ = $1;}
	| logical_or_expression OR_OP logical_and_expression	{$$ = new logical_or_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	;


logical_and_expression
	: inclusive_or_expression								{$$ = $1;}
	| logical_and_expression AND_OP inclusive_or_expression	{$$ = new logical_and_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	;


inclusive_or_expression
	: exclusive_or_expression								{$$ = $1;}
	| inclusive_or_expression '|' exclusive_or_expression   {$$ = new inclusive_or_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	;


exclusive_or_expression
	: and_expression										{$$ = $1;}
	| exclusive_or_expression '^' and_expression			{$$ = new exclusive_or_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	;


and_expression
	: equality_expression									{$$ = $1;}
	| and_expression '&' equality_expression				{$$ = new and_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	;


equality_expression
	: relational_expression									{$$ = $1;}
	| equality_expression EQ_OP relational_expression		{$$ = new equality_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	| equality_expression NE_OP relational_expression		{$$ = new equality_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	;
relational_expression
	: shift_expression										{$$ = $1;}
	| relational_expression '<' shift_expression			{$$ = new relational_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	| relational_expression '>' shift_expression			{$$ = new relational_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	| relational_expression LE_OP shift_expression			{$$ = new relational_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	| relational_expression GE_OP shift_expression			{$$ = new relational_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	;


shift_expression
	: additive_expression									{$$ = $1;}	
	| shift_expression LEFT_OP additive_expression			{$$ = new shift_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	| shift_expression RIGHT_OP additive_expression			{$$ = new shift_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	;

additive_expression
	: multiplicative_expression                             {$$ = $1;}
	| additive_expression '+' multiplicative_expression     {$$ = new additive_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	| additive_expression '-' multiplicative_expression     {$$ = new additive_expression(dynamic_cast<expression *>($1),*$2,dynamic_cast<expression *>($3));}
	;


multiplicative_expression
	: cast_expression                                       {$$ = $1;}
	| multiplicative_expression '*' cast_expression         {$$ = new multiplicative_expression( dynamic_cast< expression *>($1),*$2, dynamic_cast<expression *>($3));}
	| multiplicative_expression '/' cast_expression         {$$ = new multiplicative_expression( dynamic_cast< expression *>($1),*$2, dynamic_cast<expression *>($3));}
	| multiplicative_expression '%' cast_expression         {$$ = new multiplicative_expression( dynamic_cast< expression *>($1),*$2, dynamic_cast<expression *>($3));}
	;


/* cast_expression is removed as it is not supported */
cast_expression                                             
	: unary_expression                                      {$$ = $1;}
/*	| '(' type_name ')' cast_expression */
	;

/* SIZEOF is removed as it is an advanced feature */
unary_expression
	: postfix_expression                                    {$$ = $1;}
	| INC_OP unary_expression 								{$$ = new unary_expression(*$1, dynamic_cast<expression *>($2),true);}
	| DEC_OP unary_expression 								{$$ = new unary_expression(*$1, dynamic_cast<expression *>($2),true);}
	| unary_operator cast_expression                        {$$ = new unary_expression(*$1, dynamic_cast<expression *>($2));}
/*	| SIZEOF unary_expression */
/*	| SIZEOF '(' type_name ')' */
	;

/* & and * are removed as pointers are an advanced feature */
unary_operator
	/*: '&' */
	/*| '*' */
	: '+'                                                   {$$ = $1;}
	| '-'                                                   {$$ = $1;}
	| '~'                                                   {$$ = $1;}
	| '!'                                                   {$$ = $1;}
	;


/* postfix_expression '[' expression ']' removed as arrays are an intermediate feature */
/* postfix_expression '(' argument_expression_list ')', postfix_expression '(' ')' are removed as function calls are an intermidiate feature */
/* postfix_expression '.' IDENTIFIER removed as structs are an advanced feature */
/* postfix_expression PTR_OP IDENTIFIER as pointers are an advanced feature*/
postfix_expression
	: primary_expression                                    {$$ = $1;}
	  | postfix_expression '[' expression ']'				{$$ = new Array(dynamic_cast<Identifier*>($1),dynamic_cast<expression*>($3));}
	  | postfix_expression '(' ')'							{$$ = new function_call(dynamic_cast<Identifier*>($1),NULL);}
	  | postfix_expression '(' argument_expression_list ')' {$$ = new function_call(dynamic_cast<Identifier*>($1),dynamic_cast<argument_list*>($3));}
	/*| postfix_expression '.' IDENTIFIER*/
	/*| postfix_expression PTR_OP IDENTIFIER*/
	  | postfix_expression INC_OP							{$$ = new unary_expression(*$2, dynamic_cast<expression *>($1),false);}
	  | postfix_expression DEC_OP							{$$ = new unary_expression(*$2, dynamic_cast<expression *>($1),false);}
	;

argument_expression_list
	: assignment_expression									{ $$ = new argument_list( dynamic_cast<expression*>($1)); }					
	| argument_expression_list ',' assignment_expression	{ dynamic_cast<argument_list*>($$)->add_expr( dynamic_cast<expression*>($3)); }
	;

/* STRING_LITERAL is removed as it is an intermidiate feature  */
primary_expression
	: IDENTIFIER                                            { $$ = new Identifier(*$1); }
	| CONSTANT                                              { $$ = new Constant($1); }
/*	| STRING_LITERAL */
	| '(' expression ')'                                    { dynamic_cast<expression *>($2)->has_brackets(); $$ = $2; }
	;
%%

translation_unit *g_root; // Definition of variable (to match declaration earlier)
const translation_unit *parseAST()
{
  g_root = NULL;
  yyparse();
  return g_root;
}