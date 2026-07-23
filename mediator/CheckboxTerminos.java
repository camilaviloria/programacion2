package mediator;

// Componente A: Checkbox de términos y condiciones
public class CheckboxTerminos extends BaseComponent {
    private boolean seleccionado = false;

    public void click() {
        this.seleccionado = !this.seleccionado;
        System.out.println("[Checkbox]: Selección cambió a -> " + seleccionado);
        // Notifica al mediador pasándose a sí mismo (this)
        if (mediator != null) {
            mediator.notify(this, "check");
        }
    }

    public boolean isSeleccionado() {
        return seleccionado;
    }
} 
