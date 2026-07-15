package patrones.flyweight;
// se repiten y se comparten (no cambian)
public class papaTypes {
    private String color; 
    private String kind;
    private String texture;

    public papaTypes(String color, String kind, String texture){
        this.texture = texture;
        this.color = color;
        this.kind = kind;
    }

    public String getColor() {
        return color;
    }
    public String getKind() {
        return kind;
    }
    public String getTexture() {
        return texture;
    }
    public void setColor(String color) {
        this.color = color;
    }
    public void setKind(String kind) {
        this.kind = kind;
    }
    public void setTexture(String texture) {
        this.texture = texture;
    }

}
