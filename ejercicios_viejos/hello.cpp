#include <iostream> // Para entrada/salida estándar (cin, cout)
#include <fstream>  // Para manejo de archivos (ifstream, ofstream)
#include <string>   // Para manejar cadenas de texto (std::string)
#include <limits>   // Para numeric_limits (para limpiar el buffer de entrada)
#include <cctype>   // Para isalpha (aunque no se usará directamente para validar nombre, sí para limpiarlo de espacios)

// Estructura para almacenar los datos de un estudiante
struct Estudiante {
    std::string nombre;
    int nota;
};

// --- Prototipos de funciones ---
void mostrarMenu();
void agregarNota(const std::string& nombreArchivo);
void verNotas(const std::string& nombreArchivo);
void calcularPromedio(const std::string& nombreArchivo);
void limpiarBuffer(); // Función auxiliar para limpiar el buffer de entrada

int main() {
    const std::string NOMBRE_ARCHIVO = "notas_estudiantes.txt";
    int opcion;

    do {
        mostrarMenu();
        std::cout << "Elija una opción: ";
        std::cin >> opcion;

        // Validar que la entrada sea un número
        while (std::cin.fail()) {
            std::cout << "Entrada inválida. Por favor, ingrese un número: ";
            limpiarBuffer();
            std::cin >> opcion;
        }
        limpiarBuffer(); // Limpiar el buffer después de leer el número

        switch (opcion) {
            case 1:
                agregarNota(NOMBRE_ARCHIVO);
                break;
            case 2:
                verNotas(NOMBRE_ARCHIVO);
                break;
            case 3:
                calcularPromedio(NOMBRE_ARCHIVO);
                break;
            case 4:
                std::cout << "Saliendo del programa. ¡Hasta luego!" << std::endl;
                break;
            default:
                std::cout << "Opción no válida. Por favor, intente de nuevo." << std::endl;
                break;
        }
        std::cout << std::endl; // Salto de línea para separar las opciones

    } while (opcion != 4);

    return 0;
}

// --- Implementación de funciones ---

void mostrarMenu() {
    std::cout << "=== Registro de Notas ===" << std::endl;
    std::cout << "1. Agregar nota de estudiante" << std::endl;
    std::cout << "2. Ver todas las notas" << std::endl;
    std::cout << "3. Calcular promedio" << std::endl;
    std::cout << "4. Salir" << std::endl;
}

void agregarNota(const std::string& nombreArchivo) {
    Estudiante nuevoEstudiante;
    std::ofstream archivoSalida; // Objeto para escribir en el archivo

    // Abrir el archivo en modo de añadir (append)
    // std::ios::app asegura que el contenido se añada al final sin sobrescribir
    archivoSalida.open(nombreArchivo, std::ios::app);

    // Manejo de errores al abrir el archivo
    if (!archivoSalida.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para escribir." << std::endl;
        return; // Salir de la función si hay un error
    }

    std::cout << "--- Agregar Nota de Estudiante ---" << std::endl;
    std::cout << "Ingrese el nombre del estudiante (máx. 30 caracteres): ";
    // Leer la línea completa para el nombre (maneja espacios)
    std::getline(std::cin, nuevoEstudiante.nombre);

    // Validar y truncar el nombre si excede 30 caracteres
    if (nuevoEstudiante.nombre.length() > 30) {
        nuevoEstudiante.nombre = nuevoEstudiante.nombre.substr(0, 30);
        std::cout << "Nombre truncado a 30 caracteres: " << nuevoEstudiante.nombre << std::endl;
    }

    // Validación de la nota
    do {
        std::cout << "Ingrese la nota del estudiante (1-20): ";
        std::cin >> nuevoEstudiante.nota;

        while (std::cin.fail()) {
            std::cout << "Entrada inválida. Por favor, ingrese un número entero para la nota: ";
            limpiarBuffer();
            std::cin >> nuevoEstudiante.nota;
        }
        limpiarBuffer(); // Limpiar el buffer después de leer la nota

        if (nuevoEstudiante.nota < 1 || nuevoEstudiante.nota > 20) {
            std::cout << "Nota inválida. La nota debe estar entre 1 y 20." << std::endl;
        }
    } while (nuevoEstudiante.nota < 1 || nuevoEstudiante.nota > 20);

    // Escribir los datos en el archivo con el formato "nombre,nota"
    archivoSalida << nuevoEstudiante.nombre << "," << nuevoEstudiante.nota << std::endl;

    archivoSalida.close(); // Cerrar el archivo
    std::cout << "Nota de " << nuevoEstudiante.nombre << " guardada exitosamente." << std::endl;
}

void verNotas(const std::string& nombreArchivo) {
    std::ifstream archivoEntrada; // Objeto para leer del archivo
    std::string linea;
    int contador = 0;

    archivoEntrada.open(nombreArchivo); // Abrir el archivo en modo de lectura

    // Manejo de errores al abrir el archivo
    if (!archivoEntrada.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para leer. Puede que no exista o esté vacío." << std::endl;
        return;
    }

    std::cout << "--- Listado de Notas ---" << std::endl;
    std::cout << "Nombre\t\t\tNota" << std::endl; // Encabezado para la tabla
    std::cout << "------------------------------------" << std::endl;

    // Leer el archivo línea por línea
    while (std::getline(archivoEntrada, linea)) {
        // Encontrar la posición de la coma para separar nombre y nota
        size_t posComa = linea.find(',');

        if (posComa != std::string::npos) { // Si se encuentra la coma
            std::string nombre = linea.substr(0, posComa);
            std::string notaStr = linea.substr(posComa + 1);

            // Asegurar que el nombre se imprima con un ancho fijo para alineación
            std::cout.width(30); // Ancho de 30 caracteres para el nombre
            std::cout << std::left << nombre << "\t" << notaStr << std::endl;
            contador++;
        }
    }

    if (contador == 0) {
        std::cout << "No hay notas registradas en el archivo." << std::endl;
    }

    archivoEntrada.close(); // Cerrar el archivo
}

void calcularPromedio(const std::string& nombreArchivo) {
    std::ifstream archivoEntrada;
    std::string linea;
    int sumaNotas = 0;
    int numNotas = 0;

    archivoEntrada.open(nombreArchivo);

    if (!archivoEntrada.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo para leer. Puede que no exista o esté vacío." << std::endl;
        return;
    }

    // Leer el archivo línea por línea para calcular el promedio
    while (std::getline(archivoEntrada, linea)) {
        size_t posComa = linea.find(',');
        if (posComa != std::string::npos) {
            std::string notaStr = linea.substr(posComa + 1);
            try {
                int nota = std::stoi(notaStr); // Convertir la cadena de nota a entero
                // Validar la nota antes de sumarla al promedio
                if (nota >= 1 && nota <= 20) {
                    sumaNotas += nota;
                    numNotas++;
                } else {
                    std::cerr << "Advertencia: Nota inválida (" << nota << ") encontrada en el archivo y omitida del promedio." << std::endl;
                }
            } catch (const std::invalid_argument& e) {
                std::cerr << "Advertencia: Dato de nota no numérico en el archivo ('" << notaStr << "') y omitido." << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Advertencia: Nota fuera de rango en el archivo ('" << notaStr << "') y omitida." << std::endl;
            }
        }
    }

    archivoEntrada.close();

    std::cout << "--- Cálculo de Promedio ---" << std::endl;
    if (numNotas > 0) {
        double promedio = static_cast<double>(sumaNotas) / numNotas;
        std::cout << "Total de notas procesadas: " << numNotas << std::endl;
        std::cout << "Suma de notas: " << sumaNotas << std::endl;
        std::cout << "El promedio de las notas es: " << promedio << std::endl;
    } else {
        std::cout << "No hay notas válidas para calcular el promedio." << std::endl;
    }
}

// Función auxiliar para limpiar el buffer de entrada
void limpiarBuffer() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}