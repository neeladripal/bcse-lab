%{
#include <stdio.h>
%}

%%
A       return A;
B       return B;
\n      return 0;
.       ;
%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    return 0; 
}