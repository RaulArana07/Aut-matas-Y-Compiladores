%option noyywrap
%{
#include <stdio.h>
%}

%%

[0-9]+    { printf("ENTERO=%s\n", yytext); }

[ \t\n]   ;

.         ;

%%

int main(){
    yylex();
    return 0;
}
