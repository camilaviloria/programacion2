package factory.factory;

public abstract class Factory {

    // Este es el "Factory Method" (el "createProduct()" del diagrama)
    public abstract Notificaciones crearNotificacion();

    // Este es el "someOperation()" del diagrama. 
    // Utiliza el método fábrica para obtener el producto sin saber qué tipo real es.
    public void enviarNotificacion(String mensaje) {
        Notificaciones notificacion = crearNotificacion();
        notificacion.enviar(mensaje);
    }
}