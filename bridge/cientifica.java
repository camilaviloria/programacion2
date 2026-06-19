package bridge;

public class cientifica implements operaciones {
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

    @Override
    public double exponente(double a, double b) { return Math.pow(a, b); }

    @Override
    public double log10(double base, double exp) { return Math.log10(base); } // Nota: Ajustar según tu requerimiento de base

    @Override
    public double logNatural(double a) { return Math.log(a); }

    @Override
    public double raiz(double a) { return Math.sqrt(a); }

    @Override
    public double resolvente(double a, double b, double c) {
        // Retorna una de las raíces (la positiva, por ejemplo) como demostración
        double discriminante = (b * b) - (4 * a * c);
        if (discriminante < 0) return 0; // Raíz imaginaria
        return (-b + Math.sqrt(discriminante)) / (2 * a);
    }
}