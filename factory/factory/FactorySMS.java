package factory.factory;

public class FactorySMS extends Factory {
    @Override
    public Notificaciones crearNotificacion() {
        return new SMS();
    }
}