#include <iostream> // Para entrada/salida de consola
#include <fstream>  // Para manejo de archivos (ifstream)
#include <string>   // Para manipulación de cadenas de texto
#include <vector>   // Para almacenar líneas del archivo (opcional, pero útil)
#include <algorithm> // Para std::transform y std::tolower
#include <limits>    // Para std::numeric_limits para limpiar el buffer de entrada
#include <cctype>

// Códigos de escape ANSI para colores
const std::string ANSI_COLOR_GREEN = "\x1b[32m";
const std::string ANSI_COLOR_RESET = "\x1b[0m";

// Función para convertir una cadena a minúsculas
std::string aMinusculas(std::string texto){
    std::transform(texto.begin(), texto.end(), texto.begin(), ::tolower);
    return texto;
}

// Función principal para realizar la búsqueda y mostrar resultados
void procesarArchivo(const std::string& archivos) {
    std::ifstream file(archivos);

    // 6. Validaciones: Si el archivo no existe
    if (!file.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo '" << archivos << "'. Asegurese de que existe." << std::endl;
        return; // Termina la función si el archivo no existe
    }

    std::string search_term;
    std::string lower_search_term;
    bool valid_input = false;

    // 6. Validaciones: Si el usuario ingresa una palabra/carácter vacío
    
    int main() {
        std::string palabraBuscar;
        char opcion;

        do {
            std::cout << "ingrese la palabra o caracter que desee buscar: ";
            std::getline(std::cin, palabraBuscar); //getline para leer las lineas

            while (palabraBuscar.empty()) {
                std::cout <<" error la palabra o caracter no puede estar vacio, ingrese denuevo"
            }
        }
    }
