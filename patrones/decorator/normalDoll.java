package patrones.decorator;
public class normalDoll implements doll{
    private doll core;

    public normalDoll(doll core){
        this.core = core;
    }
    @Override
    public String speak() {
        return core.speak();
    }

    @Override
    public String scare() {
        return core.scare();
    }
}
