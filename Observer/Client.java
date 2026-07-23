package Observer;

public class Client {
    public static void main(String[] args) {
        // 1. Crear el Publicador
        Publisher canalNoticias = new Publisher();

        // 2. Crear los suscriptores
        Subscriber sub1 = new EmailSubscriber("camila@example.com");
        Subscriber sub2 = new AppSubscriber("User_123");

        // 3. Suscribir objetos (s = new ConcreteSubscriber(); publisher.subscribe(s))
        canalNoticias.subscribe(sub1);
        canalNoticias.subscribe(sub2);

        // 4. Producir un cambio de estado en el Publisher
        canalNoticias.mainBusinessLogic("¡Lanzaron la versión oficial de Java 25!");

        // 5. Desuscribir a uno y volver a publicar
        canalNoticias.unsubscribe(sub1);
        
        canalNoticias.mainBusinessLogic("Actualización de seguridad disponible.");
    }
}
