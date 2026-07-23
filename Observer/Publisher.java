package Observer;
//Mantiene la lista de suscriptores y contiene la lógica para agregar, eliminar 
// y notificar a todos recorriendo la lista (foreach (s in subscribers) s.update(context)).
import java.util.ArrayList;
import java.util.List;

public class Publisher {
    private List<Subscriber> subscribers = new ArrayList<>();
    private String mainState; // El estado interno o la última noticia

    // Permite suscribir a un observador
    public void subscribe(Subscriber s) {
        subscribers.add(s);
    }

    // Permite desuscribir a un observador
    public void unsubscribe(Subscriber s) {
        subscribers.remove(s);
    }

    // Notifica a todos los suscriptores recorriendo la lista
    public void notifySubscribers() {
        for (Subscriber s : subscribers) {
            s.update(mainState);
        }
    }

    // Método del negocio: cambia el estado y notifica automáticamente
    public void mainBusinessLogic(String newNews) {
        this.mainState = newNews;
        System.out.println("\n[Publisher]: ¡Nueva noticia publicada!: " + newNews);
        notifySubscribers();
    }
}