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
        cout << "--- Informacion de la Publicacion ---" << endl;
        cout << "Titulo: " << titulo << endl;
        cout << "Autor: " << autor << endl;
        cout << "Año de Publicacion: " << anioPublicacion << endl;
    }
    virtual string getTipo() const = 0;

};

int main() {
    cout << "Iniciando el programa de gestion de publicaciones..." << endl;

    cout << "Programa finalizado." << endl;
    return 0; 
}