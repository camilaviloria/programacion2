package TemplateMethod;
//Sobrescribe todos los pasos e incluso altera el resultado de step2() para forzar que el flujo ejecute step4() en lugar de step3().
public class ConcreteClass2 extends AbstractClass {

    @Override
    protected void step1() {
        System.out.println("[Excel]: Creando libro de trabajo (.xlsx)...");
    }

    @Override
    protected boolean step2() {
        // Al devolver false, el templateMethod tomará el camino del 'else'
        return false;
    }

    @Override
    protected void step3() {
        System.out.println("[Excel]: Este paso se omitirá.");
    }

    @Override
    protected void step4() {
        System.out.println("[Excel]: Rellenando celdas con fórmulas y estilos.");
    }
}
