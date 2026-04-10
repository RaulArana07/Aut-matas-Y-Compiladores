%option noyywrap
%{
#include <stdio.h>
%}

%%

[0-9]+"."[0-9]+    { printf("DECIMAL=%s\n", yytext); }

[ \t\n]            ;

.                  ;

%%

int main(){
    yylex();
    return 0;
}
