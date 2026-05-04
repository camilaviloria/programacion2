#include <iostream>   
#include <string>     
#include <vector>     
#include <limits>    
#include <fstream>    
#include <sstream>    
#include <algorithm>  

using namespace std;

void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool validarEntero(const string& str, int& valor) {
    try {
        size_t pos;
        valor = stoi(str, &pos);
        if (pos == str.length()) {
            return true;
        } else {
            cerr << "Error: Entrada no es un entero puro." << endl;
            return false;
        }
    } catch (const out_of_range& oor) {
        cerr << "Error: Numero fuera de rango para un entero." << endl;
        return false;
    } catch (const invalid_argument& ia) {
        cerr << "Error: Entrada no es un numero valido." << endl;
        return false;
    }
}

string obtenerEntradaNoVacia(const string& prompt) {
    string entrada;
    while (true) {
        cout << prompt;
        getline(cin, entrada);
        if (!entrada.empty()) {
            return entrada;
        } else {
            cout << "La entrada no puede estar vacia." << endl;
        }
    }
}

int obtenerEntero(const string& prompt) {
    string entradaStr;
    int valor;
    while (true) {
        cout << prompt;
        getline(cin, entradaStr);
        if (validarEntero(entradaStr, valor)) {
            return valor;
        }
    }
}

class Persona {
private: 
    string nombre;  
    string apellido;  
    string cedula;    
    int edad;
    int iq;

public:
    Persona() : nombre(""), apellido(""), cedula(""), edad(0), iq(0) {}

    Persona(const string& _nombre, const string& _apellido, const string& _cedula, int _edad, int _iq)
        : nombre(_nombre), apellido(_apellido), cedula(_cedula), edad(_edad), iq(_iq) {}

    virtual ~Persona() {
        cout << "Destructor de Persona llamado para: " << nombre << " " << apellido << endl;
    }

    string getNombre() const { return nombre; }
    string getApellido() const { return apellido; }
    string getCedula() const { return cedula; }
    int getEdad() const { return edad; }
    int getIq() const { return iq; }

    void setNombre(const string& _nombre) { nombre = _nombre; }
    void setApellido(const string& _apellido) { apellido = _apellido; }
    void setEdad(int _edad) { edad = _edad; }
    void setIq(int _iq) { iq = _iq; }

    void leerDatos() {
        setNombre(obtenerEntradaNoVacia("Nombre: "));
        setApellido(obtenerEntradaNoVacia("Apellido: "));
        
        cedula = obtenerEntradaNoVacia("Cedula: "); 
        
        edad = obtenerEntero("Edad: ");
        while (edad < 0 || edad > 120) { 
            cout << "Edad invalida. Ingrese una edad entre 0 y 120: ";
            edad = obtenerEntero("Edad: ");
        }
        
        iq = obtenerEntero("IQ: ");
        while (iq < 0 || iq > 200) { 
            cout << "IQ invalido. Ingrese un IQ entre 0 y 200: ";
            iq = obtenerEntero("IQ: ");
        }
    }

    void mostrarDatos() const {
        cout << "  Nombre: " << nombre << " " << apellido << endl;
        cout << "  Cedula: " << cedula << endl;
        cout << "  Edad: " << edad << endl;
        cout << "  IQ: " << iq << endl;
    }

    string toCsvString() const {
        stringstream ss;
        ss << nombre << "," << apellido << "," << cedula << "," << edad << "," << iq;
        return ss.str();
    }

    bool fromCsvString(const string& line) {
        stringstream ss(line);
        string segment;
        vector<string> segments;

        while(getline(ss, segment, ',')) {
            segments.push_back(segment);
        }
        if (segments.size() != 5) {
            cerr << "Error de formato en linea CSV (cantidad de segmentos incorrecta): " << line << endl;
            return false;
        }

        try {
            nombre = segments[0];
            apellido = segments[1];
            cedula = segments[2];
            edad = stoi(segments[3]);
            iq = stoi(segments[4]);
        } catch (const std::exception& e) {
            cerr << "Error al parsear datos numericos de la linea CSV: " << e.what() << " - Linea: " << line << endl;
            return false;
        }
        return true;
    }
};

vector<Persona*> g_personas; 
const string PERSONAS_FILE = "personas.txt"; 

void cargarDatos() {
    ifstream archivo(PERSONAS_FILE); 
    if (!archivo.is_open()) {
        cerr << "Archivo '" << PERSONAS_FILE << "' no encontrado o no se puede abrir. Se iniciara con datos vacios." << endl;
        return;
    }

    for (size_t i = 0; i < g_personas.size(); ++i) {
        delete g_personas[i];
    }
    g_personas.clear(); 
    
    string line;
    while (getline(archivo, line)) { 
        if (line.empty()) continue; 
        Persona* p = new Persona(); 
        if (p->fromCsvString(line)) { 
            g_personas.push_back(p); 
        } else {
            delete p; 
        }
    }
    archivo.close();
    cout << g_personas.size() << " personas cargadas desde '" << PERSONAS_FILE << "'." << endl;
}

void guardarDatos() {
    ofstream archivo(PERSONAS_FILE, ios::trunc); 
    if (!archivo.is_open()) {
        cerr << "ERROR: No se pudo abrir el archivo para guardar los datos." << endl;
        return;
    }

    for (size_t i = 0; i < g_personas.size(); ++i) { 
        archivo << g_personas[i]->toCsvString() << endl; 
    }
    archivo.close();
    cout << g_personas.size() << " personas guardadas en '" << PERSONAS_FILE << "'." << endl;
}

bool cedulaExistente(const string& cedulaBuscada) {
    for (size_t i = 0; i < g_personas.size(); ++i) { 
        if (g_personas[i]->getCedula() == cedulaBuscada) { 
            return true;
        }
    }
    return false;
}

void agregarPersona() {
    cout << "\n--- AGREGAR NUEVA PERSONA ---" << endl;
    Persona* nuevaPersona = new Persona(); 
    
    nuevaPersona->leerDatos(); 

    if (cedulaExistente(nuevaPersona->getCedula())) {
        cout << "ERROR: Ya existe una persona con la cedula " << nuevaPersona->getCedula() << ". No se puede agregar." << endl;
        delete nuevaPersona; 
        return;
    }
    
    g_personas.push_back(nuevaPersona); 
    cout << "Persona agregada." << endl;
}

void mostrarPersonas() {
    cout << "\n--- LISTA DE PERSONAS ---" << endl;
    if (g_personas.empty()) {
        cout << "No hay personas en el sistema." << endl;
        return;
    }

    for (size_t i = 0; i < g_personas.size(); ++i) {
        cout << "\n--- Persona #" << (i + 1) << " ---" << endl;
        g_personas[i]->mostrarDatos(); 
    }
}

void buscarPersonaPorCedula() {
    cout << "\n--- BUSCAR PERSONA POR CEDULA ---" << endl;
    if (g_personas.empty()) {
        cout << "No hay personas en el sistema para buscar." << endl;
        return;
    }

    string cedulaBuscada = obtenerEntradaNoVacia("Cedula a buscar: ");

    bool encontrada = false;
    for (size_t i = 0; i < g_personas.size(); ++i) { 
        if (g_personas[i]->getCedula() == cedulaBuscada) { 
            cout << "Persona encontrada:" << endl;
            g_personas[i]->mostrarDatos(); 
            encontrada = true;
            break;
        }
    }
    if (!encontrada) {
        cout << "Cedula no encontrada." << endl;
    }
}

void buscarPersonaPorEdad() {
    cout << "\n--- BUSCAR PERSONAS POR EDAD ---" << endl;
    if (g_personas.empty()) {
        cout << "No hay personas en el sistema para buscar." << endl;
        return;
    }

    int edadBuscada = obtenerEntero("Edad a buscar: ");

    bool encontradas = false;
    for (size_t i = 0; i < g_personas.size(); ++i) { 
        if (g_personas[i]->getEdad() == edadBuscada) {
            if (!encontradas) { cout << "Personas con edad " << edadBuscada << ":" << endl; }
            g_personas[i]->mostrarDatos(); 
            encontradas = true;
        }
    }
    if (!encontradas) {
        cout << "No hay personas con esa edad." << endl;
    }
}

void eliminarPersona() {
    cout << "\n--- ELIMINAR PERSONA ---" << endl;
    if (g_personas.empty()) {
        cout << "No hay personas en el sistema para eliminar." << endl;
        return;
    }

    string cedulaEliminar = obtenerEntradaNoVacia("Cedula de la persona a eliminar: ");

    bool eliminada = false;
    for (vector<Persona*>::iterator it = g_personas.begin(); it != g_personas.end(); ++it) { 
        if ((*it)->getCedula() == cedulaEliminar) { 
            cout << "¿Esta seguro de eliminar la siguiente persona? (s/n)" << endl;
            (*it)->mostrarDatos(); 
            string confirmacion = obtenerEntradaNoVacia("Confirmar (s/n): ");
            transform(confirmacion.begin(), confirmacion.end(), confirmacion.begin(), ::tolower);

            if (confirmacion == "s") {
                delete *it; 
                it = g_personas.erase(it); 
                cout << "Persona eliminada del sistema (recuerde guardar los cambios)." << endl;
                eliminada = true;
            } else {
                cout << "Eliminacion cancelada." << endl;
            }
            break; 
        }
    }

    if (!eliminada) {
        cout << "Cedula no encontrada para eliminar." << endl;
    }
}

void editarPersona() {
    cout << "\n--- EDITAR PERSONA ---" << endl;
    if (g_personas.empty()) {
        cout << "No hay personas en el sistema para editar." << endl;
        return;
    }

    string cedulaEditar = obtenerEntradaNoVacia("Cedula de la persona a editar: ");

    bool encontrada = false;
    for (size_t i = 0; i < g_personas.size(); ++i) {
        if (g_personas[i]->getCedula() == cedulaEditar) { 
            encontrada = true;
            cout << "Persona encontrada. Nuevos datos:\n";
            
            string nuevoNombre = obtenerEntradaNoVacia("Nuevo Nombre (" + g_personas[i]->getNombre() + "): ");
            g_personas[i]->setNombre(nuevoNombre);

            string nuevoApellido = obtenerEntradaNoVacia("Nuevo Apellido (" + g_personas[i]->getApellido() + "): ");
            g_personas[i]->setApellido(nuevoApellido);
            
            int nuevaEdad = obtenerEntero("Nueva Edad (" + to_string(g_personas[i]->getEdad()) + "): ");
            while (nuevaEdad < 0 || nuevaEdad > 120) {
                cout << "Edad invalida. Ingrese una edad entre 0 y 120: ";
                nuevaEdad = obtenerEntero("Nueva Edad: ");
            }
            g_personas[i]->setEdad(nuevaEdad);

            int nuevoIq = obtenerEntero("Nuevo IQ (" + to_string(g_personas[i]->getIq()) + "): ");
            while (nuevoIq < 0 || nuevoIq > 200) {
                cout << "IQ invalido. Ingrese un IQ entre 0 y 200: ";
                nuevoIq = obtenerEntero("Nuevo IQ: ");
            }
            g_personas[i]->setIq(nuevoIq);

            cout << "Datos actualizados en memoria (recuerde guardar los cambios)." << endl;
            break;
        }
    }
    if (!encontrada) {
        cout << "Cedula no encontrada para editar." << endl;
    }
}

void imprimirPersonaMayorEdad() {
    cout << "\n--- PERSONA CON LA MAYOR EDAD ---" << endl;
    if (g_personas.empty()) {
        cout << "No hay personas en el sistema." << endl;
        return;
    }

    const Persona* personaMayor = nullptr;
    int maxEdad = -1; 

    for (size_t i = 0; i < g_personas.size(); ++i) { 
        if (g_personas[i]->getEdad() > maxEdad) {
            maxEdad = g_personas[i]->getEdad();
            personaMayor = g_personas[i]; 
        }
    }
    if (personaMayor) {
        cout << "La persona con la mayor edad es:" << endl;
        personaMayor->mostrarDatos();
    } else {
        cout << "No se pudo determinar la persona con mayor edad." << endl;
    }
}

int main() {
    cargarDatos(); 

    int opcion;
    do {
        cout << "\n--- MENU DE GESTION DE PERSONAS ---" << endl;
        cout << "1. Agregar Persona" << endl;
        cout << "2. Mostrar Todas las Personas" << endl;
        cout << "3. Buscar Persona por Cedula" << endl;
        cout << "4. Buscar Personas por Edad" << endl;
        cout << "5. Eliminar Persona" << endl;
        cout << "6. Editar Persona" << endl;
        cout << "7. Imprimir Persona con Mayor Edad" << endl;
        cout << "8. Guardar Cambios en Archivo" << endl; 
        cout << "0. Salir" << endl;
        cout << "Opcion: ";
        
        opcion = obtenerEntero(""); 
        while (opcion < 0 || opcion > 8) {
            cout << "Opcion invalida. Ingrese un numero entre 0 y 8: ";
            opcion = obtenerEntero("");
        }

        switch (opcion) {
            case 1: agregarPersona(); break;
            case 2: mostrarPersonas(); break;
            case 3: buscarPersonaPorCedula(); break;
            case 4: buscarPersonaPorEdad(); break;
            case 5: eliminarPersona(); break;
            case 6: editarPersona(); break;
            case 7: imprimirPersonaMayorEdad(); break;
            case 8: guardarDatos(); break; 
            case 0:
                guardarDatos(); 
                cout << "Saliendo del programa. Datos guardados" << endl;
                for (size_t i = 0; i < g_personas.size(); ++i) {
                    delete g_personas[i];
                }
                g_personas.clear(); 
                break;
            default:
                cout << "Opcion no valida." << endl;
                break;
        }
    } while (opcion != 0);

    return 0;
}