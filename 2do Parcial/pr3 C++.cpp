#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream archivo("afd.txt");

    if (!archivo.is_open()) {
        cout << "No se puede abrir el archivo" << endl;
        return 1;
    }

    int N, S, D, q0, T, C;

    archivo >> N >> S >> D >> q0 >> T >> C;

    char alfabeto[100];
    for (int i = 0; i < S; i++) {
        archivo >> alfabeto[i];
    }

    bool fin[101] = {false};
    for (int i = 0; i < T; i++) {
        int estado;
        archivo >> estado;
        fin[estado] = true;
    }

    int trans[101][256];

    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < 256; j++) {
            trans[i][j] = -1;
        }
    }

    for (int i = 0; i < D; i++) {
        int I, J;
        char X;
        archivo >> I >> X >> J;
        trans[I][(int)X] = J;
    }

    for (int i = 0; i < C; i++) {
        string cadena;
        archivo >> cadena;

        int actual = q0;

        for (int j = 0; j < cadena.length(); j++) {
            char simbolo = cadena[j];

            if (trans[actual][(int)simbolo] != -1) {
                actual = trans[actual][(int)simbolo];
            } else {
                actual = -1;
                break;
            }
        }

        if (actual != -1 && fin[actual]) {
            cout << cadena << " Aceptado" << endl;
        } else {
            cout << cadena << " Rechazado" << endl;
        }
    }

    archivo.close();
    return 0;
}

