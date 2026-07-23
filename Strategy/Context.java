package Strategy;
//Mantiene la referencia a un objeto Strategy y le delega el trabajo 
// mediante strategy.execute(data), tal como indica la nota del diagrama.
public class Context {
    private Strategy strategy;

    // Permite cambiar la estrategia dinámicamente
    public void setStrategy(Strategy strategy) {
        this.strategy = strategy;
    }

    // Ejecuta la estrategia seleccionada
    public void doSomething(double monto) {
        if (strategy == null) {
            System.out.println("Error: Por favor selecciona un método de pago.");
            return;
        }
        // Lógica del diagrama: strategy.execute()
        this.strategy.execute(monto);
    }
}
