package factory;

public class Email implements Notificaciones {
    private String email;
    private String correo;
    private String contraseña;
    @Override
    public void enviarNotificacion() {
        System.out.println("Email enviado");
    }
}