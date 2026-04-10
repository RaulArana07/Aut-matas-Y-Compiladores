## Introducción
Algunas de las funciones del análisis léxico son: 
**Lee caracteres. 
- Produce componentes léxicos (tokens). 
- Filtra comentarios. 
- Filtra separadores múltiples (espacios, tabuladores y saltos de línea). 
- Lleva el contador de línea y columna del texto fuente. 
- Genera errores en caso de que la entrada no corresponda a ninguna categoría léxica. 
 
Para realizar dichas funciones, es importante tomar en cuenta los siguientes conceptos: 
Categoría léxica. Tipo de símbolo elemental del lenguaje fuente, (identificadores, palabras clave, constantes numéricas, operadores, ...). 
Componente léxico (token). Elemento perteneciente a una categoría léxica. 
Lexema. Cadena de caracteres correspondiente al componente léxico. 
 
Además, las categorías léxicas más comunes son: 
Palabras clave. Palabras con un significado especial en el lenguaje 
(if, then, else, for, while, do, switch, case, ...) También se nombran como palabras reservadas. 
Identificadores. Nombres de variables, de constantes, de funciones, de tipos... (media, valor0, i1, _PI, ...)  
 **Operadores**. Símbolos que identifican operaciones aritméticas y lógicas. 
( + , - , * , / , %, = , ++ , -- , += , -= , *= , /= , == , !=, && , || , & , | , ...) 

**Constantes numéricas.** Literales que especifican valores numéricos. 
(325, 3.141592, 0xA3F2, 0.2e+3) 
**Constantes de carácter o cadenas.** Literales con el valor de un carácter o de una cadena  (‘z’, ‘\n’, “ejemplo de cadena”, ...) 
**Símbolos especiales.** Separadores, delimitadores, terminadores, etc. 
( { , }, [ , ] , ( , ) , ; , , )

**Blancos.** Caracteres de separación de componentes léxicos 
(espacios, tabuladores, saltos de línea) 
El análisis léxico se limita a suprimirlos. 

**Comentarios.*** Información para el lector del programa. 
(/* comentario multilínea * /, // comentario de una línea \n, /** comentario para la documentación* / ) 
El análisis léxico los elimina. 
**Fin de entrada.** Componente ficticio que indica el final de lectura

## Marco Teorico
#### Análisis Léxico
El análisis léxico lee el flujo de caracteres de entrada y los agrupa en *tokens*. Cada token representa una unidad atómica con significado en el lenguaje, como un identificador, un número o un operador. Durante este proceso, el analizador léxico también filtra comentarios, espacios en blanco y otros separadores, y opcionalmente lleva un conteo de líneas y columnas para la localización de errores.

#### Lex
Lex es un generador de analizadores léxicos que, a partir de un archivo de especificaciones (reglas con expresiones regulares y acciones en C), produce un programa en C (`yylex()`) que reconoce los patrones definidos. La estructura de un archivo Lex es:
1. **Sección de definiciones**: Opciones, includes, variables y definiciones de expresiones regulares.
2. **Sección de reglas**: Patrón seguido de acción (código C a ejecutar al coincidir).
3. **Sección de código de usuario**: Funciones adicionales, como `main()`.
#### Componentes Léxicos
- **Categoría léxica**: Tipo de símbolo elemental (palabra clave, identificador, constante, operador, etc.).
- **Token**: Elemento perteneciente a una categoría léxica (ej. `NUM_ENTERO`).
- **Lexema**: Secuencia real de caracteres que coincide con el token (ej. `"123"`).
## Objetivo General
Desarrollar un programa en Lex que, dado un archivo de texto con código escrito en el lenguaje de programación C++, sea capaz de identificar y clasificar diversos elementos del lenguaje de alto nivel (como palabras reservadas, comentarios, operadores lógicos y aritméticos, e identificadores) mediante la definición de reglas para el análisis léxico.

## Objetivos Específicos
- Diseñar las expresiones regulares necesarias en Lex para identificar las palabras reservadas de C++, los operadores aritméticos y lógicos, y los comentarios.
- Implementar un analizador léxico en Lex que procese el archivo de texto, identificando y clasificando correctamente los tokens definidos.  
- Validar el funcionamiento del programa ejecutándolo sobre diferentes fragmentos de código en C++ para asegurar que todos los elementos del lenguaje sean reconocidos adecuadamente.

## Desarrollo de la practica
#### a. Palabras reservadas
Son palabras con significado especial en C++ que no pueden usarse como nombres de variables.
#### b. Comentarios
Texto que el compilador ignora. El analizador debe detectarlos y contarlos.
**Tipos:**
- `// comentario de línea`
- \ /\ /.*
- `/* comentario de bloque */`
-  \ /  \ * ([ ^ * ]| \ * + [ ^ */])*\ *+\ / 
**Para contarlos:** Se agrega una variable `contador_comentarios++` dentro de cada regla. 

#### c. Nombres de las variables
Nombres que el programador asigna a variables, funciones, etc.
**Reglas:**
- Comienza con letra o _
- Sigue con letras, números o _
- ***{LETRA}({LETRA}|{DIGITO})****
#### d. Operadores aritméticos
Realizan operaciones matemáticas.
#### e. Operadores lógicos
Se usan en condiciones y comparaciones.
***(\ +\ +|--| == |!=|<=|>=|\ +|-|\ *|\ /|=|<|>|\ |\ ||&&|!)***

#### Estructura del código
El código del analizador léxico en Lex tiene tres partes. En la primera parte se definen las opciones, se incluyen las librerías necesarias, se crea un contador de líneas y una función para imprimir los tokens. 

En la segunda parte están las reglas. Cada regla tiene un patrón y una acción. Por ejemplo, al encontrar un salto de línea se aumenta el contador al encontrar una palabra reservada se escribe “Palabra reservada”, al encontrar un operador se escribe “operador” y así sucesivamente con cada una de las reglas. Los espacios y tabuladores se ignoran, y cualquier carácter no reconocido se reporta como error.

En la tercera parte está el programa principal. Este abre un archivo de entrada llamado `archivo.cpp` y un archivo de salida llamado `MyScanner.txt`. Luego ejecuta el analizador con `yylex()`, cierra los archivos y muestra un mensaje de finalización.

## Cuestionario
1. ¿Qué patrones se deben definir para identificar correctamente los tokens de números, operadores aritméticos y lógicos?
- Números enteros: [0-9]+
- Números flotantes: [0-9]+\.[0-9]+([eE][+-]?[0-9]+)?
- Operadores aritméticos: +, -, *, /, =, ++, --, +=, -=, etc.
- Operadores lógicos: == , !=, <, >, <=, >=, &&, ||, !

2. ¿Cuál es el proceso que seguiste para analizar las cadenas de símbolos y reconocer los tokens?
- Leer el archivo de código fuente carácter por carácter, agrupamos caracteres según expresiones regulares y cuando un patrón coincide se genera un token con su categoría. Después se ignoran espacios, tabuladores y comentarios. Tambien si ningún patrón coincide se reporta un error léxico y continuamos hasta el final del archivo.

3. ¿Qué elementos de la herramienta Lex te permitieron implementar las reglas para el análisis léxico?
- La sección de definiciones, la sección de reglas, variables especiales como yytext, yyin/yyout, la función yylex() y %option noyywrap

4. ¿Qué condiciones o recomendaciones se deben seguir al plantear las reglas para identificar los tokens?
- Es importante ordenar las reglas de la más específica a la más general. Por ejemplo, las palabras reservadas deben ir antes que los identificadores porque un identificador también podría coincidir con if si no se prioriza la palabra clave. Evitar reglas muy generales

5. ¿Cómo se logró identificar errores léxicos y qué estrategias utiliza para recuperarse de ellos?
- Los errores léxicos se identifican mediante una regla especial que captura cualquier carácter no reconocido por los demás patrones y la forma en la que se recupera de ellos es: se reporta el error y se continúa con el siguiente carácter sin detener el análisis permitiendo que el analizador procese todo el archivo y encuentre todos los errores en una sola ejecución en lugar de detenerse en el primero. 
## Resultados
La salida generada es un archivo de texto titulado MyScanner donde se almacenaron los tokens identificados,  acompañada de la linea en la que se encuentra cada uno. Se marcan los errores encontrados y se hace un conteo de la cantidad de comentarios en el archivo de entrada.
## Conclusiones
Se desarrolló con éxito un analizador léxico funcional en Lex capaz de reconocer un subconjunto significativo del lenguaje C++ incluyendo palabras reservadas, identificadores, constantes numéricas en diversas bases, operadores aritméticos y lógicos, separadores, cadenas, caracteres y comentarios. Finalizamos  con que cumple con los objetivos planteados.
## Bibliografía
- Giró, J., Vázquez, J., Meloni, B., Constable, L. (2015). _Lenguajes formales y teoría de automátas_. Editorial Alfaomega. Argentina.
- Ruiz Catalán, J. (2010). _Compiladores: teoría e implementación_. Editorial Alfaomega. México.
- Brookshear, J. G. (1995). _Teoría de la Computación. Lenguajes formales, autómatas y complejidad_. Editorial Addison-Wesley Iberoamericana. Primera edición. U.S.A.
