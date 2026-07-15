package Abstrac;

public class Main {// El cliente trabaja con las interfaces abstractas
    private static void enviarAlertaDeSistema(NotificationFactory factory, String mensaje) {
        Email email = factory.crearEmail();
        SMS sms = factory.crearSMS();
        
        email.enviarEmail(mensaje);
        sms.enviarSMS(mensaje);
    }

    public static void main(String[] args) {
        // Escenario A: Ocurrió un fallo en el servidor (Familia Urgente)
        System.out.println("--- Configurando Sistema para Emergencias ---");
        NotificationFactory fabricaUrgente = new UrgentNotificationFactory();
        enviarAlertaDeSistema(fabricaUrgente, "El servidor de base de datos está caído.");

        System.out.println();

        // Escenario B: Campaña del día del padre (Familia Marketing)
        System.out.println("--- Configurando Sistema para Campañas ---");
        NotificationFactory fabricaMarketing = new MarketingNotificationFactory();
        enviarAlertaDeSistema(fabricaMarketing, "¡50% de descuento en toda la tienda!");
    }
}


