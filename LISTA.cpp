#include <iostream>
#include <string>
#include <limits>
#include <fstream>

using namespace std;

struct Personas {
    char nombre[20];
    char apellido[20];
    int edad;
    char cedula[15];
    float CI;

};

const string lista = "personas.in";

void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
}

void aregarpersona() {
    ofstream archivo(lista, ios::binary | ios::app); 
    if (!archivo.is_open()) { cerr << "error al abrir archivo." << endl; return;}

    Personas p; {
        cout << "nombre: "; cin.getline(p.nombre, sizeof(p.nombre));
        cout << "aellido: "; cin.getline(p.apellido, sizeof(p.apellido));
        cout << "edad: "; cin >> p.edad; limpiarBuffer();
        cout << "cedula: "; cin >> p.cedula; limpiarBuffer();
        cout << "CI: "; cin >> p.CI; limpiarBuffer();

    archivo.write(reinterpret_cast<const char*>(&p), sizeof(Personas));
    archivo.close();
    cout << "Persona agregada." << endl;
    }

}

void mostrarDatosPersona(const Personas& p) {
    cout << "Nombre: " << p.nombre << ", Apellido: " << p.apellido
              << ", Cedula: " << p.cedula << ", Edad: " << p.edad
              << ", CI: " << p.CI << endl;
}

void mostrarPersonas() {
    ifstream archivo(lista, ios::binary);
    if (!archivo.is_open()) { cerr << "No hay personas." << endl; return; }

    Personas p;
    cout << "\n--- LISTA DE PERSONAS ---" << endl;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Personas))) {
        mostrarDatosPersona(p);
    }
    archivo.close();
}

void buscarPersonaPorCedula() {
    ifstream archivo(lista, ios::binary);
    if (!archivo.is_open()) { cerr << "No hay personas para buscar." << endl; return; }

    string cedulaBuscada;
    cout << "Cedula a buscar: "; cin >> cedulaBuscada; limpiarBuffer();

    Personas p;
    bool encontrada = false;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Personas))) {
        if (cedulaBuscada == p.cedula) {
            cout << "Persona encontrada:" << endl;
            mostrarDatosPersona(p);
            encontrada = true;
            break;
        }

    } if(!encontrada){cout << "Cedula no encontrada." << endl;};
    archivo.close();
}    

void buscarPersonaPorEdad() {
    ifstream archivo(lista, ios::binary);
    if (!archivo.is_open()) { cerr << "No hay personas para buscar." << endl; return; }

    int edadBuscada;
    cout << "Edad a buscar: "; cin >> edadBuscada; limpiarBuffer();

    Personas p;
    bool encontradas = false;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Personas))) {
        if (p.edad == edadBuscada) {
            if (!encontradas) { cout << "Personas con edad " << edadBuscada << ":" << endl; }
            mostrarDatosPersona(p);
            encontradas = true;
        }
    }
    if (!encontradas) { cout << "No hay personas con esa edad." << endl; }
    archivo.close();
}

void eliminarPersona() {
    ifstream archivo(lista, ios::binary);
    if (!archivo.is_open()) { cerr << "No hay personas para eliminar." << endl; return; }

    string cedulaEliminar;
    cout << "Cedula a eliminar: "; cin >> cedulaEliminar; limpiarBuffer();

    ofstream temporal("temp.bin", ios::binary | ios::trunc);
    if (!temporal.is_open()) { cerr << "Error creando temp." << endl; archivo.close(); return; }

    Personas p;
    bool eliminada = false;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Personas))) {
        if (cedulaEliminar == p.cedula) {
            eliminada = true;
        } else {
            temporal.write(reinterpret_cast<const char*>(&p), sizeof(Personas));
        }
    }
    archivo.close();
    temporal.close();

    if (!eliminada) { cout << "Cedula no encontrada para eliminar." << endl; }
    else {
        remove(lista.c_str());
        rename("temp.bin", lista.c_str());
        cout << "Persona eliminada." << endl;
    }
}
void editarPersona() {
    fstream archivo(lista, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) { cerr << "No hay personas para editar." << endl; return; }

    string cedulaEditar;
    cout << "Cedula a editar: "; cin >> cedulaEditar; limpiarBuffer();

    Personas p;
    bool encontrada = false; 
    long posActual = 0; //almacenar la posición de inicio en bytes del registro de la Persona que se está leyendo o que se acaba de leer en el archivo
    //recorre el archivo binario registro por registro para encontrar la persona con la cédula deseada.
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Personas))) {
        if (cedulaEditar == p.cedula) {
            encontrada = true;
            cout << "Persona encontrada. Nuevos datos:\n";
            cout << "Nombre (" << p.nombre << "): "; cin.getline(p.nombre, sizeof(p.nombre));
            cout << "Apellido (" << p.apellido << "): "; cin.getline(p.apellido, sizeof(p.apellido));
            cout << "Edad (" << p.edad << "): "; cin >> p.edad; limpiarBuffer();
            cout << "CI (" << p.CI << "): "; cin >> p.CI; limpiarBuffer();

            archivo.seekp(posActual); // metodo que mueve el puntero hacia la posicion deseada 
            archivo.write(reinterpret_cast<const char*>(&p), sizeof(Personas));
            cout << "Datos actualizados." << endl;
            break;
        }
//en este punto nos da la posición donde comienza el siguiente registro en el archivo. este valor se guarda en posActual para la próxima iteración.
        posActual = archivo.tellg(); 
    }
    if (!encontrada) { cout << "Cedula no encontrada para editar." << endl; }
    archivo.close();
}

void imprimirPersonaMayorEdad() {
    ifstream archivo(lista, ios::binary); 
    if (!archivo.is_open()) { cerr << "No hay personas." << endl; return; }

    Personas p;
    bool encontradas = false; 

    cout << "\n--- NOMBRES DE PERSONAS MAYORES DE EDAD ---" << endl;

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Personas))) {
        if (p.edad > 18) {
            cout << "Nombre: " << p.nombre << endl;
            encontradas = true;
        }
    }
    if (!encontradas) {
        cout << "No se encontraron personas mayores de edad." << endl;
    }
    archivo.close();
}
int main() {
    int opcion;
    do {
        cout << "\n--- MENU ---" << endl;
        cout << "1. Agregar\n2. Mostrar todo\n3. Buscar por cedula\n4. Buscar por edad\n5. Eliminar\n6. Editar\n7. Mayor edad\n0. Salir\n";
        cout << "Opcion: ";
        while (!(cin >> opcion)) {
            cout << "Invalido. Ingrese un numero: ";
            cin.clear();
            limpiarBuffer();
        }
        limpiarBuffer();

        switch (opcion) {
            case 1: aregarpersona(); break;
            case 2: mostrarPersonas(); break;
            case 3: buscarPersonaPorCedula(); break;
            case 4: buscarPersonaPorEdad(); break;
            case 5: eliminarPersona(); break;
            case 6: editarPersona(); break;
            case 7: imprimirPersonaMayorEdad(); break;
            case 0: cout << "Saliendo..." << endl; break;
            default: cout << "Opcion no valida." << endl; break;
        }
    } while (opcion != 0);

    return 0;
}