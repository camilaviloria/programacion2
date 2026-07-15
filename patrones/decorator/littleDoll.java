package patrones.decorator;
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
