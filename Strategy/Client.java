package Strategy;
//Ensambla el contexto y cambia de estrategia sobre la marcha, 
// siguiendo el mismo flujo de las notas del diagrama UML.
public class Client {
    public static void main(String[] args) {
        Context carrito = new Context();
        double totalCompra = 150.0;

        // 1. Pagar con Tarjeta de Crédito
        // str = new SomeStrategy(); context.setStrategy(str); context.doSomething()
        Strategy str = new TarjetaCreditoStrategy("4500-1234-5678-9012");
        carrito.setStrategy(str);
        carrito.doSomething(totalCompra);

        System.out.println("----------------------------------");

        // 2. Cambiar de estrategia en tiempo de ejecución a PayPal
        // other = new OtherStrategy(); context.setStrategy(other); context.doSomething()
        Strategy other = new PaypalStrategy("usuario@email.com");
        carrito.setStrategy(other);
        carrito.doSomething(totalCompra);
    }

}
