package trabajos_java.POO;

public abstract class Empleado {
    // Atributos protegidos para que las clases hijas puedan acceder a ellos
    protected String id;
    protected String nombre;

    public Empleado(String id, String nombre) {
        this.id = id;
        this.nombre = nombre;
    }

    // Métodos Getters para obtener información (No hay Setters para proteger los datos)
    public String getId() { return id; }
    public String getNombre() { return nombre; }

    // Método abstracto: El núcleo de la Abstracción y el Polimorfismo
    public abstract double calcularSalarioMensual();
}
