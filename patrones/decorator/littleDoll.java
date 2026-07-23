package patrones.decorator;
// clase que define el comportamiento que puede ser alterado por los decoradores
public class littleDoll implements doll {
    private String name;
    public littleDoll( String name){
        this.name = name;
    }
    @Override
    public String scare() {
        
        return "*mira fijamente*";
    }
    @Override
    public String speak() {
        return "...";
    }

}
