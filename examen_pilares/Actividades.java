package examen_pilares;

import java.sql.Date;

public abstract class Actividades {
    private String prioridad;
    private String descripcion;
    private Date fecha_creacion;


    protected Actividades(String prioridad, String descripcion, Date fecha_creacion) {
            this.prioridad = prioridad;
            this.descripcion = descripcion;
            this.fecha_creacion = fecha_creacion; 

     }
        public String getprioridad() { return prioridad; }
        public String getdescripcion() { return descripcion; }
        public Date getfecha_creacion() { return fecha_creacion; }

    
        public abstract String ImprimirInformacion();
    }

