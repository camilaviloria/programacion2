#include <iostream> 
#include <string>   
#include <vector>   
#include <limits>  
#include <algorithm> 
#include <cctype>   

using namespace std;

class Matriz {
    private:
    double** datos;
    int filas;
    int columnas;
    public:
    Matriz() : datos(0), filas(0), columnas(0) {}

    Matriz(int _filas, int _columnas)
        : filas(_filas), columnas(_columnas) {}

    virtual ~Matriz() {
        cout << "Destructor de Matriz: " << endl;
    }

};