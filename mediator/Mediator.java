package mediator;
//Define el método de notificación que llamarán los componentes cuando algo suceda.
public interface Mediator {
    void notify(Object sender, String event);

}
