#include <iostream>
#include <string>

using namespace std;

/**
 * PARTE 1: Estructura solicitada
 */
struct nodo {
    int Edad;
    string Nombre;
    string apellido;
    nodo *siguiente;

    // Constructor opcional para facilitar la inicialización
    nodo() : Edad(0), Nombre(""), apellido(""), siguiente(nullptr) {}
};

/**
 * PARTE 2: Clase Lista que registra el total de nodos
 */
class Lista {
private:
    nodo* cabeza;
    int totalNodos;

public:
Lista() : cabeza(nullptr), totalNodos(0) {}

    // Insertar al inicio
    void insertar(int edad, string nombre, string apellido) {
        nodo* nuevo = new nodo;
        nuevo->Edad = edad; // es el equivalente a decir: "Ve a la dirección que guarda 'nuevo' y busca el campo 'Edad'".
        nuevo->Nombre = nombre;
        nuevo->apellido = apellido;
        
        nuevo->siguiente = cabeza;
        cabeza = nuevo;

        totalNodos++; 
        cout << "[Sistema] Insertado: " << nombre << ". Total nodos actual: " << totalNodos << endl;
    }

    void eliminar() {
        if (cabeza == nullptr) {
            cout << "[Sistema] La lista esta vacia." << endl;
            return;
        }

        nodo* temporal = cabeza;
        cabeza = cabeza->siguiente;
        delete temporal;

        totalNodos--; // Registro decremental
        cout << "[Sistema] Nodo eliminado. Total nodos restante: " << totalNodos << endl;
    }

    void mostrar() {
        nodo* actual = cabeza;
        cout << "\n--- Registros en la Lista ---" << endl;
        while (actual != nullptr) {
            cout << "Nombre: " << actual->Nombre << " " << actual->apellido 
                 << " | Edad: " << actual->Edad << endl;
            actual = actual->siguiente;
        }
        cout << "-----------------------------\n" << endl;
    }

    int getTotalNodos() {
        return totalNodos;
    }

    ~Lista() {
        while (cabeza != nullptr) {
            eliminar();
        }
    }
};

int main() {
    cout << "--- CREACION MANUAL ---" << endl;
    
    nodo* nodoInicial = new nodo;
    nodoInicial->Edad = 30;
    nodoInicial->Nombre = "Juan"; 
    nodoInicial->apellido = "Perez";

    nodo* nodo2 = new nodo;
    nodo2->Nombre = "camila";
    nodo2->Edad = 20;
    nodoInicial->siguiente = nodo2;

    nodo* nodo3 = new nodo;
    nodo3->apellido = "viloria";
    nodo3->Nombre = "Elena";
    nodo2->siguiente = nodo3;

    cout << "Enlace manual exitoso: " << nodoInicial->Nombre << " -> " 
         << nodoInicial->siguiente->Nombre << " -> " 
         << nodoInicial->siguiente->siguiente->apellido << endl;

    // Limpieza manual
    delete nodo3;
    delete nodo2;
    delete nodoInicial;

    // --- Requerimiento 2: Clase Lista Automática ---
    cout << "\n--- CLASE LISTA CON CONTADOR ---" << endl;
    Lista miLista;

    miLista.insertar(30, "Juan", "Perez");
    miLista.insertar(20, "Camila", "Gomez");
    miLista.insertar(25, "Elena", "Viloria");

    miLista.mostrar();
    cout << "Conteo final de nodos: " << miLista.getTotalNodos() << endl;

    miLista.eliminar();
    cout << "Conteo tras eliminar: " << miLista.getTotalNodos() << endl;

    return 0;
}