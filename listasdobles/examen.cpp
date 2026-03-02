#include <iostream>
#include <limits>

using namespace std;

struct Nodo {
    int dato;
    Nodo* siguiente;
    Nodo* anterior;
};

void insertarAlFinal(Nodo*& cabeza, int valor) {
    Nodo* nuevo = new Nodo();
    nuevo->dato = valor;
    nuevo->siguiente = nullptr;
    if (cabeza == nullptr) {
        nuevo->anterior = nullptr;
        cabeza = nuevo;
    } else {
        Nodo* temp = cabeza;
        while (temp->siguiente != nullptr) temp = temp->siguiente;
        temp->siguiente = nuevo;
        nuevo->anterior = temp;
    }
}

// ORDENAMIENTO POR INSERCIÓN: Recorre mucho menos la lista
void ordenamientoInsercion(Nodo* cabeza) {
    if (cabeza == nullptr || cabeza->siguiente == nullptr) return;
        //El marcador representa la "carta" que tienes en la mano y quieres acomodar.
        //Empezamos en el segundo nodo (cabeza->siguiente), porque el primer nodo, por sí solo, ya se considera una lista "ordenada".
    Nodo* marcador = cabeza->siguiente; 

    while (marcador != nullptr) {
        int valorActual = marcador->dato;
        //movil: Es un puntero auxiliar que empieza justo a la izquierda del marcador. Lo usaremos para retroceder y buscar dónde debe encajar el valorActual
        Nodo* movil = marcador->anterior;

        // Solo retrocedemos mientras el valor sea menor al que tenemos a la izquierda
        // Esto evita recorridos innecesarios
        while (movil != nullptr && movil->dato > valorActual) {
            movil->siguiente->dato = movil->dato; // Desplazamos el valor
            movil = movil->anterior;
        }

        // Colocamos el valor en su posición correcta
        if (movil == nullptr) 
            cabeza->dato = valorActual;
        else 
            movil->siguiente->dato = valorActual;

        marcador = marcador->siguiente;
    }
}

void imprimirLista(Nodo* cabeza) {
    Nodo* temp = cabeza;
    while (temp != nullptr) {
        cout << "[" << temp->dato << "]" << (temp->siguiente ? " <-> " : "");
        temp = temp->siguiente;
    }
    cout << endl;
}

void liberarMemoria(Nodo*& cabeza) {
    while (cabeza != nullptr) {
        Nodo* aux = cabeza;
        cabeza = cabeza->siguiente;
        delete aux;
    }
}

int main() {
    Nodo* miLista = nullptr;
    int cant, val;

    cout << "Ingrese cantidad de numeros: ";
    cin >> cant;

    for (int i = 0; i < cant; i++) {
        cout << "Numero " << i + 1 << ": ";
        cin >> val;
        insertarAlFinal(miLista, val);
    }

    cout << "\nLista original: ";
    imprimirLista(miLista);

    // Ordenamos de forma mas eficiente
    ordenamientoInsercion(miLista);

    cout << "Lista ordenada: ";
    imprimirLista(miLista);

    liberarMemoria(miLista);
    cout << "\nPresione Enter para salir...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    return 0;
}