package factory.factory;

public class SMS implements Notificaciones {
    @Override
    public void enviar(String mensaje) {
        System.out.println("Enviando SMS con el mensaje: " + mensaje);
    }
}