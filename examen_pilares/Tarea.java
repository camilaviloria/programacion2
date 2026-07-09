package examen_pilares;

import java.sql.Date;

public class Tarea extends Memorandum {
    private Date fecha_duracion;

    public Tarea(String prioridad, String descripcion, Date fecha, Date fecha_creacion, Date fecha_duracion) {
        super(prioridad, descripcion, fecha, fecha_creacion);
        this.fecha_duracion = fecha_duracion;
    }

    public Date getFechaDuracion() { return fecha_duracion; }

    @Override
    public String ImprimirInformacion() {
        return "[TAREA] Prioridad: " + getprioridad() +
               "\n -> Descripcion: " + getdescripcion() +
               "\n -> Creado el: " + getfecha_creacion() +
               "\n -> Duracion Estimada Hasta: " + fecha_duracion +
               "\n---------------------------------------------------------";
    }
}