#include <iostream>
#include <cmath>
#include <limits>

using namespace std;

struct nodo {
    int dato;
    nodo* siguiente;
};


void insertarlista(nodo*& cabeza, nodo*& cola, int valor) {
    nodo* nuevo = new nodo;
    nuevo->dato = valor;
    nuevo->siguiente = nullptr;

    if (cabeza == nullptr) {
        cabeza = cola = nuevo;
    } else {
        cola->siguiente = nuevo; 
        cola = nuevo;            
    }
}


void calcularyeliminar(nodo*& cabeza, nodo*& cola) {
    if (cabeza == nullptr) return;

    double suma = 0;
    int contador = 0;
    nodo* temp = cabeza;
    while (temp != nullptr) {
        suma += temp->dato;
        contador++;
        temp = temp->siguiente;
    }
    double promedio = suma / (double)contador;
    cout << "\nPromedio calculado: " << promedio << endl;

    if (contador <= 2) {
        while (cabeza != nullptr) {
            nodo* borrar = cabeza;
            cabeza = cabeza->siguiente;
            delete borrar;
        }
        cola = nullptr;
        return;
    }

    double nodo1 = numeric_limits<double>::max();
    double nodo2 = numeric_limits<double>::max();

    temp = cabeza;
    while (temp != nullptr) {
        double difActual = abs(temp->dato - promedio);
        
        if (difActual < nodo1) {
            nodo2 = nodo1; 
            nodo1 = difActual; 
        } else if (difActual < nodo2) {
            nodo2 = difActual; 
        }
        temp = temp->siguiente;
    }

    double objetivos[2] = {nodo1, nodo2};

    for (int i = 0; i < 2; i++) {
        double buscarDif = objetivos[i];
        nodo* actual = cabeza;
        nodo* prev = nullptr;

        while (actual != nullptr) {
            if (abs(actual->dato - promedio) == buscarDif) {
                cout << "Eliminando nodo: " << actual->dato << " (Dif: " << buscarDif << ")" << endl;
                
                nodo* aborrar = actual;
                if (prev == nullptr) { 
                    cabeza = actual->siguiente;
                    if (cabeza == nullptr) cola = nullptr;
                } else {
                    prev->siguiente = actual->siguiente;
                    if (actual == cola) cola = prev; 
                }
                
                delete aborrar;
                break; 
            }
            prev = actual;
            actual = actual->siguiente;
        }
    }
}


void imprimir(nodo* cabeza) {
    if (cabeza == nullptr) {
        cout << "lista vacia." << endl;
        return;
    }
    nodo* temp = cabeza;
    while (temp != nullptr) {
        cout << "[" << temp->dato << "] -> ";
        temp = temp->siguiente;
    }
    cout << "NULL" << endl;
}

int main() {
    nodo *cabeza = nullptr, *cola = nullptr;
    int misDatos[] = {45, 12, 89, 7, 33, 21, 56, 56, 99, 123, 44}; 
    int n = sizeof(misDatos) / sizeof(misDatos[0]); 
    
    for (int i = 0; i < n; i++) {
        insertarlista(cabeza, cola, misDatos[i]);
    }

    cout << "lista antes: ";
    imprimir(cabeza);

    calcularyeliminar(cabeza, cola);

    cout << "lista despues: ";
    imprimir(cabeza);

    return 0;
}