
public class StringExample {

    public static void main(String[] args) {
        String name = "camila";
        var apellido = new String("viloria");
        System.out.println(name + " " + apellido);

        System.out.println(name.length() - 1);

        System.out.println(name.charAt(1));

        // sub cadena
        System.out.println(name.substring(1,3));

        //mayusculas y minusculas 
        System.out.println(name.toUpperCase());
        System.out.println(name.toLowerCase());

        //comprobar si contiene algo
        System.out.println(apellido.contains("cam"));

        //comparar cadenas
        System.out.println(apellido.equals(name));
    }
}