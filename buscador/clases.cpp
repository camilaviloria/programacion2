#include <iostream> 
#include <string>   
#include <vector>   
#include <limits>  
#include <algorithm> 
#include <cctype>   

using namespace std;

class Publicacion{
    private:
    string titulo;
    string autor;
    int anioPublicacion;

    public:    
    Publicacion(const string& titulo, const string& autor, int anioPublicacion)
        : titulo(titulo), autor(autor), anioPublicacion(anioPublicacion) {
    }
        virtual ~Publicacion() {
        cout << "Destructor de Publicacion llamado para: " << titulo << endl;
    }
    string getTitulo() const {
        return titulo;
    }
    string getAutor() const {
        return autor;
    }
    int getAnioPublicacion() const {
        return anioPublicacion;
    }

    virtual void mostrarInfo() const {
        cout << "--- Informacion de la Publicacion ---" << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Autor: " << autor << endl;
        cout << "Año de Publicacion: " << anioPublicacion << endl;
    }
    virtual string getTipo() const = 0;

};
class Libro : public Publicacion{
    private:
    int numPaginas;

    public: 
    Libro(const string& titulo, const string& autor, int anioPublicacion, int numPaginas)
        : Publicacion(titulo, autor, anioPublicacion), numPaginas(numPaginas) {

        }
        void mostrarInfo() const {
        Publicacion::mostrarInfo(); 
        cout << ", Paginas: " << numPaginas << endl;
    }
    string getTipo() const {
        return "Libro";
    }
      
};
class Revista : public Publicacion {
private:
    int numeroEdicion; 

public:
    Revista(const string& titulo, const string& autor, int anioPublicacion, int numeroEdicion)
        : Publicacion(titulo, autor, anioPublicacion), numeroEdicion(numeroEdicion) {
    }

    void mostrarInfo() const { 
        Publicacion::mostrarInfo(); 
        cout << ", Edicion: " << numeroEdicion << endl;
    }

    string getTipo() const { 
        return "Revista"; 
    }
};
class Periodico : public Publicacion {
private:
    string fechaPublicacion; 
    string ciudadPublicacion;

public:
    Periodico(const string& titulo, const string& autor, int anioPublicacion, string fechaPublicacion, string ciudadPublicacion)
        : Publicacion(titulo, autor, anioPublicacion), fechaPublicacion(fechaPublicacion), ciudadPublicacion(ciudadPublicacion) {
    }

    void mostrarInfo() const { 
        Publicacion::mostrarInfo(); 
        cout << ", Edicion: " << fechaPublicacion << endl;
        cout << ", Edicion: " << ciudadPublicacion << endl;

    }

    string getTipo() const { 
        return "Periodico"; 
    }
};

bool validarEntero(const string& str, int& valor) {
    try {
        size_t pos;
        valor = stoi(str, &pos);
        if (pos == str.length()) {
            return true;
        } else {
            cerr << "Entrada no es un entero puro." << endl;
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
            cout << "La entrada no puede estar vacia. Intente de nuevo." << endl;
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

vector<Publicacion*> catalogoPublicaciones;

void agregarPublicacion() {
    cout << "\n--- Agregar Nueva Publicacion ---" << endl;
    cout << "Seleccione el tipo de publicacion:" << endl;
    cout << "1. Libro" << endl;
    cout << "2. Revista" << endl;
    cout << "3. Periodico" << endl;
    cout << "4. Cancelar" << endl;

    int tipoSeleccionado = obtenerEntero("Ingrese su opcion: ");

    string titulo, autor;
    int anioPublicacion;
    Publicacion* nuevaPublicacion = nullptr;

    if (tipoSeleccionado >= 1 && tipoSeleccionado <= 3) { 
        cout << "\n--- Datos de la Publicacion ---" << endl;
        titulo = obtenerEntradaNoVacia("Titulo: ");
        autor = obtenerEntradaNoVacia("Autor: ");
        anioPublicacion = obtenerEntero("Anio de Publicacion (1500-2025): ");
        while (anioPublicacion < 1500 || anioPublicacion > 2025) { 
             cout << "Año invalido. Debe estar entre 1500 y 2025." << endl;
             anioPublicacion = obtenerEntero("Anio de Publicacion (1500-2025): ");
        }
    }

    switch (tipoSeleccionado) {
        case 1: { // Libro
            cout << "\n--- Datos Especificos del Libro ---" << endl;
            int numPaginas = obtenerEntero("Numero de Paginas: ");
            while (numPaginas <= 0) { 
                cout << "El numero de paginas debe ser mayor que 0." << endl;
                numPaginas = obtenerEntero("Numero de Paginas: ");
            }
            nuevaPublicacion = new Libro(titulo, autor, anioPublicacion, numPaginas);
            break;
        }
        case 2: { 
            cout << "\n--- Datos Especificos de la Revista ---" << endl;
            int numeroEdicion = obtenerEntero("Numero de Edicion: ");
            while (numeroEdicion <= 0) { 
                cout << "El numero de edicion debe ser mayor que 0." << endl;
                numeroEdicion = obtenerEntero("Numero de Edicion: ");
            }
            nuevaPublicacion = new Revista(titulo, autor, anioPublicacion, numeroEdicion);
            break;
        }
        case 3: { 
            cout << "\n--- Datos Especificos del Periodico ---" << endl;
            string fechaPublicacion = obtenerEntradaNoVacia("Fecha de Publicacion: ");
            string ciudadPublicacion = obtenerEntradaNoVacia("Ciudad de Publicacion: ");
            nuevaPublicacion = new Periodico(titulo, autor, anioPublicacion, fechaPublicacion, ciudadPublicacion);
            break;
        }
        case 4: { 
            cout << "Operacion cancelada." << endl;
            return;
        }
        default: {
            cout << "Opcion no valida. Volviendo al menu principal." << endl;
            return;
        }
    }

    if (nuevaPublicacion) {
        catalogoPublicaciones.push_back(nuevaPublicacion);
        cout << "Publicacion '" << nuevaPublicacion->getTitulo() << "' de tipo '" << nuevaPublicacion->getTipo() << "' agregada al catalogo." << endl;
    }
}