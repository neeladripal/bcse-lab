%{
    #include <stdlib.h>
    #include "y.tab.h"
    extern float yylval;
%}

%%
[0-9]+(\.[0-9]?[0-9])?  {yylval = atof(yytext); return NUMBER;}
\n                      return 0;
[ \t]                   ;
.                       return yytext[0];
%%

int yywrap() {
    return 1;
}