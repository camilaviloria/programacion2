
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
void imprimir(nodo* cabeza) {
    if (!cabeza) { cout << "vacia"; }
    while (cabeza) {
        cout << "[" << cabeza->dato << "] -> ";
        cabeza = cabeza->siguiente;
    }
    cout << "NULL" << endl;
}

void dividirLista(nodo*& cabezaoriginal, int M, int N, int valordefecto) {
    nodo* actual = cabezaoriginal;

    for (int i = 1; i <= N; i++) {
        nodo* subcabeza = nullptr;
        nodo* subcola = nullptr;

        cout << "sublista " << i << ": ";

        for (int j = 0; j < M; j++) {
            if (actual != nullptr) {
                insertarlista(subcabeza, subcola, actual->dato);
                actual = actual->siguiente;
            } else {
                insertarlista(subcabeza, subcola, valordefecto);
            }
        }
        imprimir(subcabeza);
    }
}
int main() {
    nodo *cabeza = nullptr, *cola = nullptr;
    int misDatos[] = {45, 12, 89, 7, 33, 21, 56, 75, 57, 90}; 
    int n = sizeof(misDatos) / sizeof(misDatos[0]); 
    
    for (int i = 0; i < n; i++) {
        insertarlista(cabeza, cola, misDatos[i]);
    }
    cout << "lista original:" << endl;
    imprimir(cabeza);

    int N, M, defecto;
    cout << "listas a dividir (N): "; cin >> N;
    cout << "nodos en cada una (M): "; cin >> M;
    cout << "valor de relleno por defecto: "; cin >> defecto;

    dividirLista(cabeza, N, M, defecto);

    return 0;
}