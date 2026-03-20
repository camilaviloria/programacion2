//hacer una clase para una cola de prioridad y con esa misma clase tomar los registros de las emergencias 
#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct caso_emergencia{
    string nombre;
    int prioridad;
};
class colaprioridad{
    private:
    caso_emergencia* arreglo;
    int capacidad; 
    int tamano;

    void redimensionar() {
        int nuevaCapacidad = capacidad * 2;
        caso_emergencia* nuevoArreglo = new caso_emergencia[nuevaCapacidad];

        for (int i = 0; i < tamano; i++) {
            nuevoArreglo[i] = arreglo[i];
        }

        delete[] arreglo; // Liberamos la memoria del arreglo viejo
        arreglo = nuevoArreglo;
        capacidad = nuevaCapacidad;
        cout << "\n[!] Capacidad alcanzada. Redimensionando a: " << capacidad << endl;
    }

public:
    // Constructor
    colaprioridad(int cap_inicial = 5) {
        capacidad = cap_inicial;
        tamano = 0;
        arreglo = new caso_emergencia[capacidad];
    }

    // Destructor para evitar fugas de memoria
    ~colaprioridad() {
        delete[] arreglo;
    }

    void registrar_emergencia(string nombre, int prioridad) {
        if (tamano == capacidad) {
            redimensionar();
        }

        caso_emergencia nuevo;
        nuevo.nombre = nombre;
        nuevo.prioridad = prioridad;

        // Inserción ordenada (Priority Queue simplificada)
        // Los de menor número (Rojo=1) se mueven al principio
        int i = tamano - 1;
        while (i >= 0 && arreglo[i].prioridad > prioridad) {
            arreglo[i + 1] = arreglo[i];
            i--;
        }

        arreglo[i + 1] = nuevo;
        tamano++;
    }

    void atender_paciente() {
        if (tamano == 0) {
            cout << "No hay pacientes en espera." << endl;
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
        cout << "\n--- SALA DE ESPERA ACTUAL ---" << endl;
        for (int i = 0; i < tamano; i++) {
            cout << i + 1 << ". " << arreglo[i].nombre 
                 << " [Nivel " << arreglo[i].prioridad << "]" << endl;
        }
    }
};

int main() {
    colaprioridad hospital(2);

    hospital.registrar_emergencia("Paciente Verde", 5);
    hospital.registrar_emergencia("Paciente Amarillo", 3);
    
    hospital.registrar_emergencia("Paciente Rojo (Urgente)", 1);
    hospital.registrar_emergencia("Paciente Naranja", 2);

    hospital.mostrar_cola();

    hospital.atender_paciente();
    hospital.mostrar_cola();

    return 0;
}
