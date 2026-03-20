#include <iostream>

using namespace std;

struct nodo {  
    int dato;
    nodo* siguiente;
};

void push(nodo*& tope, int valor) {
    nodo* nuevo = new nodo;
    nuevo->dato = valor;
    nuevo->siguiente = tope; 
    tope = nuevo;            
}
int pop(nodo*& tope) {
    if (tope == nullptr) return -1; 

    nodo* temp = tope;
    int valor = temp->dato;
    tope = tope->siguiente; 
    delete temp;            
    return valor;
}
int peek(nodo* tope) {
    if (tope == nullptr) return -1;
    return tope->dato;
}

void imprimirPila(nodo* tope) {
    if (tope == nullptr) {
        cout << "Pila vacia" << endl;
        return;
    }
    while (tope) {
        cout << "[" << tope->dato << "]" << endl;
        tope = tope->siguiente;
    }
}

void ordenarPila(nodo*& pila1) {
    nodo* pila2 = nullptr; 
    nodo* pila3 = nullptr; 

    while (pila1 != nullptr) {
        int temporal = pop(pila1); 

        while (pila2 != nullptr && peek(pila2) < temporal) {
            push(pila1, pop(pila2));
        }
        push(pila2, temporal);
    }

    while (pila2 != nullptr) {
        push(pila3, pop(pila2));
    }

    cout << " pila final ordenada " << endl;
    imprimirPila(pila3);
}

int main() {
    nodo* pila1 = nullptr;

    push(pila1, 10);
    push(pila1, 45);
    push(pila1, 5);
    push(pila1, 90);
    push(pila1, 21);

    cout << "pila desordenada:" << endl;
    nodo* temp = pila1;
    while(temp) { cout << "[" << temp->dato << "] "; temp = temp->siguiente; }
    cout << "\n---------------------------" << endl;

    ordenarPila(pila1);

    return 0;
}

