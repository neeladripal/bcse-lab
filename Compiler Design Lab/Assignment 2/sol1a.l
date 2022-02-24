%{
#include <stdio.h>
%}

%%
\n          return 0; 
[A]+[B]+\n  return 1; 
.           ;
%%

int yywrap() {
    return 1;
}

int main() {
    int ok = yylex();
    if (ok)
        printf("Valid String.\n"); 
    else
        printf("Invalid String.\n"); 
    return 0; 
}