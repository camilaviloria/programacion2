package TemplateMethod;
//define el esqueleto o la estructura de un algoritmo en un método de una clase base (AbstractClass), 
//pero delega la implementación de algunos pasos específicos a las subclases (ConcreteClasses).
//Permite que las subclases redefinan ciertos pasos de un algoritmo sin 
//cambiar la estructura general del mismo.
public abstract class AbstractClass {
    // Método plantilla (Template Method): Define la secuencia exacta
    public final void templateMethod() {
        step1();
        if (step2()) { // 'step2' actúa como un 'hook' o condición
            step3();
        } else {
            step4();
        }
    }

    // Pasos genéricos o abstractos
    protected abstract void step1();
    
    // Puede ser un método con implementación por defecto (Hook)
    protected boolean step2() {
        return true; 
    }

    protected abstract void step3();
    protected abstract void step4();
}
