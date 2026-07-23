package mediator;
//Contiene las referencias a todos los componentes y coordina la lógica de 
// interacción (evalúa quién envió la notificación mediante el if (sender == component)).
public class FormularioMediator implements Mediator {
    private CheckboxTerminos checkbox;
    private BotonSubmit boton;

    // Registra los componentes con los que trabajará
    public FormularioMediator(CheckboxTerminos checkbox, BotonSubmit boton) {
        this.checkbox = checkbox;
        this.checkbox.setMediator(this);

        this.boton = boton;
        this.boton.setMediator(this);
    }

    @Override
    public void notify(Object sender, String event) {
        // Corresponde a la nota UML: if (sender == componentA) reactOnA()
        if (sender == checkbox && event.equals("check")) {
            if (checkbox.isSeleccionado()) {
                boton.setHabilitado(true);
            } else {
                boton.setHabilitado(false);
            }
        }
    }
}