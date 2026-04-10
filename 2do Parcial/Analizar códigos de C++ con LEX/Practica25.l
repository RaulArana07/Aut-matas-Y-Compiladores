%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>

int linea = 1;
int num_comentarios = 0;

void write_token(const char* token){
    fprintf(yyout, "[L%-3d] %-14s --- \"%s\"\n", linea, token, yytext);
}
%}

DIGITO	[0-9]
LETRA	[a-zA-Z_]
ID	{LETRA}({LETRA}|{DIGITO})*
ENTERO	{DIGITO}+
FLOTANTE	{DIGITO}+"."{DIGITO}+([eE][+-]?{DIGITO}+)?
HEXA	0[xX][0-9a-fA-F]+
OCTAL	0[0-7]+
BINARIO	0[bB][01]+
CADENA	\"([^\\\"]|\\.)*\"
CARACTER        \'([^\\\']|\\.)\'
OPERADOR	(\+\+|--|==|!=|<=|>=|\+|-|\*|\/|=|<|>|\|\||&&|!)
SEPARADOR	[;,(){}\[\]]
COMENT_LINEA    \/\/.*
COMENT_BLOQUE   \/\*([^*]|\*+[^*/])*\*+\/

RESERVADAS	(int|float|double|char|if|else|while|for|return|void|class|public|private|protected|include|using|namespace|std|cout|cin|switch|case|break|default|do)

%%

\n              { linea++; }

{RESERVADAS}        { write_token("Palabra reservada"); }
{HEXA}              { write_token("Num Hexa"); }
{BINARIO}           { write_token("Num binario"); }
{OCTAL}             { write_token("Num octal"); }
{FLOTANTE}          { write_token("Num Flotante"); }
{ENTERO}            { write_token("Num Entero"); }
{ID}                { write_token("Identificador"); }
{CADENA}            { write_token("Cadena"); }
{CARACTER}          { write_token("Caracter"); }
{OPERADOR}          { write_token("operador"); }
{SEPARADOR}         { write_token("separador"); }
{COMENT_LINEA}      { write_token("COMENTARIO_LINEA"); 
                        num_comentarios++;}
{COMENT_BLOQUE}     { write_token("COMENTARIO_BLOQUE"); 
                        num_comentarios++;}

[ \t\r]+            {}

.                   { fprintf(yyout,"Error: %s\n",yytext); }

%%

int main(int argc, char *argv[]){
    yyin = fopen("codigo.cpp","r");
    if(!yyin){
        printf("No se encontro el archivo de entrada\n");
        return 1;
    }

    yyout = fopen("MyScanner.txt","w");
    if(!yyout){
        printf("Error en el archivo de salida\n");
        return 1;
    }

    yylex();
    fprintf(yyout, "Comentario(s) #%d\n", ++num_comentarios);
    fclose(yyin);
    fclose(yyout);

    printf("Fin del programa\n");
    return 0;
}