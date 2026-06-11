package basic.c06_loops;

public class Loops {

    public static void main(String[] args) {
        for (int index = 0; index < 5; index++) {
            System.out.println(index);
        }

        for (int index = 0; index < 5; index++) {
            System.out.println("Hola, Java!");
        }

        String[] names = {"Brais", "Moure", "mouredev"};

        for (int index = 0; index < names.length; index++) {
            System.out.println(names[index]);
        }
    }
}
