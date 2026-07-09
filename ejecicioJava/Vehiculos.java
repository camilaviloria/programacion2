package ejecicioJava;

public abstract class Vehiculos {
    protected double precioBase;
    private String placa;
    private String modelo;

    protected Vehiculos(double precioBase, String placa, String modelo) {
        this.precioBase = precioBase;
        this.placa = placa;
        this.modelo = modelo; }
        public String getPlaca() { return placa; }
        public String getModelo() { return modelo; }
        public double getPrecioBase() { return precioBase; }
    
        public abstract double calcularPrecio(int cantidadDias);
    }
