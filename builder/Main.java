package builder;

public class Main {
    public static void main(String[] args) {
        // 1. El cliente crea el Builder concreto (el constructor de PC Gamer)
        ComputadoraBuilder builder = new GamerComputadoraBuilder();

        // 2. El cliente crea al Director y le pasa el builder
        Director director = new Director(builder);

        // --- ESCENARIO A: Construir una computadora básica (receta del director) ---
        System.out.println("--- Armando Computadora Básica ---");
        director.construirPcBasica(); // El director ejecuta la receta simple
        
        // El cliente obtiene el resultado final directamente desde el builder
        Computadora pcBasica = builder.getResult(); 
        System.out.println(pcBasica);

        System.out.println();

        // --- ESCENARIO B: Construir una computadora completa/ Gamer (receta del director) ---
        System.out.println("--- Armando Computadora Gamer Completa ---");
        director.construirPcCompleta(); // El director ejecuta la receta compleja
        
        // El cliente extrae el producto final terminado
        Computadora pcGamer = builder.getResult();
        System.out.println(pcGamer);

        System.out.println();

        // --- ESCENARIO C: Construcción personalizada (El cliente asume el control sin Director) ---
        // El patrón Builder también permite saltarse al director si necesitas un diseño único.
        System.out.println("--- Armando Computadora Personalizada (Sin Director) ---");
        builder.reset();
        builder.buildProcesador();
        builder.buildAlmacenamiento();
        // Decidimos no ponerle tarjeta de video ni RAM extra en este paso
        
        Computadora pcPersonalizada = builder.getResult();
        System.out.println(pcPersonalizada);
    }
}
