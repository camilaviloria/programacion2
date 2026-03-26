#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct proceso {
    int id;
    string nombre;
    int prioridad;
};

class cola_procesos{
    //dato que sirva para gestionar la estructura (índices, contadores, punteros)
    private:
    proceso* arreglo;
    int capacidad;
    int tamano;

    bool estallena(){
        return tamano==capacidad;
    }

    public:
     // Constructor
    cola_procesos(int cap_inicial = 5) {
        capacidad = cap_inicial;
        tamano = 0;
        arreglo = new proceso[capacidad];
    }

    // Destructor para evitar fugas de memoria
    ~cola_procesos() {
        delete[] arreglo; }

    void insertarproceso(int id, string nombre, int prioridad) {
    // 1. Validar si hay espacio
    if (tamano == capacidad) {
        cout << "Error: La cola de procesos está llena (Overflow)." << endl;
        return;
    }

    // 2. Crear el objeto temporal
    proceso nuevo;
    nuevo.id = id;
    nuevo.nombre = nombre;
    nuevo.prioridad = prioridad;

    // 3. Buscar la posición y desplazar elementos
    int i = tamano - 1;

    // Mientras no lleguemos al inicio Y el proceso actual tenga MENOR prioridad
    while (i >= 0 && arreglo[i].prioridad < prioridad) {
        arreglo[i + 1] = arreglo[i]; // Desplazamos a la derecha
        i--;
    }

    // 4. Insertar en el lugar exacto
    // El índice i bajó hasta uno antes de la posición ideal, por eso usamos i+1
    arreglo[i + 1] = nuevo;

    // 5. Actualizar el contador
    tamano++;
} void ejecutar_siguiente() {
        if (tamano == 0) {
            cout << "No hay procesos" << endl;
            return;
        }

        cout << "\n>>> Atendiendo a: " << arreglo[0].nombre 
             << " (Prioridad: " << arreglo[0].prioridad << ")" << endl;

        // Desplazamos los elementos para "eliminar" el primero
        for (int i = 0; i < tamano - 1; i++) {
            arreglo[i] = arreglo[i + 1];
        }
        tamano--;
    }
    void mostrar_cola() {
        cout << "\n--- procesos ---" << endl;
        for (int i = 0; i < tamano; i++) {
            cout << i + 1 << ". " << arreglo[i].nombre 
                 << " [Nivel " << arreglo[i].prioridad << "]" << endl;
        }
    }
};


int main() {
    cola_procesos sistema(5);

    sistema.insertarproceso(101, "spotify", 5);
    sistema.insertarproceso(111, "anti virus", 3);
    sistema.insertarproceso(121, "kernel", 1);
    sistema.insertarproceso(123, "word", 2);

    sistema.mostrar_cola();

    sistema.ejecutar_siguiente();
    sistema.mostrar_cola();

    return 0; 
    }