package Singleton;
//Imagina que en tu aplicación necesitas guardar los datos del usuario que acaba de iniciar sesión 
// (su nombre, su rol, etc.) para que cualquier pantalla pueda ver quién está conectado.
public class SesionUsuario {// 1. Guardamos la única instancia en una variable estática y privada
    private static SesionUsuario instancia;

    // Atributos del objeto de ejemplo
    private String usuarioLogueado;
    private String rol;

    // 2. El constructor es estrictamente PRIVADO
    private SesionUsuario() {
        // Inicializamos valores por defecto
        this.usuarioLogueado = "Invitado";
        this.rol = "Ninguno";
    }

    // 3. Método público global para obtener la instancia única
    public static SesionUsuario getInstance() {
        if (instancia == null) { // Si no se ha creado, la creamos
            instancia = new SesionUsuario();
            System.out.println("-> [SesionUsuario] Creando sesión única en memoria por primera vez...");
        }
        return instancia; // Retornamos la instancia existente
    }

    // Métodos normales para interactuar con el objeto
    public void login(String usuario, String rol) {
        this.usuarioLogueado = usuario;
        this.rol = rol;
    }

    public void mostrarInfo() {
        System.out.println("Usuario activo: " + usuarioLogueado + " | Rol: " + rol);
    }
}