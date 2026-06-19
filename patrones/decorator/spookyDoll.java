package patrones.decorator;
public class spookyDoll extends normalDoll {
      public spookyDoll(doll insideDoll){
        super(insideDoll);
    }
    @Override
    public String scare() {
        return super.scare() + "\n*dobla la cabeza*";
    }
    
    @Override
    public String speak() {
        return super.speak() + "\nme duele";
    }

}
