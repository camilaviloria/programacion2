#include <iostream> 
#include <string>    
#include <limits>    
#include <stdexcept>
#include "matriz.hpp"    
#include "MatrizLib.hpp" 

using namespace MatrizLib;

bool validarEntero(const std::string& str, int& valor) {
    try {
        size_t pos;
        valor = std::stoi(str, &pos); 
        if (pos == str.length()) { 
            return true; 
        } else {
            std::cerr << "Error: Entrada no es un entero." << std::endl;
            return false;
        }
    } catch (const std::out_of_range& oor) {
        std::cerr << "Error: Numero fuera de rango para un entero." << std::endl;
        return false;
    } catch (const std::invalid_argument& ia) {
        std::cerr << "Error: Entrada no es un numero valido." << std::endl;
        return false;
    }
}

int obtenerEntero(const std::string& prompt) {
    std::string entradaStr;
    int valor;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, entradaStr); 
        if (validarEntero(entradaStr, valor)) {
            return valor; 
        }
    }
}

Matriz* seleccionarMatriz(Matriz& m1, Matriz& m2, Matriz& m3, const std::string& prompt) {
    int eleccion;
    std::cout << prompt << std::endl;
    std::cout << "  1. Matriz m1" << std::endl;
    std::cout << "  2. Matriz m2" << std::endl;
    std::cout << "  3. Matriz m3" << std::endl;
    eleccion = obtenerEntero("Seleccione una matriz: ");

    switch (eleccion) {
        case 1: return &m1;
        case 2: return &m2;
        case 3: return &m3;
        default:
            std::cout << "Seleccion invalida. " << std::endl;
            return &m1; 
    }
}

int main() {
    Matriz m1, m2, m3; 
    Matriz m_result; 

    int opcion;
    do {
        std::cout << "\n--- MENU DE OPERACIONES CON MATRICES ---" << std::endl;
        std::cout << "1. Crear Matriz " << std::endl;
        std::cout << "2. Llenar Matriz " << std::endl;
        std::cout << "3. Mostrar Matriz" << std::endl;
        std::cout << "4. Calcular Transpuesta" << std::endl;
        std::cout << "5. Calcular Determinante" << std::endl;
        std::cout << "6. Sumar Matrices" << std::endl;
        std::cout << "7. Multiplicar Matrices" << std::endl;
        std::cout << "8. Comparar Matrices" << std::endl;
        std::cout << "0. Salir" << std::endl;
        std::cout << "Ingrese su opcion: ";

        opcion = obtenerEntero(""); 

        switch (opcion) {
            case 1: { 
                int filas = obtenerEntero("Ingrese el numero de filas: ");
                int columnas = obtenerEntero("Ingrese el numero de columnas: ");
                Matriz* selectedMatriz = seleccionarMatriz(m1, m2, m3, "Seleccione donde crear la matriz:");
                try {
                    *selectedMatriz = crearMatriz(filas, columnas);
                    std::cout << "Matriz creada exitosamente." << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error al crear matriz: " << e.what() << std::endl;
                }
                break;
            }
            case 2: { 
                Matriz* selectedMatriz = seleccionarMatriz(m1, m2, m3, "Seleccione la matriz a llenar:");
                selectedMatriz->llenarMatriz(); 
                break;
            }
            case 3: { 
                int eleccion;
                std::cout << "Seleccione la matriz a mostrar:" << std::endl;
                std::cout << "  1. Matriz m1" << std::endl;
                std::cout << "  2. Matriz m2" << std::endl;
                std::cout << "  3. Matriz m3" << std::endl;
                std::cout << "  4. Matriz Resultado" << std::endl;
                eleccion = obtenerEntero("Opcion (1-4): ");
                
                switch (eleccion) {
                    case 1: m1.mostrarMatriz(); break;
                    case 2: m2.mostrarMatriz(); break;
                    case 3: m3.mostrarMatriz(); break;
                    case 4: m_result.mostrarMatriz(); break;
                    default: std::cout << "Seleccion invalida." << std::endl; break;
                }
                break;
            }
            case 4: { 
                Matriz* selectedMatriz = seleccionarMatriz(m1, m2, m3, "Seleccione la matriz para calcular la transpuesta:");
                try {
                    m_result = selectedMatriz->transpuesta();
                    std::cout << "Transpuesta calculada y guardada en Matriz Resultado." << std::endl;
                    m_result.mostrarMatriz();
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error al calcular transpuesta: " << e.what() << std::endl;
                }
                break;
            }
            case 5: { 
                Matriz* selectedMatriz = seleccionarMatriz(m1, m2, m3, "Seleccione la matriz para calcular el determinante:");
                try {
                    double det = selectedMatriz->determinante();
                    std::cout << "Determinante de la matriz: " << det << std::endl;
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error al calcular determinante: " << e.what() << std::endl;
                }
                break;
            }
            case 6: { 
                std::cout << "--- SUMA DE MATRICES ---" << std::endl;
                Matriz* matA = seleccionarMatriz(m1, m2, m3, "Seleccione la primera matriz (operando A):");
                Matriz* matB = seleccionarMatriz(m1, m2, m3, "Seleccione la segunda matriz (operando B):");
                try {
                    m_result = matA->suma(*matB);
                    std::cout << "Suma de matrices calculada y guardada en Matriz Resultado." << std::endl;
                    m_result.mostrarMatriz();
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error al sumar matrices: " << e.what() << std::endl;
                }
                break;
            }
            case 7: { 
                std::cout << "--- MULTIPLICACION DE MATRICES ---" << std::endl;
                Matriz* matA = seleccionarMatriz(m1, m2, m3, "Seleccione la primera matriz (operando A):");
                Matriz* matB = seleccionarMatriz(m1, m2, m3, "Seleccione la segunda matriz (operando B):");
                try {
                    m_result = matA->multiplicacion(*matB);
                    std::cout << "Multiplicacion de matrices calculada" << std::endl;
                    m_result.mostrarMatriz();
                } catch (const std::runtime_error& e) {
                    std::cerr << "Error al multiplicar matrices: " << e.what() << std::endl;
                }
                break;
            }
            case 8: { 
                std::cout << "--- COMPARACION DE MATRICES ---" << std::endl;
                Matriz* matA = seleccionarMatriz(m1, m2, m3, "Seleccione la primera matriz:");
                Matriz* matB = seleccionarMatriz(m1, m2, m3, "Seleccione la segunda matriz:");
                if (matA->esIgual(*matB)) {
                    std::cout << "Las matrices son iguales." << std::endl;
                } else {
                    std::cout << "Las matrices no son iguales." << std::endl;
                }
                break;
            }
            case 0: {
                std::cout << "Saliendo del programa." << std::endl;
                break;
            }
            default: {
                std::cout << "Opcion no valida." << std::endl;
                break;
            }
        }
    } while (opcion != 0); 

    return 0;  }
