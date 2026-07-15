package ejecicioJava;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        // 1. Creamos la lista genérica usando la clase abstracta Padre (Polimorfismo)
        List<Vehiculos> flota = new ArrayList<>();

        // 2. Agregamos diferentes tipos de vehículos a la misma lista
        // Auto 1: Precio base 50$, Placa ABC-123, Modelo Corolla, Descuento Fijo de 30$
        flota.add(new AutosParticulares(50.0, "ABC-123", "Toyota Corolla", 30.0));
        
        // Auto 2 (Para probar el descuento de más de 7 días): Precio base 45$, Placa XYZ-789, Yaris, Descuento 25$
        flota.add(new AutosParticulares(45.0, "XYZ-789", "Toyota Yaris", 25.0));

        // Camioneta 1: Precio base 80$, Placa KKK-555, Silverado, Cargo extra 2.5$ por kg, Capacidad 500kg
        flota.add(new CamionetasCarga(80.0, "KKK-555", "Chevrolet Silverado", 2.5, 500.0));

        // 3. Definimos los días de alquiler para la simulación
        int diasAlquiler = 10; 
        double ingresosTotales = 0;

        System.out.println("=========================================================");
        System.out.println("   REPORTE DE ALQUILER DE FLOTA (Simulación: " + diasAlquiler + " días)");
        System.out.println("=========================================================");

        // 4. UN SOLO CICLO para procesar la lista genérica y calcular el total
        for (Vehiculos v : flota) {
            // El polimorfismo decide en tiempo de ejecución qué 'calcularPrecio' llamar
            double precioAlquiler = v.calcularPrecio(diasAlquiler);
            ingresosTotales += precioAlquiler;

            System.out.println("Placa: " + v.getPlaca() + 
                               " | Modelo: " + v.getModelo() + 
                               " | Total Alquiler: $" + precioAlquiler);
        }

        System.out.println("=========================================================");
        System.out.println("Ingresos Totales Generados por la Flota: $" + ingresosTotales);
        System.out.println("=========================================================");
    }
} 