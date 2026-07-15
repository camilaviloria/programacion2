package examenPOO;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        try {
            CsvManager manager = new CsvManager();
            
            // 1. Cargar el archivo provisto 
            manager.loadFromFile("prueba.txt", new StandardCsvReader(","));

            // 2. Crear un modificador interactivo que dependa de la decisión del usuario
            CsvModifier menuInteractivo = new CsvModifier() {
                @Override
                public void apply(CsvTable table) {
                    Scanner scanner = new Scanner(System.in);
                    boolean continuar = true;

                    while (continuar) {
                        System.out.println("\nMenu de modificacion de csv ");
                        System.out.println("1. Agregar Fila");
                        System.out.println("2. Eliminar Fila");
                        System.out.println("3. Agregar Columna");
                        System.out.println("4. Eliminar Columna");
                        System.out.println("5. Finalizar y Mostrar Resultado");
                        System.out.print("Seleccione una opcion ");
                        
                        int opcion = scanner.nextInt();
                        scanner.nextLine(); // Limpiar el salto de línea del buffer

                        switch (opcion) {
                            case 1:
                                // Agregar Fila
                                System.out.println("Ingrese los valores de la fila separados por comas (ejemplo: 106,Pedro,Sistemas,Soporte,1400):");
                                String filaInput = scanner.nextLine();
                                String[] valoresFila = filaInput.split(",");
                                List<String> nuevaFila = new ArrayList<>();
                                for (String val : valoresFila) {
                                    nuevaFila.add(val.trim());
                                }
                                table.addRow(nuevaFila);
                                System.out.println("Fila agregada correctamente");
                                break;

                            case 2:
                                // Eliminar Fila
                                System.out.print("Ingrese el índice de la fila a eliminar (0 para la cabecera, 1 para la primera fila de datos, etc.): ");
                                int indiceFila = scanner.nextInt();
                                table.removeRow(indiceFila);
                                System.out.println("Fila eliminada");
                                break;

                            case 3:
                                // Agregar Columna
                                System.out.print("Ingrese el nombre de la cabecera para la nueva columna: ");
                                String cabeceraCol = scanner.nextLine();
                                
                                List<String> nuevaColumna = new ArrayList<>();
                                nuevaColumna.add(cabeceraCol); // El primer elemento será el título de la columna
                                
                                // Determinar cuántas filas hay actualmente para pedir los datos correspondientes
                                int totalFilas = table.getData().size();
                                System.out.println("Ingrese los valores para cada una de las " + (totalFilas - 1) + " filas restantes:");
                                for (int i = 1; i < totalFilas; i++) {
                                    System.out.print("Valor para la fila " + i + ": ");
                                    nuevaColumna.add(scanner.nextLine());
                                }
                                
                                table.addColumn(nuevaColumna);
                                System.out.println("¡Columna agregada");
                                break;

                            case 4:
                                // Eliminar Columna
                                System.out.print("Ingrese el indice de la columna a eliminar (0 para ID, 1 para Nombre, etc.): ");
                                int indiceCol = scanner.nextInt();
                                table.removeColumn(indiceCol);
                                System.out.println("Columna eliminada");
                                break;

                            case 5:
                                continuar = false;
                                break;

                            default:
                                System.out.println("Opcion no valida.");
                        }
                    }
                }
            };

            // 3. Ejecutar el modificador que creamos al vuelo
            manager.executeModifier(menuInteractivo);

            // 4. Imprimir el resultado final en la consola usando la impresora por defecto
            System.out.println("\nResultado");
            manager.display(new ConsoleCsvPrinter());

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}