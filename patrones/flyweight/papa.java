package patrones.flyweight;
public class papa {
    private float weight;
    private float height;
    private String state;
    private papaTypes type;

    public papa(float weight, float height, String state, papaTypes type){
        this.type = type;
        this.height = height;
        this.weight = weight;
        this.state = state;
    }

    @Override
    public String toString(){
        return "height:"+ this.height+
        "\nweight:"+this.weight +
        "\nstate:" +this.state +
        "\ntexture:"+this.type.getTexture()+
        "\ntype:" + this.type;
    }

}
