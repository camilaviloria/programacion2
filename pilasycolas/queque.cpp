#include <iostream>

using namespace std;

struct nodo {
    int dato;
    nodo* siguiente;
};

void enqueue(nodo*& cabeza, nodo*& cola, int valor) {
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

int dequeue(nodo*& cabeza, nodo*& cola) {
   if (cabeza == nullptr) return -1; 

    nodo* temp = cabeza;
    int valor = temp->dato;
    cabeza = cabeza->siguiente;

    if (cabeza == nullptr) cola = nullptr;

    delete temp;
    return valor;
}

int obtenertamano(nodo* cabeza) {
    int cont = 0;
    while (cabeza) {
        cont++;
        cabeza = cabeza->siguiente;
    }
    return cont;
}

void imprimir(nodo* cabeza) {
    if (!cabeza) cout << "Cola vacia";
    while (cabeza) {
        cout << "[" << cabeza->dato << "] ";
        cabeza = cabeza->siguiente;
    }
    cout << endl;
}

void ordenarCola(nodo*& cabeza, nodo*& cola) {
    int n = obtenertamano(cabeza);

    for (int i = 0; i < n; i++) {
        int min_val = dequeue(cabeza, cola); // el primero de la cola

        for (int j = 0; j < n - i - 1; j++) {
            int actual = dequeue(cabeza, cola);
            if (actual < min_val) {
                enqueue(cabeza, cola, min_val); 
                min_val = actual;               
            } else {
                enqueue(cabeza, cola, actual);  
            }
        }
        enqueue(cabeza, cola, min_val);

        for (int k = 0; k < i; k++) {
            enqueue(cabeza, cola, dequeue(cabeza, cola));
        }
    }
}

int main() {
    nodo *cabeza = nullptr, *cola = nullptr;
    int datos[] = {45, 12, 89, 7, 33};
    for (int i = 0; i < 5; i++) {
        enqueue(cabeza, cola, datos[i]);
}
    cout << "Cola original: ";
    imprimir(cabeza);

    ordenarCola(cabeza, cola);

    cout << "Cola ordenada: ";
        imprimir(cabeza);

    return 0;
};