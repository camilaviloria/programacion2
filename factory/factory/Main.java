package factory.factory;

public class Main {
    public static void main(String[] args) {
        // 1. Queremos enviar un Email usando su fábrica
        Factory fabricaEmail = new FactoryEmail();
        fabricaEmail.enviarNotificacion("¡Hola! Tu código de verificación ha sido generado.");

        // 2. Si mañana queremos cambiar a SMS, solo cambiamos la fábrica instanciada
        Factory fabricaSMS = new FactorySMS();
        fabricaSMS.enviarNotificacion("¡Hola! Tu código de verificación ha sido generado.");
    }
}