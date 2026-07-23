package patrones.decorator;
// son las clases que heredan de base decorator y añaden los comportamientos extras antes o despues de llamar al objeto envuelto
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
