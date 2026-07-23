package examenPatrones;

import java.util.ArrayList;
import java.util.List;

public class Main {
    public static void main(String[] args) {
        Configuracion configA = new Configuracion(60.0f, 10, 'A');

        Lider liderGrupoA = new Lider(1, 60, 10, configA);

        List<PuntoEspecifico> puntos = new ArrayList<>();
        for (int i = 0; i < 100000; i++) {
            puntos.add(new PuntoEspecifico((float) (Math.random() * 100), (float) (Math.random() * 100), configA));
        }

        System.out.println("--- ESTADO INICIAL ---");
        puntos.get(0).mostrarInformacion();
        puntos.get(1).mostrarInformacion();

        liderGrupoA.ajustarParametros(65, 2);

        System.out.println("\n--- ESTADO TRAS EL CAMBIO DEL LÍDER ---");
        puntos.get(0).mostrarInformacion();
        puntos.get(99999).mostrarInformacion();

        liderGrupoA.ajustarParametros(67, 5);

        System.out.println("\n--- ESTADO TRAS SEGUNDO CAMBIO DEL LÍDER ---");
        puntos.get(0).mostrarInformacion();
    }
}