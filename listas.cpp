#include <iostream>
#include <fstream>
#include <string>
#include <limits> 

using namespace std;

struct Persona {
    char nombre[30];
    char apellido[30];
    char cedula[15];
    int edad;
    float coeficiente_intelectual;
};

const string lista = "personas.bin";

void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //tamaño de un flujo de caracteres
}

void agregarPersona() {
    ofstream archivo(lista, ios::binary | ios::app); 
    if (!archivo.is_open()) { cerr << "error al abrir archivo." << endl; return; }

    Persona p;
    cout << "Nombre: "; cin.getline(p.nombre, sizeof(p.nombre));
    cout << "Apellido: "; cin.getline(p.apellido, sizeof(p.apellido));
    cout << "Cedula: "; cin >> p.cedula; limpiarBuffer();
    cout << "Edad: "; cin >> p.edad; limpiarBuffer();
    cout << "CI: "; cin >> p.coeficiente_intelectual; limpiarBuffer();

    archivo.write(reinterpret_cast<const char*>(&p), sizeof(Persona));
    archivo.close();
    cout << "Persona agregada." << endl;
}

void mostrarDatosPersona(const Persona& p) {
    cout << "Nombre: " << p.nombre << ", Apellido: " << p.apellido
              << ", Cedula: " << p.cedula << ", Edad: " << p.edad
              << ", CI: " << p.coeficiente_intelectual << endl;
}

void mostrarPersonas() {
    ifstream archivo(lista, ios::binary);
    if (!archivo.is_open()) { cerr << "No hay personas." << endl; return; }

    Persona p;
    cout << "\n--- LISTA DE PERSONAS ---" << endl;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Persona))) {
        mostrarDatosPersona(p);
    }
    archivo.close();
}

void buscarPersonaPorCedula() {
    ifstream archivo(lista, ios::binary);
    if (!archivo.is_open()) { cerr << "No hay personas para buscar." << endl; return; }

    string cedulaBuscada;
    cout << "Cedula a buscar: "; cin >> cedulaBuscada; limpiarBuffer();

    Persona p;
    bool encontrada = false;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Persona))) {
        if (cedulaBuscada == p.cedula) {
            cout << "Persona encontrada:" << endl;
            mostrarDatosPersona(p);
            encontrada = true;
            break;
        }
    }
    if (!encontrada) { cout << "Cedula no encontrada." << endl; }
    archivo.close();
}

void buscarPersonaPorEdad() {
    ifstream archivo(lista, ios::binary);
    if (!archivo.is_open()) { cerr << "No hay personas para buscar." << endl; return; }

    int edadBuscada;
    cout << "Edad a buscar: "; cin >> edadBuscada; limpiarBuffer();

    Persona p;
    bool encontradas = false;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Persona))) {
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

    Persona p;
    bool eliminada = false;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Persona))) {
        if (cedulaEliminar == p.cedula) {
            eliminada = true;
        } else {
            temporal.write(reinterpret_cast<const char*>(&p), sizeof(Persona));
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

    Persona p;
    bool encontrada = false;
    long posActual = 0;

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Persona))) {
        if (cedulaEditar == p.cedula) {
            encontrada = true;
            cout << "Persona encontrada. Nuevos datos:\n";
            cout << "Nombre (" << p.nombre << "): "; cin.getline(p.nombre, sizeof(p.nombre));
            cout << "Apellido (" << p.apellido << "): "; cin.getline(p.apellido, sizeof(p.apellido));
            cout << "Edad (" << p.edad << "): "; cin >> p.edad; limpiarBuffer();
            cout << "CI (" << p.coeficiente_intelectual << "): "; cin >> p.coeficiente_intelectual; limpiarBuffer();

            archivo.seekp(posActual); // Mover el puntero de escritura
            archivo.write(reinterpret_cast<const char*>(&p), sizeof(Persona));
            cout << "Datos actualizados." << endl;
            break;
        }
        posActual = archivo.tellg(); // Guardar la posición después de leer
    }
    if (!encontrada) { cout << "Cedula no encontrada para editar." << endl; }
    archivo.close();
}

void imprimirPersonaMayorEdad() {
    ifstream archivo(lista, ios::binary); 
    if (!archivo.is_open()) { cerr << "No hay personas." << endl; return; }

    Persona p;
    bool encontradas = false; 

    cout << "\n--- NOMBRES DE PERSONAS MAYORES DE EDAD ---" << endl;

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Persona))) {
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
            case 1: agregarPersona(); break;
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