package factory.factory;
// busca proporciones de una interfaz para crear objetos en una subclase mientras permite a las clases alterar el tipo de objetos que se crearan
public class Email implements Notificaciones {
    @Override
    public void enviar(String mensaje) {
        System.out.println("Enviando Email con el mensaje: " + mensaje);
    }
}