package builder;

public class GamerComputadoraBuilder implements ComputadoraBuilder {
    private Computadora pc;

    public GamerComputadoraBuilder() { this.reset(); }

    public void reset() { this.pc = new Computadora(); }
    public void buildProcesador() { pc.setProcesador("Intel i9 de última generación"); }
    public void buildTarjetaGrafica() { pc.setTarjetaGrafica("Nvidia RTX 4090"); }
    public void buildRAM() { pc.setRam(64); }
    public void buildAlmacenamiento() { pc.setAlmacenamiento(2000); }

    public Computadora getResult() {
        Computadora productoTerminado = this.pc;
        this.reset(); // Listo para la siguiente
        return productoTerminado;
    }
}
