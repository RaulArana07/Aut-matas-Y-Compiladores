import java.util.regex.*;
import java.util.*;
import java.nio.file.*;
import java.io.IOException;

public class KeywordsIdentifiers {

    // Tipos de token
    enum TokenType { JAVADOC, KEYWORD, IDENTIFIER, WHITESPACE, OPERATOR, SEPARATOR, FLOATLIT, HEXADECIMALLIT, BINARYLIT, OCTALLIT, INTEGERLIT, STRINGLIT, CHARLIT, UNKNOWN }
    
    // Record para representar un Token (Java 16+)
    record Token(TokenType type, String lexeme, int line) {
        public String toString() {
            return String.format("[L%-3d] %-14s --> \"%s\"", line, type, lexeme);
        }
    }
    
    static class LexicalError extends RuntimeException {
        private final int line, column;
        private final char illegal;

    public LexicalError(char c, int line, int col) {
        super(String.format(
            "Error léxico [línea %d, col %d]: carácter ilegal '%c' (U+%04X)",
            line, col, c, (int) c
        ));
        this.line = line; this.column = col; this.illegal = c;
        }
    }

static record Result(List<Token> tokens, List<LexicalError> errors) {}

    // Patrón de keywords (todas las palabras reservadas de Java)
    static final String KW_PATTERN =
        "\\b(main|abstract|assert|boolean|break|byte|case|catch|char|" +
        "class|const|continue|default|do|double|else|enum|extends|" +
        "final|finally|float|for|if|implements|import|instanceof|" +
        "int|interface|long|new|package|private|protected|public|" +
        "return|short|static|super|switch|synchronized|this|throw|" +
        "throws|try|void|volatile|while|true|false|null)\\b";

        // Patrón MASTER con grupos nombrados
    static final Pattern MASTER = Pattern.compile(
        "(?<JAVADOC>/\\*\\*[\\s\\S]*?\\*/)|" +
        "(?<BLOCKCOMMENT>/\\*[\\s\\S]*?\\*/)|" +
        "(?<LINECOMMENT>//[^\\n]*)|" +
        "(?<STRINGLIT>\"([^\"\\\\]|\\\\.)*\")|" +
        "(?<CHARLIT>'([^'\\\\]|\\\\.)')|" +
        "(?<FLOATLIT>[0-9][0-9_]*\\.[0-9][0-9_]*([eE][+-]?[0-9]+)?[fFdD]?)|" +
        "(?<HEXADECIMALLIT>0[xX][0-9a-fA-F][0-9a-fA-F_]*[lL]?)|" +
        "(?<BINARYLIT>0[bB][01][01_]*[lL]?)|" +
        "(?<OCTALLIT>0[0-7]+[lL]?)|" +
        "(?<INTEGERLIT>0|[1-9][0-9_]*[lL]?)|" +
        "(?<KEYWORD>" + KW_PATTERN + ")|" +
        "(?<IDENTIFIER>[a-zA-Z_$][a-zA-Z0-9_$]*)|" +
        "(?<OPERATOR>==|!=|<=|>=|&&|\\|\\||<<|>>>|>>|\\+\\+|--|\\+=|-=|\\*=|/=|[+\\-*/%<>=!&|^~?:])|" +
        "(?<SEPARATOR>[(){}\\[\\];,.])|" +
        "(?<WHITESPACE>[ \\t\\r\\n]+)",
        Pattern.MULTILINE
    );

    // Método de Tokenización
    public static Result tokenize(String source) {
        List<Token> tokens = new ArrayList<>();
        List<LexicalError> errors = new ArrayList<>();
        Matcher m = MASTER.matcher(source);
        int line = 1, pos = 0;

        while (m.find()) {
            // Detectar caracteres no reconocidos
            if (m.start() > pos) {
                String illegal = source.substring(pos, m.start());
                int col = pos - source.lastIndexOf('\n', pos);
                System.err.printf("Error léxico [L%d, C%d]: '%s'%n", line, col, illegal);
                errors.add(new LexicalError(illegal.charAt(0), line, col));
            }
            if (m.group("WHITESPACE") != null) {
                line += m.group("WHITESPACE").chars().filter(c -> c == '\n').count();

            } else if (m.group("JAVADOC") != null) {
                tokens.add(new Token(TokenType.JAVADOC, m.group(), line));

            } else if (m.group("KEYWORD") != null) {
                tokens.add(new Token(TokenType.KEYWORD, m.group(), line));

            } else if (m.group("IDENTIFIER") != null) {
                tokens.add(new Token(TokenType.IDENTIFIER, m.group(), line));

            } else if (m.group("OPERATOR") != null) {
                tokens.add(new Token(TokenType.OPERATOR, m.group(), line));

            } else if (m.group("SEPARATOR") != null) {
                tokens.add(new Token(TokenType.SEPARATOR, m.group(), line));

            } else if (m.group("FLOATLIT") != null){
                tokens.add(new Token(TokenType.FLOATLIT, m.group(), line));

            } else if (m.group("HEXADECIMALLIT") != null) {
                tokens.add(new Token(TokenType.HEXADECIMALLIT, m.group(), line));

            } else if (m.group("BINARYLIT") != null){
                tokens.add(new Token(TokenType.BINARYLIT, m.group(), line));

            } else if (m.group("OCTALLIT") != null){
                tokens.add(new Token(TokenType.OCTALLIT, m.group(), line));

            } else if (m.group("INTEGERLIT") != null){
                tokens.add(new Token(TokenType.INTEGERLIT, m.group(), line));

            } else if (m.group("STRINGLIT") != null){
                tokens.add(new Token(TokenType.STRINGLIT, m.group(), line));

            } else if (m.group("CHARLIT") != null){
                tokens.add(new Token(TokenType.CHARLIT, m.group(), line));
            }
            pos = m.end();
        }
        return new Result(tokens, errors);
    }

    public static void main(String[] args) {
        try {
            String inputPath = "Ejemplo.java";
            String outputPath = "salida.txt";
            String source = Files.readString(Path.of(inputPath));
            Result result = tokenize(source);
            List<String> lines = new ArrayList<>();
            for (Token t : result.tokens) {
                lines.add(t.toString());
            }
            lines.add("Errores Lexicos");
            for (LexicalError e : result.errors) {
                lines.add(e.getMessage());
            }
            Files.write(Path.of(outputPath),lines);
            System.out.println("Archivo de salida.txt generado");
        } catch (IOException e) {
            System.err.println("Error en el archivo de entrada");
        }
    }
}