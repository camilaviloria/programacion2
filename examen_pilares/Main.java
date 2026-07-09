package examen_pilares;

import java.sql.Date;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        List<Nota> listaActividades = new ArrayList<>();
        long ahora = System.currentTimeMillis();
        
        Date fecha_creacion = new Date(ahora);
        Date fecha_duracion = new Date(ahora + (1000L * 60 * 60 * 24 * 7)); // 7 días después

        listaActividades.add(new Memorandum("Media", "Notificar cambios en el plan de e-commerce", fecha_creacion, "D1 (Lead)", "Equipo"));
        listaActividades.add(new Memorandum("Alta", "Falla crítica en base de datos PostgreSQL de producción", fecha_creacion, "Sistemas", "Camila"));
        
        listaActividades.add(new Tarea("Baja", "Revisar lecturas opcionales sobre patrones de diseño", fecha_creacion, fecha_duracion));
        listaActividades.add(new Tarea("Alta", "Implementar script ETL en Python", fecha_creacion, fecha_duracion));

        Collections.sort(listaActividades, new Comparator<Nota>() {
            @Override
            public int compare(Nota n1, Nota n2) {
                String p1 = ((Actividades) n1).getprioridad();
                String p2 = ((Actividades) n2).getprioridad();
                return Integer.compare(mapearPrioridad(p1), mapearPrioridad(p2));
            }

            private int mapearPrioridad(String prioridad) {
                if (prioridad == null) return 4;
                switch (prioridad.trim().toLowerCase()) {
                    case "alta":  return 1;
                    case "media": return 2;
                    case "baja":  return 3;
                    default:      return 4;
                }
            }
        });

        System.out.println("=========================================================");
        System.out.println("      ACTIVIDADES DEL EXAMEN ORDENADAS POR PRIORIDAD      ");
        System.out.println("=========================================================\n");

        for (Nota actividad : listaActividades) {
            System.out.println(actividad.ImprimirInformacion(null));
        }
    }
}