package Singleton;

public class Main {
    public static void main(String[] args) {
    // Si intentas hacer esto, Java no te dejará compilar (Constructor privado):
    // SesionUsuario miSesion = new SesionUsuario();

    System.out.println("--- Iniciando Aplicación ---");

    // Obtenemos el gestor de sesión desde la "Pantalla de Login"
    SesionUsuario loginScreen = SesionUsuario.getInstance();
    loginScreen.login("Camila", "Administrador");
    System.out.print("Estado en login: ");
    loginScreen.mostrarInfo();

    System.out.println("\n--- Navegando a otra sección del sistema ---");

    // Obtenemos el gestor desde una "Pantalla de Ajustes" totalmente distinta
    SesionUsuario settingsScreen = SesionUsuario.getInstance();
    System.out.print("Estado en ajustes: ");
    settingsScreen.mostrarInfo();

    System.out.println("\n--- Verificación de Identidad ---");
    // Demostremos que ambas variables apuntan exactamente al mismo espacio en memoria
    if (loginScreen == settingsScreen) {
        System.out.println("¡Son exactamente el mismo objeto! " + loginScreen);
    } else {
        System.out.println("Son objetos diferentes (Esto no debería pasar con Singleton)");
    }
}

}
