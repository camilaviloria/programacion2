package TemplateMethod;
//Cada subclase implementa o sobrescribe solo los pasos requeridos según sus necesidades.
//Sobrescribe solo los pasos que necesita (step3 y step4), manteniendo step2() en true.
public class ConcreteClass1 extends AbstractClass {

    @Override
    protected void step1() {
        System.out.println("[PDF]: Inicializando cabecera y plantilla PDF...");
    }

    @Override
    protected void step3() {
        System.out.println("[PDF]: Dibujando tablas de datos en formato vectorial.");
    }

    @Override
    protected void step4() {
        System.out.println("[PDF]: Generando pie de página estándar.");
    }
}