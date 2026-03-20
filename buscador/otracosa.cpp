#include <iostream> 
#include <fstream>  
#include <string>   
#include <vector>   
#include <algorithm> 
#include <limits>    
#include <cctype>    

// colores
const std::string ANSI_COLOR_GREEN = "\x1b[32m";
const std::string ANSI_COLOR_RESET = "\x1b[0m";

// Función para convertir una cadena a minúsculas
std::string aMinusculas(std::string texto) {
    // Itera sobre cada caracter de la cadena
    for (size_t i = 0; i < texto.length(); ++i) {
        texto[i] = std::tolower(static_cast<unsigned char>(texto[i]));
    }
    return texto;
}

void procesarArchivo(const std::string& archivo) {
    std::ifstream archivo_entrada(archivo); 

    // 6. Validaciones: Si el archivo no existe
    if (!archivo_entrada.is_open()) {
        std::cout << "Error: No se pudo abrir el archivo '" << archivo << "'. Asegurese de que existe." << std::endl;
        return; 
    }
    std::string palabra_a_buscar;
    std::string palabra_a_buscar_minusculas; 
    bool entrada_valida = false; 

    // 6. Validaciones
    while (!entrada_valida) {
        std::cout << "\nIngrese la palabra o caracter a buscar: ";
        std::getline(std::cin, palabra_a_buscar); // lee la línea completa, incluyendo espacios
        
        if (palabra_a_buscar.empty()) {
            std::cout << "Error: La palabra o caracter a buscar no puede estar vacio. Por favor, intente de nuevo." << std::endl;
        } else {
            entrada_valida = true; 
            palabra_a_buscar_minusculas = aMinusculas(palabra_a_buscar); // Convertir para búsqueda insensible
        }
    }
    std::string linea_actual;
    int total_coincidencias = 0;
    int numero_linea = 0;

    std::cout << "\nResultados de la busqueda para \"" << palabra_a_buscar << "\":" << std::endl;
    std::cout << "--------------------------------------------------------" << std::endl;

    // 1. Lectura de archivos: Leer linea por linea
    while (std::getline(archivo_entrada, linea_actual)) { // Lee cada línea del archivo
        numero_linea++;
        std::string linea_minusculas = aMinusculas(linea_actual); // Convertir la línea actual a minúsculas
        std::string linea_a_mostrar = linea_actual; // Copia de la línea original para mostrar con resaltado

        size_t pos = 0;
        int coincidencias_en_linea = 0;

        // 2. Búsqueda insensible a mayúsculas/minúsculas y resaltado de coincidencias
        while ((pos = linea_minusculas.find(palabra_a_buscar_minusculas, pos)) != std::string::npos) {
            // Insertar el código de color verde antes de la coincidencia
            linea_a_mostrar.insert(pos, ANSI_COLOR_GREEN);
            linea_a_mostrar.insert(pos + palabra_a_buscar_minusculas.length() + ANSI_COLOR_GREEN.length(), ANSI_COLOR_RESET);
            // Ajustar la posición para la siguiente búsqueda
            pos += palabra_a_buscar_minusculas.length() + ANSI_COLOR_GREEN.length() + ANSI_COLOR_RESET.length();
            coincidencias_en_linea++;
        }

        // 4. Reporte de resultados: Mostrar cada línea con coincidencias
        std::cout << "Linea " << numero_linea << ": " << linea_a_mostrar << std::endl;
        total_coincidencias += coincidencias_en_linea; // Acumula el total de coincidencias
    }

    archivo_entrada.close(); 

    // Cantidad total de coincidencias al final
    std::cout << "--------------------------------------------------------" << std::endl;
    std::cout << "Total de coincidencias para \"" << palabra_a_buscar << "\": " << total_coincidencias << std::endl;
}

// Función principal del programa
int main() {
    std::string nombre_archivo_a_usar = "archivo.txt"; 
    char opcion_repetir;

    // 5. Interacción del usuario: Permitir repetir el proceso
    do {
        procesarArchivo(nombre_archivo_a_usar); 
        std::cout << "\n--------------------------------------------------------" << std::endl;
        std::cout << "¿Desea realizar una nueva busqueda? (S/N): ";
        std::cin >> opcion_repetir;
        opcion_repetir = std::toupper(opcion_repetir); // Convertir a mayúscula para comparar

        // Limpiar el resto de la línea del buffer de entrada después de leer el char
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    } while (opcion_repetir == 'S');

    std::cout << "Programa finalizado" << std::endl;

    return 0; 
    }