package TemplateMethod;
//Es un patrón de diseño de comportamiento que define el
//esqueleto de un algoritmo en la superclase pero permite
//que las subclases sobrescriban pasos del algoritmo sin
//cambiar su estructura.
public class Client {
    public static void main(String[] args) {
        System.out.println("--- Ejecutando Reporte 1 (PDF) ---");
        // 1. Instancia la primera clase concreta usando el tipo base
        AbstractClass reportePDF = new ConcreteClass1();
        // 2. Llama al método plantilla (NO a los pasos individuales step1, step2...)
        reportePDF.templateMethod();

        System.out.println("\n--- Ejecutando Reporte 2 (Excel) ---");
        // 3. Instancia la segunda clase concreta
        AbstractClass reporteExcel = new ConcreteClass2();
        // 4. Llama nuevamente al método plantilla
        reporteExcel.templateMethod();
    }
}
