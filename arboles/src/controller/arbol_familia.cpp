#include "arbol_familia.h"
#include "../model/gestor_archivo.h"
#include "../view/interfaz_usuario.h"

static MiembroFamilia* listaGlobal = nullptr;
static MiembroFamilia* raizArbol = nullptr;

void controller_eventoCargarDatos() {
	interfaz_mostrarMensaje("Cargando datos desde CSV...");

	listaGlobal = modelo_cargarDesdeCSV("bin/familia.csv");
	if (listaGlobal == nullptr) {
		interfaz_mostrarMensaje("ERROR: No se pudo abrir o procesar 'bin/familia.csv'.");
		raizArbol = nullptr;
		return;
	}

	raizArbol = modelo_construirArbol(listaGlobal);
	if (raizArbol == nullptr) {
		interfaz_mostrarMensaje("ERROR: No se encontro nodo raiz (id_boss = 0). Revise el CSV.");
		return;
	}

	interfaz_mostrarMensaje("Datos cargados exitosamente.");
	interfaz_mostrarArbol(raizArbol);
}

void controller_eventoAsignarJefe() {
	if (raizArbol == nullptr) {
		interfaz_mostrarMensaje("ERROR: Base de datos vacia. Cargue datos primero.");
		return;
	}

	interfaz_mostrarMensaje("Calculando sucesion...");

	modelo_limpiarJefes(raizArbol);
	MiembroFamilia* nuevoJefe = modelo_encontrarSucesor(raizArbol);
	if (nuevoJefe != nullptr) {
		nuevoJefe->isBoss = true;
		nuevoJefe->wasBoss = true;
	}

	interfaz_anunciarJefe(nuevoJefe);
	interfaz_mostrarArbol(raizArbol);
}
