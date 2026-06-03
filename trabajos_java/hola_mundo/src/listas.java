import java.util.ArrayList;
public class listas {
    public static void main(String[] args) {
        //listas
        var names = new ArrayList<String>();
        var numbers = new ArrayList<Integer>();

        // añadir elementos
        names.add("camila");
        names.add("viloria");
        names.add("camila");

        numbers.add(10);
        numbers.add(20);
        numbers.add(30);

        System.out.println(names);
        System.out.println(numbers);

        //acceso a los elementos
        System.out.println(names.getFirst());
        System.out.println(names.getLast());
        System.out.println(names.get(1));
        System.out.println(numbers.get(2));

        //modificacion
        names.set(0, "camila viloria");
        System.out.println(names);

        //eliminar
        names.remove(0);
        System.out.println(names.get(0));

        //buscar elementos
        System.out.println(names.contains("camila"));

        //ordenar
        names.sort(null);
        System.out.println(names);


    }    
}
