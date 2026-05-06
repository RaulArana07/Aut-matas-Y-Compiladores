%option noyywrap
%{
#include <stdio.h>
#include "parser.tab.h"
%}

%%
[0-9]+                  { return ENTERO; }
[0-9]+\.[0-9]+          { return DECIMAL; }
[+\-*\/]                { return SIMBOLO; }
(==|!=|<=|>=|<|>)       { return COMPARACION; }
if                      { return CONDIF; }
else                    { return CONDELSE; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
"("                     { return '('; }
")"                     { return ')'; }
"{"                     { return '{'; }
"}"                     { return '}'; }
[ \t]                   { }        // ignorar espacios
\n                      { return EOL; }

%%
