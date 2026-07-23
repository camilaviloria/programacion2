package Observer;
//Implementan la interfaz Subscriber y definen qué hacen cuando reciben la notificación en update.
// Suscriptor Concreto 1: Notificación por Email
class EmailSubscriber implements Subscriber {
    private String email;

    public EmailSubscriber(String email) {
        this.email = email;
    }

    @Override
    public void update(String context) {
        System.out.println("-> Enviando correo a " + email + " con la noticia: " + context);
    }
}

// Suscriptor Concreto 2: Notificación Push en App Móvil
class AppSubscriber implements Subscriber {
    private String usuario;

    public AppSubscriber(String usuario) {
        this.usuario = usuario;
    }

    @Override
    public void update(String context) {
        System.out.println("-> [Push App] Alerta para " + usuario + ": " + context);
    }
}
