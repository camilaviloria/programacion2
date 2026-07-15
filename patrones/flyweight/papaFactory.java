package patrones.flyweight;
//Es una clase encargada de crear y gestionar los objetos compartidos.
import java.util.HashMap;
import java.util.Map;

public class papaFactory {
    private static Map<String,papaTypes> map = new HashMap<>();
    public static papaTypes getPapaType(String color, String kind, String texture){
        papaTypes result = map.get(kind);
        if(result == null){

            result = new papaTypes(color, kind, texture);
            map.put(kind, result);
        }
        return result;
    }
    public static int getSize(){
        return map.size();
    }
    public static void changeTexture(String kind, String texture){
       papaTypes result = map.get(kind);
        if(result != null){
            result.setTexture(texture);
            map.replace(kind, result);
        }
       
    }
}
