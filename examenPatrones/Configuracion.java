package examenPatrones;

public class Configuracion {
    public static final String ENCENDIDO = "ENCENDIDO";
    public static final String PAUSA = "PAUSA";
    public static final String APAGADO = "APAGADO";

    private String estado; 
    private float radioDeAccion;
    private int repeticionesPorSegundo;
    private char tipo; 

    public Configuracion(float radioDeAccion, int repeticionesPorSegundo, char tipo) {
        this.radioDeAccion = radioDeAccion;
        this.repeticionesPorSegundo = repeticionesPorSegundo;
        this.tipo = tipo;
        actualizarEstado(radioDeAccion);
    }

    public void actualizarDesdeLider(int radioDominio, int repeticiones) {
        this.repeticionesPorSegundo = repeticiones;
        actualizarEstado(radioDominio);
    }

    private void actualizarEstado(float radio) {
        if (radio > 50) {
            this.estado = ENCENDIDO;
        } else if (radio > 0 && radio < 25) {
            this.estado = PAUSA;
        } else if (radio <= 0) {
            this.estado = APAGADO;
        }
    }

    public String getEstado() {
        return estado;
    }

    @Override
    public String toString() {
        return String.format("[Estado=%s | Radio=%.1f | Rep/s=%d | Tipo=%c]", 
                estado, radioDeAccion, repeticionesPorSegundo, tipo);
    }
}
