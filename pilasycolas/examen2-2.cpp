// dado una cola de n numeros, pedir al usuario ingrese una secuencia de simbolos 
//y aplicar las operaciones de cada simbolo siguiendo LIFO -: eliminar tope, +: sumar los numeros, eliminarlos y guardar la suma
// %: dividir todos los numeros por el tamaño de la pila, /: dividir la cola en N porciones y quedarse solo con la ultima porcion

#include <iostream>
#include <stack>
#include <string>

using namespace std;

struct nodo {
    int dato;
    struct nodo* siguiente;
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

void dequeue(nodo*& cabeza, nodo*& cola) {
    if (cabeza == nullptr) return;
    
    nodo* aux = cabeza;
    cabeza = cabeza->siguiente;
    
    if (cabeza == nullptr) cola = nullptr; 
    delete aux;
}

int obtenerTamano(nodo* cabeza) {
    int cont = 0;
    while (cabeza != nullptr) {
        cont++;
        cabeza = cabeza->siguiente;
    }
    return cont;
}

int main() {
    nodo* cabeza = nullptr;
    nodo* cola = nullptr;
    stack<char> pilaSimbolos;
    
    int n, valor;
    string secuencia;

    cout << "números que desea ingresar: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        cout << "ingrese numeros " << i + 1 << ": ";
        cin >> valor;
        enqueue(cabeza, cola, valor);
    }

    cout << "\nsecuencia de símbolos (+, -, %, /): ";
    cin >> secuencia;
    int i = 0;
    while (i < secuencia.length()) {
         pilaSimbolos.push(secuencia[i]);
         i++;
}

    cout << "\n--- operaciones ---" << endl;
    while (!pilaSimbolos.empty()) {
        char op = pilaSimbolos.top();
        pilaSimbolos.pop();

        if (cabeza == nullptr) break;

        switch (op) {
            case '-': 
                cout << "Eliminando " << cabeza->dato << endl;
                dequeue(cabeza, cola);
                break;

            case '+': { 
                int suma = 0;
                while (cabeza != nullptr) {
                    suma += cabeza->dato;
                    dequeue(cabeza, cola);
                }
                enqueue(cabeza, cola, suma);
                cout << "suma " << suma << " guardada" << endl;
                break;
            }

            case '%': {
                int tam = obtenerTamano(cabeza);
                nodo* temp = cabeza;
                while (temp != nullptr) {
                    temp->dato /= tam;
                    temp = temp->siguiente;
                }
                cout << "Dividido entre " << tam << endl;
                break;
            }

            case '/': { 
                int porciones;
                cout << "porciones a dividir: ";
                cin >> porciones;
                
                int tamTotal = obtenerTamano(cabeza);
                int tamPorcion = tamTotal / porciones;
                int eliminar = tamTotal - tamPorcion;

                for (int i = 0; i < eliminar; i++) {
                    dequeue(cabeza, cola);
                }
                cout << "solo quedan " << tamPorcion << " elementos" << endl;
                break;
            }
        }
    }

    cout << "\nresultado final: ";
    if (cabeza == nullptr) cout << "Vacia";
    while (cabeza != nullptr) {
        cout << "[" << cabeza->dato << "] ";
        dequeue(cabeza, cola);
    }
    cout << endl;

    return 0;
}
