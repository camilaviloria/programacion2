package ejecicioJava;

public class CamionetasCarga extends Vehiculos {
    private double cargoExtra;
    private double kilogramoCapacidad;

    public CamionetasCarga(double precioBase, String placa, String modelo, double cargoExtra, double kilogramoCapacidad) {
        super(precioBase, placa, modelo);
        this.cargoExtra = cargoExtra;
        this.kilogramoCapacidad = kilogramoCapacidad;
    }

    @Override
    public double calcularPrecio(int cantidadDias) {
        double costoDias = cantidadDias * this.precioBase;
        double recargoPeso = this.kilogramoCapacidad * this.cargoExtra;
        
        return costoDias + recargoPeso;
    }
}
