%{
#include <stdio.h>
int lines=0, words=0, characters=0;
%}

%%
\n		    {lines++;}
[^ \t\n]+	{words++; characters+=yyleng;}
.		    {characters++;}
%%

int yywrap(void) {
    return 1;
}

int main() {
	yylex();
	
	printf("Line count: %d\n", lines);
	printf("Word count: %d\n", words);
	printf("Character count: %d\n", characters);
	
	return 0;
}