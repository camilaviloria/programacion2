package examenPatrones;

public class Lider {
    private int subordinadoId; 
    private int radioDeDominio;
    private int repeticionesPorSegundo;
    private Configuracion configuracionAsociada;

    public Lider(int subordinadoId, int radioDeDominio, int repeticionesPorSegundo, Configuracion configuracion) {
        this.subordinadoId = subordinadoId;
        this.radioDeDominio = radioDeDominio;
        this.repeticionesPorSegundo = repeticionesPorSegundo;
        this.configuracionAsociada = configuracion;
    }

    public void ajustarParametros(int nuevoRadioDominio, int nuevasRepeticiones) {
        this.radioDeDominio = nuevoRadioDominio;
        this.repeticionesPorSegundo = nuevasRepeticiones;
        
        System.out.println("\n⚡ [LÍDER]: Ajustando parámetros a Radio Dominio = " 
                + nuevoRadioDominio + ", Rep/s = " + nuevasRepeticiones);

          if (configuracionAsociada != null) {
            configuracionAsociada.actualizarDesdeLider(nuevoRadioDominio, nuevasRepeticiones);
        }
    }
}
