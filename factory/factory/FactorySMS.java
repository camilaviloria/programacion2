package factory.factory;
//concretos creadores que deciden que producto instanciar 

public class FactorySMS extends Factory {
    @Override
    public Notificaciones crearNotificacion() {
        return new SMS();
    }
}