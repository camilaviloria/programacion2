package ChainofResponsability;
//Define el contrato para los manejadores y la capacidad de encadenarlos.
public interface Handler {
    //Recibe a otro Handler y lo guarda como el "siguiente en la fila".
    public void setNext(Handler handler);
    //Recibe la petición (el parámetro request). Cada clase que implemente este método 
    // decidirá si tiene los datos/permisos para resolverla o si se la pasa al siguiente 
    // manejador llamando a su propio handle(request).
    public void handle(String request);     

}
