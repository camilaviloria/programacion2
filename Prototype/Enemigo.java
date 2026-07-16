package Prototype;

public class Enemigo implements Prototype {
    private String tipo;
    private int vida;
    private String arma;

    // Constructor normal para el primer prototipo
    public Enemigo(String tipo, int vida, String arma) {
        this.tipo = tipo;
        this.vida = vida;
        this.arma = arma;
    }    
// Constructor de copia (el truco del patrón)
public Enemigo(Enemigo prototipo) {
    this.tipo = prototipo.tipo;
    this.vida = prototipo.vida;
    this.arma = prototipo.arma;
}

// Getters y Setters para que el clon pueda modificarse después
public void setVida(int vida) { this.vida = vida; }

@Override
public Prototype duplicar() {
    return new Enemigo(this); // Retorna una copia exacta usando el constructor de copia
}

@Override
public String toString() {
    return "Enemigo [Tipo=" + tipo + ", Vida=" + vida + "HP, Arma=" + arma + "]";
}
}
