import java.util.HashSet;

public class Set {
    public static void main(String[] args) {

        HashSet<String> names = new HashSet<>();
        var numbers = new HashSet<Integer>();

        //tamaño
        System.out.println(names.size());

        //agregar elementos
        names.add("camila"); //no se permite repetir los elementos
        names.add("viloria");
        names.add("camila");

        numbers.add(10);
        numbers.add(20);
        numbers.add(30);

        System.out.println(names);
        System.out.println(numbers);

        //acceso
        System.out.println(names.contains("camila"));

        //eliminar
        names.remove("camila");
        System.out.println(names);
        System.out.println(names.contains("camila"));

        //conjuntos
        name.addAll(numbers);
        System.out.println(name); //error por incompatibilidad
    }
}