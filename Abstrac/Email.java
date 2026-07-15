package Abstrac;
// Producto Abstracto A
interface Email {
    void enviarEmail(String contenido);
}

// Producto Abstracto B
interface SMS {
    void enviarSMS(String contenido);
}
