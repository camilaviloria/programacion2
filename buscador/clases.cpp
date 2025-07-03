#include <iostream>
#include <locale>
#include <vector>

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
class Libro : private Publicacion{
    private:
    int numPaginas;

    public: 
    Libro(const string& titulo, const string& autor, int anioPublicacion, int numPaginas)
        : Publicacion(titulo, autor, anioPublicacion), numPaginas(numPaginas) {

        }
        void mostrarInfo() {
        Publicacion::mostrarInfo(); 
        cout << ", Paginas: " << numPaginas << endl;
    }
    string getTipo() {
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

    void mostrarInfo() { 
        Publicacion::mostrarInfo(); 
        cout << ", Edicion: " << numeroEdicion << std::endl;
    }

    string getTipo() { 
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

    void mostrarInfo() { 
        Publicacion::mostrarInfo(); 
        cout << ", Edicion: " << fechaPublicacion << endl;
        cout << ", Edicion: " << ciudadPublicacion << endl;

    }

    string getTipo() { 
        return "Periodico"; 
    }
};

int main() {
    cout << "Iniciando el programa de gestion de publicaciones..." << endl;

    cout << "Programa finalizado." << endl;
    return 0; 
}