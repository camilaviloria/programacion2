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
        cout << ", fecha: " << fechaPublicacion << endl;
        cout << ", ciudad: " << ciudadPublicacion << endl;

    }

    string getTipo() const { 
        return "Periodico"; 
    }
};

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
            cerr << "Entrada no es un entero puro." << endl;
            return false;
        }
        }catch (const out_of_range& oor) {
            cerr << "Error: Numero fuera de rango para un entero." << endl;
            return false;
            }
            catch (const invalid_argument& ia) {
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

    string titulo; 
    string autor;
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
        case 1: { 
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

void mostrarCatalogo() {
    if (catalogoPublicaciones.empty()) {
        cout << "\nEl catalogo esta vacio." << endl;
        return;
    }
    cout << "\n--- Catalogo de Publicaciones ---" << endl;
    for (size_t i = 0; i < catalogoPublicaciones.size(); ++i) {
        cout << "\n--- Publicacion: " << (i + 1) << " (" << catalogoPublicaciones[i]->getTipo() << ") ---" << endl; 
        catalogoPublicaciones[i]->mostrarInfo(); 
    }
}

void buscarPublicacionPorTitulo() { 
    cout << "\n--- BUSCAR PUBLICACION POR TITULO ---" << endl;
    if (catalogoPublicaciones.empty()) {
        cout << "El catalogo esta vacio." << endl;
        return;
    }

    string tituloBuscado = obtenerEntradaNoVacia("Ingrese el titulo a buscar: ");

    bool encontrado = false;
    cout << "\n--- RESULTADOS DE LA BUSQUEDA ---" << endl;
    
    size_t i = 0; 
    while (i < catalogoPublicaciones.size()) { 
        const Publicacion* pub = catalogoPublicaciones[i];
        string tituloActual = pub->getTitulo(); 
        if (tituloActual.find(tituloBuscado) != string::npos) {
            pub->mostrarInfo();
            cout << "------------------------------------" << endl;
            encontrado = true;
        }
        i++; 
    }

    if (!encontrado) {
        cout << "No se encontraron publicaciones con ese titulo." << endl;
    }
}
void eliminarPublicacion() {
    if (catalogoPublicaciones.empty()) {
        cout << "\nEl catalogo esta vacio. No hay publicaciones para eliminar." << endl;
        return;
    }

    mostrarCatalogo(); 

    int indiceEliminar = obtenerEntero("Ingrese el numero de la publicacion a eliminar: ");

    if (indiceEliminar == 0) {
        cout << "Eliminacion cancelada." << endl;
        return;
    }

    int realIndice = indiceEliminar - 1; 

    if (realIndice >= 0 && realIndice < catalogoPublicaciones.size()) {
        cout << "¿Esta seguro de eliminar la siguiente publicacion? (s/n)" << endl;
        catalogoPublicaciones[realIndice]->mostrarInfo();
        string confirmacion = obtenerEntradaNoVacia("Confirmar (s/n): ");

        transform(confirmacion.begin(), confirmacion.end(), confirmacion.begin(), ::tolower);

        if (confirmacion == "s") {
            delete catalogoPublicaciones[realIndice]; 
            catalogoPublicaciones.erase(catalogoPublicaciones.begin() + realIndice); 
            cout << "Publicacion eliminada." << endl;
        } else {
            cout << "Eliminacion cancelada." << endl;
        }
    } else {
        cout << "Numero de publicacion invalido." << endl;
    }
}
void mostrarEstadisticas() { 
    cout << "\n--- ESTADISTICAS DEL CATALOGO ---" << endl;
    if (catalogoPublicaciones.empty()) {
        cout << "El catalogo esta vacio." << endl;
        return;
    }

    int totalPublicaciones = catalogoPublicaciones.size();
    int totalLibros = 0;
    int totalRevistas = 0;
    int totalPeriodicos = 0; 
    int anioMasAntiguo = 9999; 
    int anioMasReciente = 0; 
    string tituloMasAntiguo = "N/A";

    for (size_t i = 0; i < catalogoPublicaciones.size(); ++i) {
        const Publicacion* pub = catalogoPublicaciones[i]; 
        if (pub->getTipo() == "Libro") {
            totalLibros++;
        } else if (pub->getTipo() == "Revista") {
            totalRevistas++;
        } else if (pub->getTipo() == "Periodico") { 
            totalPeriodicos++;
        }

        if (pub->getAnioPublicacion() < anioMasAntiguo) {
            anioMasAntiguo = pub->getAnioPublicacion();
            tituloMasAntiguo = pub->getTitulo(); 
        }
        if (pub->getAnioPublicacion() > anioMasReciente) { 
            anioMasReciente = pub->getAnioPublicacion();
        }
    }

    cout << "Total de publicaciones: " << totalPublicaciones << endl;
    cout << "Cantidad de Libros: " << totalLibros << endl;
    cout << "Cantidad de Revistas: " << totalRevistas << endl;
    cout << "Cantidad de Periodicos: " << totalPeriodicos << endl; 
    cout << "Publicacion mas antigua: '" << tituloMasAntiguo << "' Año: " << anioMasAntiguo << endl;
    cout << "Año de publicacion mas reciente: " << anioMasReciente << endl; 
}
void liberarTodaMemoria() { 

for (size_t i = 0; i < catalogoPublicaciones.size(); ++i) { 
        delete catalogoPublicaciones[i]; 
    }
    catalogoPublicaciones.clear(); 
    cout << "Toda la memoria ha sido liberada." << endl;
}

int main() {
    int opcion;
    do {
        cout << "\n===== SISTEMA DE GESTION DE BIBLIOTECA =====" << endl;
        cout << "1. Agregar nueva publicacion" << endl;
        cout << "2. Mostrar todas las publicaciones" << endl;
        cout << "3. Buscar publicacion por titulo" << endl;
        cout << "4. Eliminar publicacion" << endl;
        cout << "5. Mostrar estadisticas" << endl;
        cout << "6. Salir del programa" << endl; 
        cout << "Seleccione una opcion: ";
        if (!(cin >> opcion)) { 
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            limpiarBuffer();
        }
        switch (opcion) {
            case 1: agregarPublicacion(); break; 
            case 2: mostrarCatalogo(); break;
            case 3: buscarPublicacionPorTitulo(); break;
            case 4: eliminarPublicacion(); break;
            case 5: mostrarEstadisticas(); break;
            case 6: 
                cout << "¿Esta seguro que desea salir? Toda la memoria sera liberada. (s/n): ";
                char confirmacion;
                cin >> confirmacion;
                limpiarBuffer();
                if (tolower(confirmacion) == 's') {
                    liberarTodaMemoria(); 
                    cout << "Saliendo del programa" << endl;
                    opcion = 0; 
                } else {
                    opcion = -1; 
                }
                break;
            default:
                cout << "Opcion no valida." << endl;
                break;
        }
    } while (opcion != 0); 

    return 0;
}