package factory.factory;

public class FactoryEmail extends Factory {
    @Override
    public Notificaciones crearNotificacion() {
        return new Email();
    }
}
