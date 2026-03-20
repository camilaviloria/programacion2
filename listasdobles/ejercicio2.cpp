// por medio de una lista circular simple ordene los numeros de menor a mayor en sentido horario
// y eliminarlos de n en n pasos hasta que no haya ninguno 

#include <iostream>

using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
};

void insertarOrdenado(Nodo*& cola, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;

    if (cola == nullptr) {
        nuevo->siguiente = nuevo; 
        cola = nuevo;
        return;
    }

    Nodo* actual = cola->siguiente; 
    Nodo* anterior = cola;

    if (valor <= actual->dato || valor >= cola->dato) {
        nuevo->siguiente = cola->siguiente;
        cola->siguiente = nuevo;
        if (valor >= cola->dato) {
            cola = nuevo; 
        }
    } else {
        while (actual->dato < valor) {
            anterior = actual;
            actual = actual->siguiente;
        }
        nuevo->siguiente = actual;
        anterior->siguiente = nuevo;
    }
}

void eliminar(Nodo*& cola, int n) {
    if (cola == nullptr) return;

    Nodo* actual = cola->siguiente; 
    Nodo* anterior = cola;

    while (cola != nullptr) {
        for (int i = 1; i < n; i++) {
            anterior = actual;
            actual = actual->siguiente;
        }
 
        cout << "Eliminando: " << actual->dato << endl;

        if (actual == actual->siguiente) {
            delete actual;
            cola = nullptr;
        } else {
            anterior->siguiente = actual->siguiente; 
            if (actual == cola) {
                cola = anterior; 
            }
            delete actual;
            actual = anterior->siguiente; 
        }
    }
}

void imprimir(Nodo* cola) {
    if (cola == nullptr) return;
    Nodo* aux = cola->siguiente;
    do {
        cout << aux->dato << " -> ";
        aux = aux->siguiente;
    } while (aux != cola->siguiente);
    cout << "(vuelta al inicio)" << endl;
}

int main() {
    Nodo* cola = nullptr; 
    int n_pasos = 3; 

    int datos[] = {40, 10, 30, 20, 50};
    
    int tam = sizeof(datos) / sizeof(datos[0]);

    for (int i = 0; i < tam; i++) {
        insertarOrdenado(cola, datos[i]);
    }

    if (cola != nullptr) {
        cout << "Lista circular ordenada (sentido horario):" << endl;
        imprimir(cola);

        cout << "\nIniciando eliminacion cada " << n_pasos << " pasos:" << endl;
        eliminar(cola, n_pasos);
    } else {
        cout << "La lista esta vacia." << endl;
    }

    return 0;
}