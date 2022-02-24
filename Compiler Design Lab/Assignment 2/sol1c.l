%{
    #include <stdio.h>
    int c = 0;
%}

%%
A           c++;
B           c--;
\n          return 0;
.           ;
%%

int yywrap() {
    return 1;
}

int main() {
    yylex();
    if (c == 0)
        printf("Valid String.\n"); 
    else
        printf("Invalid String.\n"); 
    return 0; 
}