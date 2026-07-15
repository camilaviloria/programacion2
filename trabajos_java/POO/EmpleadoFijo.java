package trabajos_java.POO;

public class EmpleadoFijo extends Empleado {
    private final double salarioBase; // 'final' asegura que no se modifique tras asignarse en el constructor

    public EmpleadoFijo(String id, String nombre, double salarioBase) {
        super(id, nombre); // Llama al constructor del padre
        this.salarioBase = salarioBase;
    }

    @Override
    public double calcularSalarioMensual() {
        return this.salarioBase; // El salario mensual es directamente su sueldo fijo
    }
}