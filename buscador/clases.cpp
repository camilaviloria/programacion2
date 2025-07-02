#include <iostream>
#include <locale>

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
        cout << "--- Informacion de la Publicacion ---" << std::endl;
        cout << "Titulo: " << titulo << std::endl;
        cout << "Autor: " << autor << std::endl;
        cout << "Año de Publicacion: " << anioPublicacion << std::endl;
    }
    virtual string getTipo() const = 0;

};