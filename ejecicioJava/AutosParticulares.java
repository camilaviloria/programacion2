package ejecicioJava;

public class AutosParticulares extends Vehiculos {
    private double descuentoFijo;

    public AutosParticulares(double precioBase, String placa, String modelo, double descuentoFijo) {
            super(precioBase, placa, modelo);
            this.descuentoFijo = descuentoFijo;
    }

    @Override
    public double calcularPrecio(int cantidadDias) {
        // Ahora puedes usar precioBase directamente porque el padre lo permite
        double precioTotal = cantidadDias * this.precioBase;
        
        if (cantidadDias > 7) {
            precioTotal = precioTotal - this.descuentoFijo;
        }
        return precioTotal;
    }
}