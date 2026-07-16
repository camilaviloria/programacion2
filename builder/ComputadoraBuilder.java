package builder;

public interface ComputadoraBuilder {

    void reset();
    void buildProcesador();
    void buildTarjetaGrafica();
    void buildRAM();
    void buildAlmacenamiento();
    Computadora getResult();
}
