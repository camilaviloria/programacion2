package examen_pilares;

import java.sql.Date;

public class Memorandum extends Actividades implements Nota {
    private String emisor;
    private String receptor;

    public Memorandum(String prioridad, String descripcion, Date fecha, Date fecha_creacion) {
        super(prioridad, descripcion, fecha_creacion);
        this.emisor = emisor;
        this.receptor = receptor;
    }

    public String getEmisor() { return emisor; }
    public String getReceptor() { return receptor; }

    @Override
    public String ImprimirInformacion(String Informacion) {
        return "[MEMORANDUM] Prioridad: " + getprioridad() +
               "\n -> Descripcion: " + getdescripcion() +
               "\n -> Creado el: " + getfecha_creacion() + " | Fecha Actividad: "  +
               "\n -> De: " + emisor + " | Para: " + receptor + 
               "\n -> Estado: " + Informacion +
               "\n---------------------------------------------------------";
    }

    @Override
    public String ImprimirInformacion() {
        throw new UnsupportedOperationException("Unimplemented method 'ImprimirInformacion'");
    }  } 
     