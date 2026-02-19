#include <iostream>
#include <fstream>
#include <regex>
#include <string>

using namespace std;

int main() {

    ifstream entrada("entradas.txt");
    ofstream salida("salidas.txt");

    if (!entrada.is_open()) {
        cout << "Error abrir el archivo de entrada.\n";
        return 1;
    }

    if (!salida.is_open()) {
        cout << "Error al crear el archivo de salida.\n";
        return 1;
    }

    string linea;
    regex encabezado("^###(CURP|RFC|INE) n=([0-9]+)$");

    while (getline(entrada, linea)) {
        smatch match;

        if (regex_match(linea, match, encabezado)) {

            string tipo = match[1];
            int cantidad = stoi(match[2]);
            

            salida << "\n" << tipo;

            for (int i = 0; i < cantidad; i++) {

                if (getline(entrada, linea)) {

                    bool valido = false;

                    if (tipo == "CURP")
                        valido = CURP(linea);
                    else if (tipo == "RCF")
                        valido = RFC(linea);
                    else if (tipo == "INE")
                        valido = INE(linea);

                    salida << linea << "	"<< (valido ? "VALIDO" : "NO VALIDO")<< endl;
                }
            }
        }
    }
    cout<< "Revisar validaciones en salidas.txt";
    
    entrada.close();
    salida.close();

    return 0;
}


bool CURP(string curp) {
    regex patron("^[A-Z]{4}[0-9]{6}[A-Z0-9]{8}$");
    return regex_match(curp, patron);
}

bool	RFC(string rfc) {
    regex patron("^[A-Z]{4}[0-9]{6}[A-Z0-9]{3}$");
    return regex_match(rfc, patron);
}

bool INE(string ine) {
    regex patron("^[0-9]{13}$");
    return regex_match(ine, patron);
}

