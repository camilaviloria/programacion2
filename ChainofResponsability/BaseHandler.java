package ChainofResponsability;

public abstract class BaseHandler implements Handler {
    private Handler next;

    @Override
    public void setNext(Handler next) {
        this.next = next;
    }

    @Override
    public void handle(String request) {
        // Corresponde a la nota: if (next != null) next.handle(request)
        if (this.next != null) {
            this.next.handle(request);
        } else {
            System.out.println("Nadie pudo procesar la solicitud: " + request);
        }
    }
}