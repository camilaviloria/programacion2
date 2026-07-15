package patrones.decorator;

public class uglyDoll implements doll {
    private String name;

    public uglyDoll(String name) {
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