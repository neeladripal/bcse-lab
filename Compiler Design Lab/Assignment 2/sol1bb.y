%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex(void);
    void yyerror(char *);
%}

%token A B

%%
stmt:   A stmt B
        |
        ;
%%

void yyerror(char *s) {
    printf("Invalid String\n");
    exit(0);
}

int main() {
    yyparse();
    printf("Valid string\n");
    return 0;
}