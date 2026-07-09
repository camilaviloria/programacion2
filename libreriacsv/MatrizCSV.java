package libreriacsv;

import java.util.ArrayList;
import java.util.List;

public class MatrizCSV {
    private List<List<String>> datos;

    public MatrizCSV() {
        this.datos = new ArrayList<>();
    }

    public List<List<String>> getDatos() { return datos; }

    public void agregarFila(List<String> fila) {
        datos.add(new ArrayList<>(fila));
    }

    public void eliminarFila(int indice) {
        if (indice >= 0 && indice < datos.size()) datos.remove(indice);
    }

    public void agregarColumna(List<String> columna) {
        for (int i = 0; i < datos.size(); i++) {
            if (i < columna.size()) {
                datos.get(i).add(columna.get(i));
            } else {
                datos.get(i).add(""); // Relleno vacío si la columna es más corta
            }
        }
    }

    public void eliminarColumna(int indice) {
        for (List<String> fila : datos) {
            if (indice >= 0 && indice < fila.size()) fila.remove(indice);
        }
    }
}