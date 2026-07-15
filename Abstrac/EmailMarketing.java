package Abstrac;

// Producto Concreto A2
class EmailMarketing implements Email {
    public void enviarEmail(String contenido) {
        System.out.println("[BOLETÍN] Email con diseño elegante: " + contenido + " *Dessuscribirse aquí*");
    }
}

// Producto Concreto B2
class SMSMarketing implements SMS {
    public void enviarSMS(String contenido) {
        System.out.println("[Promo SMS] " + contenido + " ¡Compra ya en: promo.com!");
    }
}