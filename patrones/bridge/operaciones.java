package patrones.bridge;

public interface operaciones {
    // Básicas
    double suma(double a, double b);
    double resta(double a, double b);
    double multiplicar(double a, double b);
    double dividir(double a, double b);

    // Científicas
    double exponente(double a, double b);
    double log10(double base, double exp);
    double logNatural(double a);
    double raiz(double a);
    double resolvente(double a, double b, double c); 
 }