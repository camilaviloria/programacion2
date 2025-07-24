#include "MatrizLib.hpp" 
#include <stdexcept>     

namespace MatrizLib {    
    Matriz crearMatriz(int filas, int columnas) {
        return Matriz(filas, columnas);
    }
} 