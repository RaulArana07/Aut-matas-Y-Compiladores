#include <iostream>
#include <string>
#include <cctype>
#include <conio.h>

using namespace std;

int main() {

    bool esMinusculas = true;
    bool esMayusculas = true;
    bool esNumero = true;
    bool esIdentificador = true;
    string palabra;
    int salir;
    
	do{
	    cout << "Ingresa una palabra: ";
	    cin >> palabra;


	    for (int i = 0; i < palabra.length(); i++) {
	        if (!isdigit(palabra[i])) {
	            esNumero = false;
	            break;
	        }
	    }
	
		for (int i = 0; i < palabra.length(); i++) {
        	if (!islower(palabra[i])) {
            	esMinusculas = false;
            	break;
        	}
    	}
    
    	for (int i = 0; i < palabra.length(); i++) {
        	if (!isupper(palabra[i])) {
        	    esMayusculas = false;
            	break;
    	    }
    	}

    	if (!(isalpha(palabra[0]) || palabra[0] == '_')) {
        	esIdentificador = false;
    	} else {
        	for (int i = 1; i < palabra.length(); i++) {
            	if (!(isalnum(palabra[i]) || palabra[i] == '_')) {
                	esIdentificador = false;
                	break;
            	}
        	}
    	}

    	if (esNumero) {
        	cout << "Es un numero entero." << endl;
    	} else if (esMinusculas) {
        	cout << "Esta escrita en minusculas." << endl;
    	} else if (esMayusculas) {
        	cout << "Esta escrita en mayusculas." << endl;
    	} else if (esIdentificador) {
        	cout << "Es un identificador valido." << endl;
    	} else {
        	cout << "No cumple con ninguna categoria especificada." << endl;
    	}
    	
    	
    	cout << "Desea salir? " << endl << "1=si" << endl << "2=no" << endl;
    	cin>> salir;
    	
	}while(salir!=1);
	
	cout<< endl << "Fin de del programa";
	getch();
	
    return 0;
}
