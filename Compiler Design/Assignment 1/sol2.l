%{
#include <stdio.h>
int integers=0, floats=0;
%}

%%
\n
[0-9]+\.[0-9]+				{floats++; printf("FLoat: %s\n", yytext);}
[0-9]+						{integers++; printf("Integer: %s\n", yytext);}
.							;
%%

int yywrap(void){
    return 1;
}

int main()
{
	yylex();
	
	printf("Integer count: %d\n", integers);
	printf("Float count: %d\n", floats);
	
	return 0;
}