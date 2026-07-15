package patrones.bridge;

public class Main {
    public static void main(String[] args) {
        calculadora miCalculadora = new calculadora(new basica());
        
        System.out.println("--- MODO BÁSICO ---");
        System.out.println("Suma (5 + 3): " + miCalculadora.calcularSuma(5, 3));
        System.out.println("Intento de Raíz en modo básico: " + miCalculadora.calcularRaiz(16)); 

        miCalculadora.setImplementador(new cientifica());

        System.out.println("\n--- MODO CIENTÍFICO ---");
        System.out.println("Suma (5 + 3): " + miCalculadora.calcularSuma(5, 3));
        System.out.println("Raíz Cuadrada de 16: " + miCalculadora.calcularRaiz(16)); 
    }
}