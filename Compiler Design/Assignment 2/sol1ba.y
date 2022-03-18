%{
    #include <stdio.h>
    #include <stdlib.h>
    int yylex(void);
    void yyerror(char *);
%}

%token A B

%%
stmt:   e f ;
e:      A | e A ;
f:      B | f B ;
%%

void yyerror(char *s) {
    printf("Invalid String\n");
    exit(0);
}

int main() {
    yyparse();
    printf("Valid String\n");
    return 0;
}