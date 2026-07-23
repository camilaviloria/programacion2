package examenPatrones;

public class PuntoEspecifico {
    private final float x;
    private final float y;
    private Configuracion configuracion;

    public PuntoEspecifico(float x, float y, Configuracion configuracion) {
        this.x = x;
        this.y = y;
        this.configuracion = configuracion;
    }

    public void setConfiguracion(Configuracion configuracion) {
        this.configuracion = configuracion;
    }

    public void mostrarInformacion() {
        System.out.println("Punto (" + x + ", " + y + ") -> " + configuracion);
    }
}
