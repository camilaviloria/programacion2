#include <iostream>
#include <string>
using namespace std;

struct nodo {
   int Edad;
    nodo *siguiente;
    string Nombre;
    string apellido;

};

class lista {
private:
    nodo* cabeza; //cabeza: Es la dirección de memoria del primer nodo.
    int totalNodos;

public:
lista() : cabeza(nullptr), totalNodos(0) {} //Con el constructor Lista(): Te aseguras de que el cuaderno se abra en una página en blanco (cabeza = nullptr) y que el contador de alumnos en la portada diga 0 (totalNodos = 0).
       void insertar(int edad, string Nombre, string apellido) {
        nodo* nuevo = new nodo;
        nuevo->Nombre = Nombre;
        nuevo->apellido = apellido;
        
       }


};

int main() {
    nodo* nodoInicial = new nodo;
    nodoInicial->Edad = 30;

    nodo* nodo2 = new nodo;
    nodo2->Nombre = "camila";
    nodoInicial->siguiente = nodo2;

    nodo* nodo3 = new nodo;
    nodo3->apellido = "viloria";
    nodo2->siguiente = nodo3;
}

