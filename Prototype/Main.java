package Prototype;

public class Main {
    public static void main(String[] args) {
        // 1. Creamos nuestro Prototipo Maestro de manera pesada una sola vez
        Enemigo zombiePrototipo = new Enemigo("Zombie Caminante", 100, "Mordisco");
        System.out.println("Prototipo original: " + zombiePrototipo);
        
        System.out.println("\n--- Generando horda de clones ---");

        // 2. En lugar de usar 'new' y pasarle todos los parámetros de nuevo, clonamos
        Enemigo zombieClon1 = (Enemigo) zombiePrototipo.duplicar();
        Enemigo zombieClon2 = (Enemigo) zombiePrototipo.duplicar();

        // 3. Podemos modificar cada clon de forma independiente sin afectar al prototipo original
        zombieClon2.setVida(50); // Este clon ya viene herido

        System.out.println("Clon 1: " + zombieClon1);
        System.out.println("Clon 2 (Herido): " + zombieClon2);
        
        System.out.println("\nVerificamos que el original sigue intacto:");
        System.out.println("Original: " + zombiePrototipo);
    }
}
