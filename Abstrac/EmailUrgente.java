package Abstrac;

// Producto Concreto A1
class EmailUrgente implements Email {
    public void enviarEmail(String contenido) {
        System.out.println("[ALERTA] Email Urgente: " + contenido + " ¡Atención inmediata!");
    }
}

// Producto Concreto B1
class SMSUrgente implements SMS {
    public void enviarSMS(String contenido) {
        System.out.println("[SMS prioritario] " + contenido);
    }
}