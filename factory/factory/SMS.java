package factory.factory;
//productos concretos que implementan la interfaz

public class SMS implements Notificaciones {
    @Override
    public void enviar(String mensaje) {
        System.out.println("Enviando SMS con el mensaje: " + mensaje);
    }
}