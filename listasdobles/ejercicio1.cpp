#include <iostream>

using namespace std;

struct nodo {
    int dato;
    nodo *siguiente;
    nodo *anterior;
};

// Inserta un dato al final de la lista para mantener actualizada la 'cola'
void insertardatoinicial(nodo*& cabeza, nodo*& cola, int valor) {
    nodo* nuevo = new nodo();
    nuevo->dato = valor;
    nuevo->siguiente = nullptr;
    
    // se apunta a si mismo 
    if (cabeza == nullptr) {
        nuevo->anterior = nullptr;
        cabeza = cola = nuevo; 
    } else { 
        nuevo->anterior = cola;
        cola->siguiente = nuevo;
        cola = nuevo; // Actualizamos la referencia del último nodo
    }
}

// Ordenamiento Burbuja: Compara parejas y las mueve si están en desorden
void oredenarlista(nodo* cabeza) { 
    if (!cabeza) return;
    bool intercambiado;
    do {
        intercambiado = false;
        nodo* actual = cabeza; //Siempre empezamos la revisión desde el primer nodo.
        while (actual->siguiente != nullptr) { //El puntero actual avanza nodo por nodo hasta el penultimo para comparar sino daria error
            // Si el actual es mayor al que sigue, se intercambian los valores
            if (actual->dato > actual->siguiente->dato) {
                swap(actual->dato, actual->siguiente->dato);
                intercambiado = true; // Avisamos que hubo un cambio y hay que revisar de nuevo
            }
            actual = actual->siguiente;
        }
    } while (intercambiado); // Si no hubo cambios en toda la vuelta, la lista ya está lista
}



// BUSQUEDA OPTIMIZADA: Busca desde ambos extremos al mismo tiempo
void buscarOptimizado(nodo* cabeza, nodo* cola, int valorBuscado) {
    if (!cabeza) return;

    nodo* desdeCabeza = cabeza; // Puntero que inicia en el primer nodo
    nodo* desdeCola = cola;     // Puntero que inicia en el último nodo
    bool encontrado = false;

    // El ciclo corre mientras los punteros no se salgan de la lista
    while (desdeCabeza != nullptr && desdeCola != nullptr) {
        
        // 1. ¿Lo encontró el que viene del inicio?
        if (desdeCabeza->dato == valorBuscado) {
            cout << "Ruta mas corta detectada desde la CABEZA:" << endl;
            nodo* aux = cabeza;
            while (aux != desdeCabeza) {
                cout << aux->dato << " -> ";
                aux = aux->siguiente;
            }
            cout << "[" << aux->dato << "]" << endl;
            encontrado = true;
            break; // Salimos del ciclo apenas uno lo encuentre
        }

        // 2. ¿Lo encontró el que viene del final?
        if (desdeCola->dato == valorBuscado) {
            cout << "Ruta mas corta detectada desde la COLA:" << endl;
            nodo* aux = cola;
            while (aux != desdeCola) {
                cout << aux->dato << " <- ";
                aux = aux->anterior;
            }
            cout << "[" << aux->dato << "]" << endl;
            encontrado = true;
            break;
        }

        // 3. Condicion de parada: si los punteros se cruzan, el dato no existe
        if (desdeCabeza == desdeCola || desdeCabeza->siguiente == desdeCola) {
             break; 
        }

        // 4. Mover los punteros un paso hacia el centro
        desdeCabeza = desdeCabeza->siguiente; // Avanza a la derecha
        desdeCola = desdeCola->anterior;     // Retrocede a la izquierda
    }

    if (!encontrado) {
        cout << "El dato " << valorBuscado << " no se encuentra en la lista." << endl;
    }
}
int main() {
    nodo* cabeza = nullptr;
    nodo* cola = nullptr;

    int misDatos[] = {45, 12, 89, 7, 33, 21, 56}; 
    int n = sizeof(misDatos) / sizeof(misDatos[0]); 

    for (int i = 0; i < n; i++) {
        insertardatoinicial(cabeza, cola, misDatos[i]);
    }

    oredenarlista(cabeza);
    cout << "Lista ordenada: ";
    nodo* t = cabeza;
    while(t){ cout << t->dato << " "; t = t->siguiente; }
    
    int buscar;
    cout << "\n\nIngrese el valor a buscar: ";
    cin >> buscar;

    buscarOptimizado(cabeza, cola, buscar);

    return 0;
}