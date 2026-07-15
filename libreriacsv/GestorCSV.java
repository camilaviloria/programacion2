package libreriacsv;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Arrays;
import java.util.List;

public class GestorCSV implements LectorCSV, ImpresorCSV {

    @Override
    public MatrizCSV leer(String rutaArchivo) {
        MatrizCSV matriz = new MatrizCSV();
        
        // Uso de try-with-resources para garantizar el cierre seguro del archivo físico
        try (BufferedReader br = new BufferedReader(new FileReader(rutaArchivo))) {
            String linea;
            while ((linea = br.readLine()) != null) {
                // Separamos los valores por comas estándar
                String[] valores = linea.split(",");
                matriz.agregarFila(Arrays.asList(valores));
            }
        } catch (IOException e) {
            System.err.println("Error al leer el archivo CSV: " + e.getMessage());
        }
        
        return matriz;
    }

    @Override
    public void imprimir(MatrizCSV matriz) {
        if (matriz.getDatos().isEmpty()) {
            System.out.println("[Matriz vacía]");
            return;
        }
        // Recorremos la estructura interna e imprimimos formateado con barras horizontales
        for (List<String> fila : matriz.getDatos()) {
            System.out.println(String.join(" | ", fila));
        }
    }

    // MÉTODO HOOK (Template Method / Strategy): Recibe la abstracción, invierte dependencias
    public MatrizCSV ejecutarProcesamientoEspecial(MatrizCSV matriz, ProcesadorCSV algoritmoExterno) {
        return algoritmoExterno.procesar(matriz);
    }
}