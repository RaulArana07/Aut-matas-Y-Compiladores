#include <iostream>
#include <string>
#include <regex>
#include <sstream>

using namespace std;

int main() {
    string linea;
    
    cout << "EXPRESIONES REGULARES.\n\n ";
    cout << "Ingresa una o varias palabras: ";
    getline(cin, linea);

    regex minusculas("^[a-z]+$");
    regex mayusculas("^[A-Z]+$");
    regex numero("^[0-9]+$");
    regex identificador("^[A-Za-z_][A-Za-z0-9_]*$");

    stringstream ss(linea);
    string palabra;

    while (ss >> palabra) {
        cout << "Palabra: " << palabra ;

        if (regex_match(palabra, numero)) {
            cout << " es un numero entero.";
        }
        else if (regex_match(palabra, minusculas)) {
            cout << " esta escrita en minusculas.";
        }
        else if (regex_match(palabra, mayusculas)) {
            cout << " esta escrita en mayusculas.";
        }
        else if (regex_match(palabra, identificador)) {
            cout << " es un identificador valido.";
        }
        else {
            cout << " no cumple con ninguna categoria.";
        }

        cout << endl;
    }
    
    return 0;
}
