package builder;
//Imaginemos que queremos ensamblar computadoras personalizadas (una de Oficina y otra Gamer).
public class Computadora {

    private String procesador;
    private String tarjetaGrafica;
    private int ram;
    private int almacenamiento;

    // Métodos setters para que el Builder los use
    public void setProcesador(String procesador) { this.procesador = procesador; }
    public void setTarjetaGrafica(String tarjetaGrafica) { this.tarjetaGrafica = tarjetaGrafica; }
    public void setRam(int ram) { this.ram = ram; }
    public void setAlmacenamiento(int almacenamiento) { this.almacenamiento = almacenamiento; }

    @Override
    public String toString() {
        return "Computadora {" +
                "Procesador='" + procesador + '\'' +
                ", GPU='" + tarjetaGrafica + '\'' +
                ", RAM=" + ram + "GB" +
                ", Disco=" + almacenamiento + "GB" +
                '}';
    }
}