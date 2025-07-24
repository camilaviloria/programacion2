#include "matriz.hpp"    
#include "MatrizLib.hpp" 
#include <iostream>
#include <limits> 

void limpiarBufferMain() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int obtenerOpcionMenu(const std::string& prompt) {
    int opcion;
    while (true) {
        std::cout << prompt;
        std::cin >> opcion;
        if (std::cin.fail()) {
            std::cout << "Entrada invalida." << std::endl;
            std::cin.clear();
            limpiarBufferMain();
        } else {
            limpiarBufferMain();
            return opcion;
        }
    }
}

int main() {
    std::cout << "===== Demostracion Simple de la Libreria de Matrices =====" << std::endl;

    Matriz m1; 
    Matriz m2(0, 0); 
    Matriz m3(0, 0); 
    Matriz m4(0, 0); 
    Matriz m5(0, 0); 

    try {
        std::cout << "\n--- Creando matrices ---" << std::endl;
        m1 = MatrizLib::crearMatriz(2, 2); 
        m2 = MatrizLib::crearMatriz(2, 2); 
        m3 = MatrizLib::crearMatriz(2, 3); 
        m4 = MatrizLib::crearMatriz(3, 2); 
        m5 = MatrizLib::crearMatriz(3, 3); 

        std::cout << "Matrices creadas y inicializadas a 0." << std::endl;
        m1.mostrarMatriz();
        m2.mostrarMatriz();
        m3.mostrarMatriz();
        m4.mostrarMatriz();
        m5.mostrarMatriz();

    } catch (const std::runtime_error& e) {
        std::cerr << "Error al crear matrices: " << e.what() << std::endl;
        return 1; 
    }

    try {
        std::cout << "\n--- Llenando m1 (2x2) ---" << std::endl;
        m1.llenarMatriz();
        m1.mostrarMatriz();

        std::cout << "\n--- Llenando m2 (2x2) ---" << std::endl;
        m2.llenarMatriz();
        m2.mostrarMatriz();

        std::cout << "\n--- Llenando m5 (3x3) ---" << std::endl;
        m5.llenarMatriz();
        m5.mostrarMatriz();

    } catch (const std::runtime_error& e) {
        std::cerr << "Error al llenar matrices: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n--- Transpuesta de m1 ---" << std::endl;
        Matriz m1_t = m1.transpuesta();
        m1_t.mostrarMatriz();
    } catch (const std::runtime_error& e) {
        std::cerr << "Error en transpuesta: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n--- Determinante de m5 ---" << std::endl;
        double det_m5 = m5.determinante();
        std::cout << "Determinante de m5: " << det_m5 << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Error en determinante: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n--- Suma de m1 + m2 ---" << std::endl;
        Matriz suma_res = m1.suma(m2);
        suma_res.mostrarMatriz();
    } catch (const std::runtime_error& e) {
        std::cerr << "Error en suma: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n--- Intentando sumar m1 (2x2) y m3 (2x3) (ERROR ESPERADO) ---" << std::endl;
        Matriz suma_invalida = m1.suma(m3); 
        suma_invalida.mostrarMatriz();
    } catch (const std::runtime_error& e) {
        std::cerr << "Error esperado: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n--- Multiplicacion de m3 (2x3) * m4 (3x2) ---" << std::endl;
        std::cout << "Llenando m3 (2x3) para multiplicacion:" << std::endl;
        m3.llenarMatriz();
        std::cout << "Llenando m4 (3x2) para multiplicacion:" << std::endl;
        m4.llenarMatriz();

        Matriz mult_res = m3.multiplicacion(m4);
        mult_res.mostrarMatriz();
    } catch (const std::runtime_error& e) {
        std::cerr << "Error en multiplicacion: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n--- Intentando multiplicar m1 (2x2) * m3 (2x3) (ERROR ESPERADO) ---" << std::endl;
        Matriz mult_invalida = m1.multiplicacion(m3); 
        mult_invalida.mostrarMatriz();
    } catch (const std::runtime_error& e) {
        std::cerr << "Error esperado: " << e.what() << std::endl;
    }

    try {
        std::cout << "\n--- Comparacion de m1 y m2 ---" << std::endl;
        if (m1.esIgual(m2)) {
            std::cout << "m1 y m2 son iguales." << std::endl;
        } else {
            std::cout << "m1 y m2 NO son iguales." << std::endl;
        }
        
        std::cout << "\n--- Comparacion de m1 y m1 (copia implicita) ---" << std::endl;
        Matriz m1_copy = m1; 
        if (m1.esIgual(m1_copy)) {
            std::cout << "m1 y su copia son iguales." << std::endl;
        } else {
            std::cout << "m1 y su copia NO son iguales." << std::endl;
        }

    } catch (const std::runtime_error& e) {
        std::cerr << "Error en comparacion: " << e.what() << std::endl;
    }

    std::cout << "\n===== Demostracion Simple Finalizada =====" << std::endl;
    return 0;
}
