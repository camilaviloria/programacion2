package libreriacsv;

import java.util.Arrays;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        // 1. Instanciamos el motor de la librería
        GestorCSV miLibreria = new GestorCSV();

        // NOTA: Para probar el lector real, necesitarías crear un archivo físico "datos.csv".
        // Para esta simulación rápida de prueba, llenaremos una matriz directo por código:
        MatrizCSV miMatriz = new MatrizCSV();
        miMatriz.agregarFila(Arrays.asList("juan", "computacion", "maracaibo"));
        miMatriz.agregarFila(Arrays.asList("camila", "ingenieria", "san francisco"));

        System.out.println("--- TABLA ORIGINAL ---");
        miLibreria.imprimir(miMatriz);

        // 2. Probamos la modificación de la estructura (Agregar / Eliminar)
        System.out.println("\n--- TABLA LUEGO DE AGREGAR COLUMNA ---");
        miMatriz.agregarColumna(Arrays.asList("Aprobado", "Aprobado"));
        miLibreria.imprimir(miMatriz);

        // 3. EXTENSIBILIDAD SOLID: Inyectamos un algoritmo externo al vuelo (Mayúsculas)
        // Creamos la estrategia sin tocar ninguna clase interna de la librería
        ProcesadorCSV convertidorMayusculas = new ProcesadorCSV() {
            @Override
            public MatrizCSV procesar(MatrizCSV matrizOriginal) {
                for (List<String> fila : matrizOriginal.getDatos()) {
                    for (int i = 0; i < fila.size(); i++) {
                        fila.set(i, fila.get(i).toUpperCase());
                    }
                }
                return matrizOriginal;
            }
        };

        // Pasamos la matriz y nuestra estrategia personalizada al gestor
        MatrizCSV matrizFinal = miLibreria.ejecutarProcesamientoEspecial(miMatriz, convertidorMayusculas);

        System.out.println("\n--- TABLA PROCESADA (EXTENSIÓN MAYÚSCULAS) ---");
        miLibreria.imprimir(matrizFinal);
    }
}