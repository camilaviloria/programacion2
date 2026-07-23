package mediator;

// Componente B: Botón de Registrarse
public class BotonSubmit extends BaseComponent {
    private boolean habilitado = false;

    public void setHabilitado(boolean habilitado) {
        this.habilitado = habilitado;
        System.out.println("[BotonSubmit]: Estado habilitado = " + habilitado);
    }

    public void click() {
        if (habilitado) {
            System.out.println("[BotonSubmit]: ¡Formulario enviado con éxito!");
        } else {
            System.out.println("[BotonSubmit]: No se puede hacer click, está deshabilitado.");
        }
    }
}