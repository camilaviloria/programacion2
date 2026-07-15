package trabajos_java.POO;

public class EmpleadoContrato extends Empleado {
    private final double tarifaHora;
    private final int horasTrabajadas;

    public EmpleadoContrato(String id, String nombre, double tarifaHora, int horasTrabajadas) {
        super(id, nombre);
        this.tarifaHora = tarifaHora;
        this.horasTrabajadas = horasTrabajadas;
    }

    @Override
    public double calcularSalarioMensual() {
        return this.tarifaHora * this.horasTrabajadas; // Lógica particular de cálculo
    }
}
