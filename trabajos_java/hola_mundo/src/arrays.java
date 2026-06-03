public class arrays {
    public static void main(String[] args) {

        int[] numbers = new int[3];
        System.out.println(numbers.length);
        String[] names = {"camila", "viloria", "camila"};
        System.out.println(names.length);

        //acceso
        System.out.println(names[1]);
        System.out.println(numbers[2]);

        System.out.println((new String[3])[0]);

        //modificacion
    }
}