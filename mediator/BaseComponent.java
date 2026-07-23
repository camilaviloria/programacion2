package mediator;
//Clase de la que heredarán los componentes concretos para guardar la referencia al mediador.
public abstract class BaseComponent {
    protected Mediator mediator;

    public void setMediator(Mediator mediator) {
        this.mediator = mediator;
    }

}
