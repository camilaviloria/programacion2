package factory.factory;
public class Email implements Notificaciones {
    @Override
    public void enviar(String mensaje) {
        System.out.println("Enviando Email con el mensaje: " + mensaje);
    }
}