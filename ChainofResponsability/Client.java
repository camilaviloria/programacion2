package ChainofResponsability;

public class Client {
    public static void main(String[] args) {
        // 1. Crear los manejadores
        Handler h1 = new ConcreteHandlers();
        Handler h2 = new SoporteTecnicoHandler();
        Handler h3 = new GerenciaHandler();

        // 2. Armar la cadena: h1 -> h2 -> h3
        h1.setNext(h2);
        h2.setNext(h3);

        // 3. Probar distintas solicitudes a través de la cabeza de la cadena (h1)
        System.out.println("Solicitud 1:");
        h1.handle("Contraseña olvidada"); 
        // Lo resuelve SoporteBasicoHandler

        System.out.println("\nSolicitud 2:");
        h1.handle("Fallo en la red"); 
        // SoporteBasico lo pasa a SoporteTecnico y este lo resuelve

        System.out.println("\nSolicitud 3:");
        h1.handle("Compra de Servidor"); 
        // Pasa por SoporteBasico y SoporteTecnico hasta que Gerencia lo resuelve

        System.out.println("\nSolicitud 4:");
        h1.handle("Hackear el Pentágono"); 
        // Recorre toda la cadena sin que nadie pueda procesarlo
    }
}
