#include <iostream> 
#include <fstream>  
#include <string>   
#include <vector>   
#include <algorithm> 
#include <limits>    
#include <cctype>    

using namespace std;

struct Producto {
    int Codigo;
    char Nombre[30];
    int Precio;
    int Stock;
    char Categoria;
    bool Activo;
};

const string productos = "productos.bin";

void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
};

void agregarProducto() {
    ofstream archivo(productos, ios::binary | ios::app); 
    if (!archivo.is_open()) { cerr << "error al abrir archivo." << endl; return; }

    Producto p;
    cout << "Codigo: "; cin >> p.Codigo; limpiarBuffer();
    cout << "Nombre: "; cin.getline(p.Nombre, sizeof(p.Nombre));
    cout << "Precio: "; cin >> p.Precio; limpiarBuffer();
    cout << "Stock: "; cin >> p.Stock; limpiarBuffer();
    cout << "Categoria: "; cin >> p.Categoria; limpiarBuffer();
    cout << "Activo o no: "; cin >> p.Activo; limpiarBuffer();

    archivo.write(reinterpret_cast<const char*>(&p), sizeof(Producto));
    archivo.close();
    cout << "Producto agregado." << endl;
}

void mostrarDatosProducto(const Producto& p) {
    cout << "Codigo: " << p.Codigo << ", Nombre: " << p.Nombre
              << ", Precio: " << p.Precio << ", Stock: " << p.Stock
              << ", Categoria: " << p.Categoria << ", Activo o no: " << p.Activo << endl;
}

void mostrarProducto() {
    ifstream archivo(productos, ios::binary);
    if (!archivo.is_open()) { cerr << "No hay productos." << endl; return; }

    Producto p;
    cout << "\n--- LISTA DE PRODUCTOS ---" << endl;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        mostrarDatosProducto(p);
    }
    archivo.close();
}