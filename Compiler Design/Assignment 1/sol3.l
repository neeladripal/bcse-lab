%{
#include <stdio.h>
int words=0;
%}

%%
[aeiouAEIOU][a-zA-Z0-9]*		{words++; printf("%s\n", yytext);}
[a-zA-Z0-9]*					;	
. 								;
%%

int yywrap(void){
    return 1;
}

int main()
{
	yylex();
	printf("Number of words starting with vowels: %d\n", words);
	return 0;
}