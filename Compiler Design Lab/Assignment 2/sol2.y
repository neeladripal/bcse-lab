%{
    #include <stdio.h>
    #include <stdlib.h>
    #define YYSTYPE float
    int yylex(void);
    void yyerror(char *);
%}

%token NUMBER
%left '+' '-'
%left '*'
%left '&' '|'
%left '(' ')'
%left neg

%%
prog:   expr                {printf("Result = %.2f\n", $$);}
        ;         
expr:   expr '+' expr       {$$ = $1 + $3;}
        | expr '-' expr     {$$ = $1 - $3;}
        | expr '*' expr     {$$ = $1 * $3;}
        | expr '|' expr     {$$ = (int)$1 | (int)$3;}
        | expr '&' expr     {$$ = (int)$1 & (int)$3;}
        | '(' expr ')'      {$$ = $2;}
        | '-' expr          %prec neg {$$ = -$2;}
        | NUMBER            {$$ = $1;}
        ;
%%

void yyerror(char *s) {
    printf("Invalid expression.\n");
    exit(0);
}

int main() {
    yyparse();
    return 0;
}