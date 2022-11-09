%option noyywrap

%{
    #include <iostream>
    #include <string>

    #include "c_parser.tab.hpp"

%}

/* labels */
D			[0-9]
NON_ZERO_D  [1-9]
L			[a-zA-Z]
WS          [ ]
HEX_PREFIX  [xX]
HEX_D       [0-9a-fA-F]
OCT_D       [0-7]
BIN_PREFIX  [bB]
BIN_D       [0-1]  

DECIMAL_CONSTANT (({NON_ZERO_D}({D})*)|{D})
HEX_CONSTANT     (0{HEX_PREFIX}{HEX_D}+)
OCT_CONSTANT     (0{OCT_D}+)
BIN_CONSTANT     (0{BIN_PREFIX}{BIN_D}+)


%%
    /* keywords */
"return"		{ yylval.stringptr = new std::string(yytext); return(RETURN); }
"if"		    { yylval.stringptr = new std::string(yytext); return(IF); }
"else"          { yylval.stringptr = new std::string(yytext); return(ELSE); }
"while"         { yylval.stringptr = new std::string(yytext); return(WHILE); }
"do"            { yylval.stringptr = new std::string(yytext); return(DO); }
"for"           { yylval.stringptr = new std::string(yytext); return(FOR); }
"break"         { yylval.stringptr = new std::string(yytext); return(BREAK); }
"continue"      { yylval.stringptr = new std::string(yytext); return(CONTINUE); }
"switch"        { yylval.stringptr = new std::string(yytext); return(SWITCH); }
"case"          { yylval.stringptr = new std::string(yytext); return(CASE); }
"default"          { yylval.stringptr = new std::string(yytext); return(DEFAULT); }

    /* types */
"int"			{ yylval.stringptr = new std::string(yytext); return(INT); }

    /* identifier */
{L}({L}|{D})*   { yylval.stringptr = new std::string(yytext); return(IDENTIFIER);}

    /* constants */
{DECIMAL_CONSTANT}  {yylval.number = atoi(yytext); return(CONSTANT);}
{HEX_CONSTANT}      {yylval.number = (int)strtol(yytext, NULL, 16); return(CONSTANT);}
{OCT_CONSTANT}      {std::string no_prefix = yytext; no_prefix = no_prefix.substr(1,std::string::npos)  ; yylval.number = (int)strtol(no_prefix.c_str(), NULL, 8); return(CONSTANT);}
{BIN_CONSTANT}      {std::string no_prefix = yytext; no_prefix = no_prefix.substr(2,std::string::npos)  ; yylval.number = (int)strtol(no_prefix.c_str(), NULL, 2); return(CONSTANT);}

{WS}|\n         { }

    /* operators */
"<<"            {yylval.stringptr = new std::string(yytext); return(LEFT_OP);}
">>"            {yylval.stringptr = new std::string(yytext); return(RIGHT_OP);}
"<="            {yylval.stringptr = new std::string(yytext); return(LE_OP);}
">="            {yylval.stringptr = new std::string(yytext); return(GE_OP);}
"=="            {yylval.stringptr = new std::string(yytext); return(EQ_OP);}
"!="            {yylval.stringptr = new std::string(yytext); return(NE_OP);}
"&&"            {yylval.stringptr = new std::string(yytext); return(AND_OP);}
"||"            {yylval.stringptr = new std::string(yytext); return(OR_OP);}


"*="            {yylval.stringptr = new std::string(yytext); return(MUL_ASSIGN);}
"/="            {yylval.stringptr = new std::string(yytext); return(DIV_ASSIGN);}
"%="            {yylval.stringptr = new std::string(yytext); return(MOD_ASSIGN);}
"+="            {yylval.stringptr = new std::string(yytext); return(ADD_ASSIGN);}
"-="            {yylval.stringptr = new std::string(yytext); return(SUB_ASSIGN);}
"<<="           {yylval.stringptr = new std::string(yytext); return(LEFT_ASSIGN);}
">>="           {yylval.stringptr = new std::string(yytext); return(RIGHT_ASSIGN);}
"&="            {yylval.stringptr = new std::string(yytext); return(AND_ASSIGN);}
"^="            {yylval.stringptr = new std::string(yytext); return(XOR_ASSIGN);}
"|="            {yylval.stringptr = new std::string(yytext); return(OR_ASSIGN);}

"++"            {yylval.stringptr = new std::string(yytext); return(INC_OP);}
"--"            {yylval.stringptr = new std::string(yytext); return(DEC_OP);}

.               {yylval.stringptr = new std::string(yytext); return yytext[0];}


%%



int check_type()
{
/*
* pseudo code --- this is what it should check
*
*	if (yytext == type_name)
*		return(TYPE_NAME);
*
*	return(IDENTIFIER);
*/

}

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}

