#include<iostream>
#include<conio.h>
#include<stdio.h>
using namespace std;
int arreglo[100];
void mostrar_arreglo(int arreglo[], int x);
void ord_intercambio(int arreglo[], int x);
void intercambia(int &a, int &b);
main(){
	int n,i,op;
	system ("color f0");
	cout<<endl<<"Numero de elementos del arreglo: ";
	cin>>n;
	cout<<endl<<"Ingresa los elementos del arreglo:"<<endl;
	for(i=0;i<=n-1;i++)
		cin>>arreglo[i];
// clrscr();
		mostrar_arreglo(arreglo, n); // Llamada a la función
		cout<<endl<<endl<<" METODO POR INTERCAMBIO"<<endl;
 		ord_intercambio(arreglo,n); // Llamada a la función
 		cout<<endl<<endl<<"ARREGLO ORDENADO: ";
 		mostrar_arreglo(arreglo, n);
}

void mostrar_arreglo(int arreglo[], int x){
	int i;
	for (i=0;i<=x-1;i++)
		cout<<arreglo[i]<<" ";
}
void ord_intercambio(int arreglo[], int x){
	int i, j;
	for (i=0;i<x-1;i++){ // i indica las pasadas
		cout<<endl<<"PASADA "<<i<<endl;
		for(j=i+1;j<x;j++){ // j posiciona el elemento a comparar con el inferior
			if (arreglo[i]>arreglo[j]){
				intercambia(arreglo[i], arreglo[j]); // Llamada a la función
			}
		mostrar_arreglo(arreglo, x);
		cout<<endl;
		}
	}
}
void intercambia(int &a, int &b){ //Porque a y b reciben un valor de un arreglo
	int aux=a;
	a=b;
	b=aux;
}
