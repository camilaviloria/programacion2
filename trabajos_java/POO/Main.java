package trabajos_java.POO;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        // Creamos la lista genérica capaz de almacenar cualquier tipo de empleado
        List<Empleado> listaNomina = new ArrayList<>();

        // Agregamos empleados (Instanciación mediante Polimorfismo)
        listaNomina.add(new EmpleadoFijo("F01", "Juan Perez", 1500.00));
        listaNomina.add(new EmpleadoContrato("C01", "Camila Silva", 25.50, 160)); // 25.5$ la hora * 160 horas

        double gastoTotalNomina = 0;

        System.out.println("=== REPORTE DE NÓMINA MENSUAL ===");
        
        // UN SOLO CICLO para procesar y calcular el gasto total
        for (Empleado emp : listaNomina) {
            double salarioMensual = emp.calcularSalarioMensual(); // Polimorfismo en acción
            gastoTotalNomina += salarioMensual;
            
            System.out.println("ID: " + emp.getId() + 
                               " | Nombre: " + emp.getNombre() + 
                               " | Salario Mensual: $" + salarioMensual);
        }

        System.out.println("=================================");
        System.out.println("Gasto Total de la Empresa: $" + gastoTotalNomina);
    }
}