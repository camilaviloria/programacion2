#include <iostream>  
#include <fstream>   
#include <string>   
#include <limits>    
#include <cstring>   

using namespace std;

struct Producto {
    int Codigo;
    char Nombre[30];
    int Precio;
    int Stock;
    char Categoria;
    bool Activo;
};

const string PRODUCTO_FILE = "producto.bin"; 

void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void mostrarDatosProducto(const Producto& p) {
    cout << "Codigo: " << p.Codigo << ", Nombre: " << p.Nombre
              << ", Precio: " << p.Precio << ", Stock: " << p.Stock
              << ", Categoria: " << p.Categoria << ", Activo: " << (p.Activo ? "Si" : "No") << endl;
}
bool CodigoExistente(int codigoBuscado) {
    ifstream archivo(PRODUCTO_FILE, ios::binary);
    if (!archivo.is_open()) {
        return false;
    }

    Producto p;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.Codigo == codigoBuscado) {
            archivo.close();
            return true; 
        }
    }
    archivo.close();
    return false; 
}
void agregarProducto() {
    ofstream archivo(PRODUCTO_FILE, ios::binary | ios::app);
    if (!archivo.is_open()) { cerr << "Error al abrir archivo." << endl; return; }

    Producto p;
    cout << "Codigo: ";
    cin >> p.Codigo;
    limpiarBuffer();

    if (CodigoExistente(p.Codigo)) {
        cout << "Ya existe un producto con el codigo" << p.Codigo << endl;
        archivo.close(); 
        return;
    }

    cout << "Nombre: "; cin.getline(p.Nombre, sizeof(p.Nombre));
    cout << "Precio: "; cin >> p.Precio; limpiarBuffer();
    cout << "Stock: "; cin >> p.Stock; limpiarBuffer();
    cout << "Categoria (un solo caracter): "; cin >> p.Categoria; limpiarBuffer();
    cout << "Activo o no (1 activo, 0 inactivo): "; cin >> p.Activo; limpiarBuffer();

    archivo.write(reinterpret_cast<const char*>(&p), sizeof(Producto));
    archivo.close();
    cout << "Producto agregado." << endl;
}

void mostrarProductoActivos() {
    ifstream archivo(PRODUCTO_FILE, ios::binary);
    if (!archivo.is_open()) { cerr << "No hay productos." << endl; return; }

    Producto p;
    bool productos_activos = false; 
    cout << "\n--- LISTA DE PRODUCTOS ACTIVOS ---" << endl;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.Activo) {
            mostrarDatosProducto(p);
            productos_activos = true;
        }
    }
    archivo.close();

    if (!productos_activos) {
        cout << "No se encontraron productos activos." << endl;
    }
}
void mostrarProductoCategoria() {
    ifstream archivo(PRODUCTO_FILE, ios::binary);
    if (!archivo.is_open()) { cerr << "No hay productos para buscar." << endl; return; }

    char categoriaBuscada;
    cout << "Ingrese la categoria: ";
    cin >> categoriaBuscada;
    limpiarBuffer();

    Producto p;
    bool encontrada_categoria = false;
    cout << "\n--- LISTA DE PRODUCTOS POR CATEGORIA '" << categoriaBuscada << "' ---" << endl;

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.Categoria == categoriaBuscada) {
            mostrarDatosProducto(p);
            encontrada_categoria = true;
        }
    }
    archivo.close();

    if (!encontrada_categoria) {
        cout << "No se encontraron productos para la categoria '" << categoriaBuscada << "'." << endl;
    }
}

void buscarProductoCodigo() {
    ifstream archivo(PRODUCTO_FILE, ios::binary);
    if (!archivo.is_open()) { cerr << "No hay productos para buscar." << endl; return; }

    int codigoBuscado;
    cout << "Codigo a buscar: "; cin >> codigoBuscado; limpiarBuffer();

    Producto p;
    bool encontrado = false;
    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (codigoBuscado == p.Codigo) {
            cout << "Producto encontrado:" << endl;
            mostrarDatosProducto(p);
            encontrado = true;
            break;
        }
    }
    if (!encontrado) { cout << "codigo no encontrado." << endl; }
    archivo.close();
}

void editarProducto() {
    fstream archivo(PRODUCTO_FILE, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) { cerr << "No hay productos para editar." << endl; return; }

    int codigoeditar;
    cout << "Codigo a editar: "; cin >> codigoeditar; limpiarBuffer();

    Producto p;
    bool encontrada = false;
    long pos_inicio_registro = 0; 

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (codigoeditar == p.Codigo) {
            encontrada = true;
            cout << "Nuevos datos:\n";
            
            cout << "Precio actual (" << p.Precio << "): ";
            while (!(cin >> p.Precio)) { 
                cout << "Entrada invalida. Ingrese un numero para el Precio: ";
                cin.clear();
                limpiarBuffer();
            }
            limpiarBuffer();

            cout << "Categoria actual (" << p.Categoria << "): "; cin >> p.Categoria; limpiarBuffer();

            cout << "Stock actual (" << p.Stock << "): ";
            while (!(cin >> p.Stock)) { 
                cout << "Entrada invalida. Ingrese un numero para el Stock: ";
                cin.clear();
                limpiarBuffer();
            }
            limpiarBuffer();

            archivo.seekp(pos_inicio_registro); 
            archivo.write(reinterpret_cast<const char*>(&p), sizeof(Producto));
            cout << "Datos actualizados." << endl;
            break; 
        }
        pos_inicio_registro = archivo.tellg();
}
    if (!encontrada) { cout << "Codigo no encontrado para editar." << endl; }
    archivo.close();
}

void eliminarProducto() { 
    fstream archivo(PRODUCTO_FILE, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) { cerr << "No hay productos para eliminar" << endl; return; }

    int codigoEliminar;
    cout << "Ingrese el codigo del producto a eliminar: ";
    cin >> codigoEliminar;
    limpiarBuffer();

    Producto p;
    bool encontrado = false;
    long pos_inicio_registro = 0; 

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.Codigo == codigoEliminar) {
            encontrado = true;
            if (!p.Activo) { 
                cout << "El producto " << codigoEliminar << " ya esta inactivo." << endl;
                break; 
            }
            p.Activo = false;             
            archivo.seekp(pos_inicio_registro); 
            archivo.write(reinterpret_cast<const char*>(&p), sizeof(Producto));
            cout << "Producto con codigo " << codigoEliminar << " marcado como inactivo" << endl;
            break; 
        }
        pos_inicio_registro = archivo.tellg(); 
    }

    if (!encontrado) {
        cout << "Producto " << codigoEliminar << " no encontrado." << endl;
    }

    archivo.close(); 
}
void recuperarProducto() { 
    fstream archivo(PRODUCTO_FILE, ios::binary | ios::in | ios::out);
    if (!archivo.is_open()) { cerr << "No hay productos para recuperar." << endl; return; }

    int codigoRecuperar;
    cout << "Ingrese el codigo del producto a recuperar: ";
    cin >> codigoRecuperar;
    limpiarBuffer();

    Producto p;
    bool encontrado = false;
    long pos_inicio_registro = 0; 

    while (archivo.read(reinterpret_cast<char*>(&p), sizeof(Producto))) {
        if (p.Codigo == codigoRecuperar) {
            encontrado = true;
            if (p.Activo) {  
                cout << "El producto " << codigoRecuperar << " ya esta activo." << endl;
                break; 
            }p.Activo = true; 
            archivo.seekp(pos_inicio_registro);
            archivo.write(reinterpret_cast<const char*>(&p), sizeof(Producto));
            cout << "Producto con codigo " << codigoRecuperar << " marcado como activo." << endl;
            break;
        }
        pos_inicio_registro = archivo.tellg();
    }

    if (!encontrado) {
        cout << "Producto con codigo " << codigoRecuperar << " no encontrado." << endl;
    }

    archivo.close();
}
int main() {
    int opcion;
    do {
        cout << "\n--- MENU DE PRODUCTOS ---" << endl;
        cout << "1. Agregar Producto\n";
        cout << "2. Mostrar Productos Activos\n";
        cout << "3. Mostrar Productos Por Categoria\n";
        cout << "4. Buscar Productos Por Codigo\n";
        cout << "5. Editar Productos\n";
        cout << "6. Eliminar Producto\n";
        cout << "7. Recuperar Producto\n";
        cout << "0. Salir\n";
        cout << "Ingrese su opcion: ";

        while (!(cin >> opcion)) { 
            cout << "Entrada invalida. Ingrese un numero: ";
            cin.clear();
            limpiarBuffer();
        }
        limpiarBuffer(); 

        switch (opcion) {
            case 1: agregarProducto(); break;
            case 2: mostrarProductoActivos(); break;
            case 3: mostrarProductoCategoria(); break;
            case 4: buscarProductoCodigo(); break;
            case 5: editarProducto(); break;
            case 6: eliminarProducto(); break; 
            case 7: recuperarProducto(); break; 
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
