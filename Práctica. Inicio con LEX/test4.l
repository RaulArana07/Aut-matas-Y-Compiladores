%option noyywrap
%{
#include <stdio.h>
%}

%%

[A-Z]{4}[0-9]{6}[A-Z0-9]{3}   { printf("RFC=%s\n", yytext); }

[ \t\n]   ;

.         ;

%%

int main(){
    yylex();
    return 0;
}
