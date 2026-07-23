package mediator;

public class Client {

    public static void main(String[] args) {
        // 1. Crear los componentes
        CheckboxTerminos checkbox = new CheckboxTerminos();
        BotonSubmit boton = new BotonSubmit();

        // 2. Crear el mediador (se conecta internamente)
        new FormularioMediator(checkbox, boton);

        // 3. Simular interacciones del usuario
        System.out.println("--- Intento de enviar formulario sin aceptar términos ---");
        boton.click();

        System.out.println("\n--- Usuario hace click en el Checkbox ---");
        checkbox.click();

        System.out.println("\n--- Intento de enviar formulario nuevamente ---");
        boton.click();
    }
}