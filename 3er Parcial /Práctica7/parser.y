%{
#include <stdio.h>
int yylex();
int yyerror(const char *s) {
    printf("Expresion NO valida\n");
    return 0;
}
%}

%token ENTERO DECIMAL SIMBOLO COMPARACION ID EOL CONDIF CONDELSE
%left SIMBOLO
%left COMPARACION
%left CONDIF
%start input

%%

// ENTRADA AL INICIO DEL PROGRAMA
input:
      input cond EOL { printf("Expresion valida\n"); }
    | /* vacío */
;

// VALIDACION DE EXPRESIONES PARA EL IF
expr:
      expr SIMBOLO expr
    | expr COMPARACION expr
    | '(' expr ')'
    | ENTERO
    | DECIMAL
    | ID
;

cond: 
      CONDIF '(' expr ')' '{' '}'
      | CONDIF '(' expr ')' '{' '}' CONDELSE '{' '}'
;
%%

extern FILE *yyin; 

int main() {
    yyin = fopen("entrada.txt", "r");  // archivo de entrada

    if (!yyin) {
        printf("Error al abrir archivo\n");
        return 1;
    }

    yyparse();

    fclose(yyin);
    return 0;
}
