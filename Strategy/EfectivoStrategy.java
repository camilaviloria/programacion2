package Strategy;
//Cada clase implementa un algoritmo de pago distinto.
// Estrategia Concreta 1: Pago con Tarjeta de Crédito
class TarjetaCreditoStrategy implements Strategy {
    private String numeroTarjeta;

    public TarjetaCreditoStrategy(String numeroTarjeta) {
        this.numeroTarjeta = numeroTarjeta;
    }

    @Override
    public void execute(double data) {
        System.out.println("Procesando pago de $" + data + " mediante Tarjeta de Crédito (" + numeroTarjeta + ").");
    }
}

// Estrategia Concreta 2: Pago con PayPal
class PaypalStrategy implements Strategy {
    private String email;

    public PaypalStrategy(String email) {
        this.email = email;
    }

    @Override
    public void execute(double data) {
        System.out.println("Procesando pago de $" + data + " enviado desde la cuenta PayPal: " + email);
    }
}

// Estrategia Concreta 3: Pago en Efectivo
public class EfectivoStrategy implements Strategy {
    @Override
    public void execute(double data) {
        System.out.println("Cobrando $" + data + " en efectivo en caja.");
    }
}