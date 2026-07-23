package patrones.bridge;
//clase que contiene las operaciones

public class calculadora {
    protected operaciones implementador;

    public calculadora(operaciones implementador) {
        this.implementador = implementador;
    }

    public void setImplementador(operaciones implementador) {
        this.implementador = implementador;
    }

    public double calcularSuma(double a, double b) { return implementador.suma(a, b); }
    public double calcularResta(double a, double b) { return implementador.resta(a, b); }
    public double calcularMultiplicacion(double a, double b) { return implementador.multiplicar(a, b); }
    public double calcularDivision(double a, double b) { return implementador.dividir(a, b); }

    public double calcularExponente(double a, double b) { return implementador.exponente(a, b); }
    public double calcularRaiz(double a) { return implementador.raiz(a); }
    public double calcularLog10(double base, double exp) { return implementador.log10(base, exp); }
    public double calcularLogNatural(double a) { return implementador.logNatural(a); }
    public double calcularResolvente(double a, double b, double c) { return implementador.resolvente(a, b, c); }
}