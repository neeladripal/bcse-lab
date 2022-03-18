%{
#include <stdio.h>
int line=1, column=1;

void printLexeme (char lexeme[], char type[], int leng) {
    printf("%-10s%-30s%4d%4d\n", lexeme, type, line, column);
    column += leng;
}
%}

KEYWORD "for"|"float"|"int"
IDENTIFIER [a-zA-Z_][a-zA-Z0-9_]*
FLOATING_POINT [0-9]+.[0-9]+
INTEGER [0-9]+
ARITHMETIC_OPERATOR "++"|"--"|"+"|"-"|"*"
RELATIONAL_OPERATOR "<="|">="|"=="|"!="|"<"|">"
LOGICAL_OPERATOR "&&"|"||"
ASSIGNMENT_OPERATOR "="
OPENING_PARENTHESES "("
CLOSING_PARENTHESES ")"
OPENING_BRACES "{"
CLOSING_BRACES "}"
SEMICOLON ";"

%%
\n		                    {line++; column = 0;}
{KEYWORD}                   {printLexeme(yytext, "KEYWORD", yyleng);}
{IDENTIFIER}                {printLexeme(yytext, "IDENTIFIER", yyleng);}
{FLOATING_POINT}            {printLexeme(yytext, "FLOATING_POINT CONSTANT", yyleng);}
{INTEGER}                   {printLexeme(yytext, "INTEGER CONSTANT", yyleng);}
{ARITHMETIC_OPERATOR}       {printLexeme(yytext, "ARITHMETIC_OPERATOR", yyleng);}
{RELATIONAL_OPERATOR}       {printLexeme(yytext, "RELATIONAL_OPERATOR", yyleng);}
{LOGICAL_OPERATOR}          {printLexeme(yytext, "LOGICAL_OPERATOR", yyleng);}
{ASSIGNMENT_OPERATOR}       {printLexeme(yytext, "ASSIGNMENT_OPERATOR", yyleng);}
{SEMICOLON}                 {printLexeme(yytext, "SEMICOLON", yyleng);}
{OPENING_BRACES}            {printLexeme(yytext, "OPENING_BRACES", yyleng);}
{CLOSING_BRACES}            {printLexeme(yytext, "CLOSING_BRACES", yyleng);}
{OPENING_PARENTHESES}       {printLexeme(yytext, "OPENING_PARENTHESES", yyleng);}
{CLOSING_PARENTHESES}       {printLexeme(yytext, "CLOSING_PARENTHESES", yyleng);}
.		                    {column++;}
%%

int yywrap(void) {
    return 1;
}

int main() {
	yylex();
	return 0;
}