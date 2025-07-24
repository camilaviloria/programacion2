#include "matriz.hpp"
#include <iostream>
#include <limits> 
#include <iomanip> 
#include <sstream> 
#include <cmath>  

void limpiarBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

double obtenerDoubleValido(const std::string& prompt) {
    double valor;
    while (true) {
        std::cout << prompt;
        std::cin >> valor;
        if (std::cin.fail()) {
            std::cout << "Entrada invalida. Por favor, ingrese un numero valido." << std::endl;
            std::cin.clear(); 
            limpiarBuffer();  
        } else {
            limpiarBuffer(); 
            return valor;
        }
    }
}
void Matriz::copiarDatos(const Matriz& otra) {

    filas = otra.filas;
    columnas = otra.columnas;

    if (filas > 0 && columnas > 0) {
        datos = new double*[filas];
        for (int i = 0; i < filas; ++i) {
            datos[i] = new double[columnas];
            for (int j = 0; j < columnas; ++j) {
                datos[i][j] = otra.datos[i][j];
            }
        }
    } else {
        datos = nullptr; 
    }
}

void Matriz::liberarDatos() {
    if (datos != nullptr) {
        for (int i = 0; i < filas; ++i) {
            delete[] datos[i];
        }
        delete[] datos;
        datos = nullptr;
    }
    filas = 0;
    columnas = 0;
}
double Matriz::calcularDeterminanteCofactores(double** mat, int n) {
    double det = 0;
    if (n == 1) {
        return mat[0][0];
    }
    if (n == 2) {
        return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    }
    double** subMatriz = new double*[n - 1];
    for (int i = 0; i < n - 1; ++i) {
        subMatriz[i] = new double[n - 1];
    }
    int signo = 1; 
    for (int c = 0; c < n; ++c) { 
        int sub_i = 0; 
        for (int i = 1; i < n; ++i) { 
            int sub_j = 0; 
            for (int j = 0; j < n; ++j) {
                if (j == c) { 
                    continue;
                }
                subMatriz[sub_i][sub_j] = mat[i][j];
                sub_j++;
            }
            sub_i++;
        }
        det += signo * mat[0][c] * calcularDeterminanteCofactores(subMatriz, n - 1);
        signo = -signo; 
    }

    for (int i = 0; i < n - 1; ++i) {
        delete[] subMatriz[i];
    }
    delete[] subMatriz;

    return det;
}
Matriz::Matriz() : datos(nullptr), filas(0), columnas(0) {
}

Matriz::Matriz(int f, int c) : datos(nullptr), filas(f), columnas(c) {
    if (f <= 0 || c <= 0) {
        throw std::runtime_error("Matrix dimensions must be positive.");
    }
    datos = new double*[filas];
    for (int i = 0; i < filas; ++i) {
        datos[i] = new double[columnas];
        for (int j = 0; j < columnas; ++j) {
            datos[i][j] = 0.0;
        }
    }
}

Matriz::Matriz(const Matriz& otra) : datos(nullptr), filas(0), columnas(0) {
    copiarDatos(otra);
}

Matriz& Matriz::operator=(const Matriz& otra) {
    if (this != &otra) { 
        liberarDatos(); 
        copiarDatos(otra); 
    }
    return *this;
}

Matriz::~Matriz() {
    liberarDatos();
}

void Matriz::llenarMatriz() {
    if (filas == 0 || columnas == 0) {
        std::cout << "The matrix is empty. Cannot fill data." << std::endl;
        return;
    }
    std::cout << "\n--- Fill Matrix (" << filas << "x" << columnas << ") ---" << std::endl;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            datos[i][j] = obtenerDoubleValido("Enter value for [" + std::to_string(i) + "][" + std::to_string(j) + "]: ");
        }
    }
    std::cout << "Matrix filled successfully." << std::endl;
}

void Matriz::mostrarMatriz() const {
    if (filas == 0 || columnas == 0) {
        std::cout << "The matrix is empty." << std::endl;
        return;
    }
    std::cout << "\n--- Matrix (" << filas << "x" << columnas << ") ---" << std::endl;
    int max_width = 0;
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(4) << datos[i][j]; 
            int current_width = ss.str().length();
            if (current_width > max_width) {
                max_width = current_width;
            }
        }
    }
    if (max_width < 8) max_width = 8;

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            std::cout << std::fixed << std::setprecision(4) << std::setw(max_width + 2) << datos[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << "-----------------------------------" << std::endl;
}

Matriz Matriz::transpuesta() const {
    if (filas == 0 || columnas == 0) {
        throw std::runtime_error("matriz vacia");
    }
    Matriz resultado(columnas, filas); 
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            resultado.datos[j][i] = datos[i][j];
        }
    }
    return resultado;
}

double Matriz::determinante() const {
    if (filas == 0 || columnas == 0) {
        throw std::runtime_error("matriz vacia.");
    }
    if (filas != columnas) {
        throw std::runtime_error("no se puede calcular el determinante.");
    }
    return calcularDeterminanteCofactores(filas, columnas);
}

Matriz Matriz::suma(const Matriz& otra) const {
    if (filas != otra.filas || columnas != otra.columnas) {
        throw std::runtime_error("Matrices deben tener la misma dimension para la suma.");
    }
    if (filas == 0 || columnas == 0) {
        throw std::runtime_error("matrices vacias.");
    }

    Matriz resultado(filas, columnas);
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            resultado.datos[i][j] = datos[i][j] + otra.datos[i][j];
        }
    }
    return resultado;
}

Matriz Matriz::multiplicacion(const Matriz& otra) const {
    if (columnas != otra.filas) {
        throw std::runtime_error("Matrices no son compatibles para la multiplicacion.");
    }
    if (filas == 0 || columnas == 0 || otra.filas == 0 || otra.columnas == 0) {
        throw std::runtime_error("matrices vacia.");
    }

    Matriz resultado(filas, otra.columnas); 
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < otra.columnas; ++j) {
            resultado.datos[i][j] = 0.0; 
            for (int k = 0; k < columnas; ++k) { 
                resultado.datos[i][j] += datos[i][k] * otra.datos[k][j];
            }
        }
    }
    return resultado;
}

bool Matriz::esIgual(const Matriz& otra) const {
    if (filas != otra.filas || columnas != otra.columnas) {
        return false; 
    }
    if (filas == 0 && columnas == 0) {
        return true;
    }

    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            if (std::abs(datos[i][j] - otra.datos[i][j]) > 1e-9) { 
                return false;
            }
        }
    }
    return true;
}
