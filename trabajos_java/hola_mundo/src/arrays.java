public class arrays {
    public static void main(String[] args) {

        int[] numbers = new int[3];
        System.out.println(numbers.length);
        String[] names = {"camila", "viloria", "camila"};
        System.out.println(names);

        //acceso
        System.out.println(names[1]);
        System.out.println(numbers[2]);

        System.out.println((new String[3])[0]);

        //modificacion
        System.out.println(numbers[0]);
        numbers[0] = 10;
        System.out.println(numbers[0]);

        names[0] = null; // null es compatible con las cadenas de textos
        System.out.println(names[0]);

        

    }
}