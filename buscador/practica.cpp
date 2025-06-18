#include <iostream> 
#include <fstream>  
#include <string>   
#include <limits>    

using namespace std;

struct Producto {
    int Codigo;
    char Nombre[30];
    int Precio;
    int Stock;
    char Categoria[30];
    bool Activo;
};

const string producto = "producto.bin";

void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
};

void agregarProducto() {
    ofstream archivo(producto, ios::binary | ios::app); 
    if (!archivo.is_open()) { cerr << "error al abrir archivo." << endl; return; }

    Producto p;
    cout << "Codigo: "; cin >> p.Codigo; limpiarBuffer();
    cout << "Nombre: "; cin.getline(p.Nombre, sizeof(p.Nombre));
    cout << "Precio: "; cin >> p.Precio; limpiarBuffer();
    cout << "Stock: "; cin >> p.Stock; limpiarBuffer();
    cout << "Categoria: "; cin >> p.Categoria; limpiarBuffer();
    cout << "Activo o no (1 para activo, 0 para inactivo): "; cin >> p.Activo; limpiarBuffer(); 

    archivo.write(reinterpret_cast<const char*>(&p), sizeof(Producto));
    archivo.close();
    cout << "Producto agregado." << endl;
}

void mostrarDatosProducto(const Producto& p) {
    cout << "Codigo: " << p.Codigo << ", Nombre: " << p.Nombre
              << ", Precio: " << p.Precio << ", Stock: " << p.Stock
              << ", Categoria: " << p.Categoria << ", Activo o no: " << (p.Activo ? "Si" : "No") << endl;
}

void mostrarProducto() {
    ifstream archivo(producto, ios::binary);
    if (!archivo.is_open()) { cerr << "No hay productos." << endl; return; }

    Producto p;
    bool productos_activos_encontrados = false; 
    cout << "\n--- LISTA DE PRODUCTOS ACTIVOS ---" << endl;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.Activo) {
            mostrarDatosProducto(p);
            productos_activos_encontrados = true;
        }
    }
    archivo.close();

    if (!productos_activos_encontrados) {
        cout << "No se encontraron productos activos." << endl;
    }
}

int main() {
    int opcion;
    do {
        cout << "\n--- MENU DE PRODUCTOS ---" << endl;
        cout << "1. Agregar Producto\n";
        cout << "2. Mostrar Productos Activos\n"; 
        cout << "0. Salir\n";
        cout << "Ingrese su opcion: ";
        while (!(cin >> opcion)) { 
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            limpiarBuffer();
        }
        limpiarBuffer(); 

        switch (opcion) {
            case 1:
                agregarProducto();
                break;
            case 2:
                mostrarProducto();
                break;
            case 0:
                cout << "Saliendo del programa." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente de nuevo." << endl;
                break;
        }
    } while (opcion != 0);

    return 0; 
}
