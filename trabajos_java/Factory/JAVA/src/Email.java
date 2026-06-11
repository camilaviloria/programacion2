package Factory;

public class Email implements Notificaciones {
    pivate String email;
    private String correo;
    private String contraseña;
    @Override
    public void enviarNotificacion() {
        System.out.println("Email enviado");
    }
}