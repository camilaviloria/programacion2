package patrones.decorator;

public class main {
    public static void main(String[] args) {
        // 1. Creamos la muñeca base (la fea)
        doll miMuneca = new uglyDoll("Anabelle");
        
        System.out.println("--- MUÑECA BASE ---");
        System.out.println("Hablar: " + miMuneca.speak());
        System.out.println("Asustar: " + miMuneca.scare());

        // 2. La decoramos para que ahora sea una muñeca normal que envuelve a la fea
        doll munecaDecorada = new normalDoll(miMuneca);

        System.out.println("\n--- MUÑECA DECORADA ---");
        System.out.println("Hablar (del decorador): " + munecaDecorada.speak());
        System.out.println("Asustar (del decorador): " + munecaDecorada.scare());
    }
}