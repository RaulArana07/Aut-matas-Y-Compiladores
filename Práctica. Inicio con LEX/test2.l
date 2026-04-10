%option noyywrap
%{
#include <stdio.h>
%}

%%

[A-Za-z][A-Za-z0-9_]*    { printf("ID=%s\n", yytext); }

[ \t\n]   ;

.         ;

%%

int main(){
    yylex();
    return 0;
}
