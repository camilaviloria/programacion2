package Observer;
//define un mecanismo de suscripción para notificar a varios objetos sobre cualquier 
//evento que le suceda al objeto que están observando.
//Define el método update que ejecutará el Publisher para notificar a los observadores.
public interface Subscriber {
    void update(String context);
}
