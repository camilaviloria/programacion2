#include <iostream> // Para entrada/salida de consola
#include <fstream>  // Para manejo de archivos (ifstream)
#include <string>   // Para manipulación de cadenas de texto
#include <vector>   // Para almacenar líneas del archivo (opcional, pero útil)
#include <algorithm> // Para std::transform y std::tolower
#include <limits>    // Para std::numeric_limits para limpiar el buffer de entrada
#include <cctype>

// colores
const std::string ANSI_COLOR_GREEN = "\x1b[32m";
const std::string ANSI_COLOR_RESET = "\x1b[0m";

// Función para convertir una cadena a minúsculas
std::string aMinusculas(std::string texto) {
    for (size_t i = 0; i < texto.length(); ++i) {
        texto[i] = std::tolower(static_cast<unsigned char>(texto[i]));
    }
    return texto;
}

void procesarArchivo(const std::string& archivos) {
    std::ifstream archivo_entrada(archivos); 

    // 6. Validaciones: Si el archivo no existe
    if (!archivo_entrada.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo '" << archivos << "'. Asegurese de que existe." << std::endl;
        return; 
    }

    std::string palabra_a_buscar;
    std::string palabra_a_buscar_minusculas; 
    bool entrada_valida = false; 
    
    // 6. Validaciones: Si el usuario ingresa una palabra/carácter vacío
    while (!entrada_valida) {
        std::cout << "\nIngrese la palabra o caracter a buscar: ";
        std::getline(std::cin, palabra_a_buscar); // Leer la línea completa, incluyendo espacios
        
        if (palabra_a_buscar.empty()) {
            std::cout << "Error: La palabra o caracter a buscar no puede estar vacio. Por favor, intente de nuevo." << std::endl;
        } else {
            entrada_valida = true; // La entrada es válida, salir del bucle
            palabra_a_buscar_minusculas = aMinusculas(palabra_a_buscar); // Convertir para búsqueda insensible
        }
    }