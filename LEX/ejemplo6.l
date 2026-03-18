%option noyywrap
%{
#include <stdio.h>
%}

%%

[A-Za-z][A-Za-z0-9]*@uaeh\.edu\.mx   { printf("EMAIL=%s\n", yytext); }

[ \t\n]   ;

.         ;

%%

int main(){
    yylex();
    return 0;
}