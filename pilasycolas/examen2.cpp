//construir una cola de prioridad que procese a las personas segun su rol

#include <iostream>
#include <queue>
#include <string>

using namespace std;

struct persona{
    int id;
    string rol;
    string nombre;
    int prioridad;
};

class cola_prioridad {
    private:
    persona * arreglo;
    int tamano;
    int capacidad;

    bool estallena(){
        return capacidad=tamano;
    }

    public:
    cola_prioridad(int capacidad_inicial= 5){
        capacidad=capacidad_inicial;
        tamano=0;
        arreglo= new persona[capacidad];
    }
     ~cola_prioridad() {
        delete[] arreglo; }

    void procesar(int id,string nombre, string rol, int prioridad){
         if (tamano == capacidad) {
        cout << "La cola de procesos está llena" << endl;
        return;
    }    
        persona nuevo;
        nuevo.id=id;
        nuevo.rol=rol;
        nuevo.nombre=nombre;
        nuevo.prioridad=prioridad;

         int i = tamano - 1;

    while (i >= 0 && arreglo[i].prioridad > prioridad) {
        arreglo[i + 1] = arreglo[i]; 
        i--;
    }

    arreglo[i + 1] = nuevo;

    tamano++;}
    void ejecutar_siguiente() {
        if (tamano == 0) {
            cout << "No hay personas" << endl;
            return;
        }

        cout << "\n>>> procesando a: " << arreglo[0].nombre 
             << "\n>>> rol: " << arreglo[0].rol 
             << " (Prioridad: " << arreglo[0].prioridad << ")" << endl;

        for (int i = 0; i < tamano - 1; i++) {
            arreglo[i] = arreglo[i + 1];
        }
        tamano--;
    }
    void mostrar_cola() {
        cout << "\n--- personal ---" << endl;
        for (int i = 0; i < tamano; i++) {
            cout << i + 1 << ". " << arreglo[i].rol
                 << " [Nivel " << arreglo[i].prioridad << "]" << endl;
        }
    }
};

int main() {
    cola_prioridad sistema(5);

    sistema.procesar(101, "julio","directores", 5);
    sistema.procesar(111, "laura", "administracion", 1);
    sistema.procesar(121, "claudio", "profesores", 2);
    sistema.procesar(123, "paul", "estudiantes", 3);
    sistema.procesar(144, "jose", "personal de mantenimiento", 4);


    sistema.mostrar_cola();

    sistema.ejecutar_siguiente();
    sistema.mostrar_cola();

    return 0; 
    }
