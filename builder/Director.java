package builder;
//definir el orden y los pasos específicos en los que se debe construir un objeto.

public class Director {
    private ComputadoraBuilder builder;

    public Director(ComputadoraBuilder builder) {
        this.builder = builder;
    }

    public void cambiarBuilder(ComputadoraBuilder builder) {
        this.builder = builder;
    }

    // Define la receta para una computadora básica/simple
    public void construirPcBasica() {
        builder.reset();
        builder.buildProcesador();
        builder.buildRAM();
        // No le agrega tarjeta de video dedicada ni almacenamiento extra
    }

    // Define la receta para una computadora de alto rendimiento
    public void construirPcCompleta() {
        builder.reset();
        builder.buildProcesador();
        builder.buildTarjetaGrafica();
        builder.buildRAM();
        builder.buildAlmacenamiento();
    }
}
