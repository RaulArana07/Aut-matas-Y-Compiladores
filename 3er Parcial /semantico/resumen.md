# Analizador Semántico

## Teoría

El analizador semántico es la fase del compilador que verifica que el programa fuente cumpla con las reglas semánticas del lenguaje (más allá de la sintaxis). Mientras el analizador sintáctico comprueba la forma (gramática), el semántico comprueba el significado.

### Funciones principales
* **Comprobar tipos de datos:** Asegura la coherencia en operaciones, asignaciones y parámetros.
* **Verificar declaraciones:** Garantiza que las variables estén declaradas antes de ser usadas y la unicidad de los nombres.
* **Gestionar ámbitos:** Controla los *scopes* y las tablas de símbolos.
* **Detectar errores semánticos:** Identifica fallos como un índice de array no entero o una función sin instrucción `return`.

### Representación interna
* **AST (Árbol de Sintaxis Abstracta):** Enriquecido con atributos como tipo, dirección y valor.
* **Tabla de símbolos:** Estructura donde se almacena la información de los identificadores (tipo, alcance, dimensión, etc.).

> **Base teórica:** Se fundamenta en gramáticas de atributos (Knuth), esquemas de traducción dirigida por sintaxis y sistemas de tipos.

---

## Herramientas / Técnicas

### Esquemas de traducción dirigida por sintaxis (SDTS)
1. Asocian reglas semánticas (acciones) a cada producción gramatical.
2. Se integran directamente en el analizador sintáctico, ya sea descendente o ascendente.

### Recorrido del AST
* **Recorrido post-orden:** Utilizado para evaluar atributos heredados y sintetizados.
* **Patrones de diseño:** Uso de patrones de visita (*Visitor*) en implementaciones orientadas a objetos.

### Generadores de analizadores semánticos
* **YACC / Bison:** Con acciones en C/C++.
* **ANTLR:** Permite acciones en lenguajes como Java o Python, además de la construcción de AST.
* **Lex/Yacc:** Combinado con bibliotecas de manejo de símbolos.

### Técnicas de comprobación de tipos
* Inferencia de tipos (como Hindley-Milner en lenguajes funcionales).
* Unificación.
* Comprobación estática vs. dinámica.

### Herramientas auxiliares
* Tablas de símbolos implementadas con hash o listas encadenadas por ámbito.
* Atributos sintetizados (fluyen de hijos a padre) y heredados (fluyen de padre a hijos).

---

## Manejo de Errores

El analizador semántico detecta errores que no puede capturar la sintaxis utilizando ciertos métodos o estrategias. La salida esperada es una **lista de errores con número de línea, columna y descripción legible**.

### Tipos de errores típicos (Declaración de errores)
1. Variable no declarada.
2. Declaración duplicada.
3. Tipo incompatible (ej. entero + string, o asignar a una variable una función que retorna `void`).
4. Número incorrecto de argumentos.
5. Uso de un identificador que no es de función como si lo fuera.

### Estrategias de recuperación de errores
* **Modo pánico:** Se ignora el resto de la unidad semántica actual (ej. toda la expresión) y se continúa con la siguiente.
* **Corrección local:** Consiste en insertar o eliminar símbolos (ej. declarar automáticamente la variable omitida).
* **Propagación de errores:** Se asigna un tipo especial `error` a la expresión para evitar una cascada innecesaria de mensajes de error.
* **Registro en tabla de símbolos:** Se marcan los identificadores erróneos para no volver a reportarlos en las siguientes líneas.

---

## ¿Cómo se construye?

Pasos prácticos para implementar un analizador semántico:

1. **Definir la tabla de símbolos:**
   * Estructura básica: `Symbol { name, type, scope, line }`.
   * Controlar ámbitos anidados mediante una pila de tablas.

2. **Extender el parser:**
   * Insertar acciones semánticas dentro de las reglas gramaticales.
   * *Ejemplo (pseudocódigo):* ```
     declaracion: tipo ID ';' { agregarSimbolo($2, $1); }
     ```

3. **Construir el AST (opcional pero recomendado):**
   * Cada nodo contiene su tipo, hijos y atributos.
   * Al final del *parsing*, el árbol se recorre para realizar comprobaciones complejas (ej. flujo de control, retornos).

4. **Implementar comprobación de tipos:**
   * Crear una función `check_types(expr)` que retorne el tipo resultante o un error.
   * *Regla de ejemplo:* Si es una `op_aritmetica`, ambos operandos deben ser numéricos.

5. **Recorrido y evaluación:**
   * Si se usan atributos heredados, se realiza un recorrido en profundidad con parámetros.
   * Si solo se emplean atributos sintetizados, basta con un recorrido post-orden.

6. **Generación de código intermedio (opcional):**
   * El análisis semántico puede producir código de tres direcciones o construir el árbol decorado necesario para la siguiente fase del compilador.

---

## Referencias

* Alfonseca, M. (2006). *Compiladores e intérpretes: teoría y práctica*.
* Catalán, J. R. (2008). *Compiladores: Teoría y práctica con Java, JLex, CUP y ENS2001*. Lulu.com.
