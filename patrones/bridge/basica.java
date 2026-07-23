package patrones.bridge;
//es un patron que permite dividir una clase grande en dos jerarquias difinidas e independientes: abastraccion e implementacion

public class basica implements operaciones {
    @Override
    public double suma(double a, double b) { return a + b; }

    @Override
    public double resta(double a, double b) { return a - b; }

    @Override
    public double multiplicar(double a, double b) { return a * b; }

    @Override
    public double dividir(double a, double b) { 
        if (b == 0) throw new ArithmeticException("No se puede dividir entre cero");
        return a / b; 
    }

    @Override public double exponente(double a, double b) { return 0; }
    @Override public double log10(double base, double exp) { return 0; }
    @Override public double logNatural(double a) { return 0; }
    @Override public double raiz(double a) { return 0; }
    @Override public double resolvente(double a, double b, double c) { return 0; }
}