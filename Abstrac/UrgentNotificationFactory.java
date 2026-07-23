package Abstrac;
// Fábrica Concreta 1: Solo produce cosas de Marketing
public class UrgentNotificationFactory implements NotificationFactory {
    public Email crearEmail() {
        return new EmailUrgente();
    }
    public SMS crearSMS() {
        return new SMSUrgente();
    }
}

// Fábrica Concreta 2: Solo produce cosas de Marketing
class MarketingNotificationFactory implements NotificationFactory {
    public Email crearEmail() {
        return new EmailMarketing();
    }
    public SMS crearSMS() {
        return new SMSMarketing();
    }
}
