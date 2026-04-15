#include "arbol_familia.h"
#include "../model/gestor_archivo.h"
#include "../view/interfaz_usuario.h"

#include <sstream>
#include <string> 

using namespace std;

static MiembroFamilia* listaGlobal = nullptr;
static MiembroFamilia* raizArbol = nullptr;

void construirTextoArbol(MiembroFamilia* nodo, int nivel, ostringstream& salida) {
	if (nodo == nullptr) {
		return;
	}

	for (int i = 0; i < nivel; ++i) {
		salida << "   ";
	}

	salida << (nodo->isDead ? "[X] " : "[ ] ")
		   << nodo->name << " " << nodo->lastName
		   << " (" << nodo->gender << ", " << nodo->age << ")";

	if (nodo->inJail) {
		salida << " [CARCEL]";
	}
	if (nodo->isBoss) {
		salida << " <--- JEFE";
	}

	salida << '\n';

	construirTextoArbol(nodo->hijoMayor, nivel + 1, salida);
	construirTextoArbol(nodo->hijoMenor, nivel + 1, salida);
}

string obtenerTextoArbol(MiembroFamilia* raiz) {
	if (raiz == nullptr) {
		return "(Vacio)\n";
	}

	ostringstream salida;
	construirTextoArbol(raiz, 0, salida);
	return salida.str();
}

string obtenerNombreJefe(MiembroFamilia* jefe) {
	if (jefe == nullptr) {
		return "";
	}

	return jefe->name + " " + jefe->lastName;
}

void construirTextoSucesionPorEstado(MiembroFamilia* nodo, int& posicion, ostringstream& salida, bool incluirPrision) {
	if (nodo == nullptr) {
		return;
	}

	if (!nodo->isDead && ((incluirPrision && nodo->inJail) || (!incluirPrision && !nodo->inJail))) {
		salida << posicion << ". " << nodo->name << " " << nodo->lastName;
		if (nodo->isBoss) {
			salida << " <--- JEFE ACTUAL";
		}
		if (nodo->inJail) {
			salida << " [CARCEL]";
		}
		salida << '\n';
		++posicion;
	}

	construirTextoSucesionPorEstado(nodo->hijoMayor, posicion, salida, incluirPrision);
	construirTextoSucesionPorEstado(nodo->hijoMenor, posicion, salida, incluirPrision);
}

string obtenerTextoSucesionVivos(MiembroFamilia* raiz) {
	int totalVivos = modelo_contarVivos(raiz);
	if (totalVivos == 0) {
		return "No hay miembros vivos en la familia.\n";
	}

	int posicion = 1;
	ostringstream salida;
	construirTextoSucesionPorEstado(raiz, posicion, salida, false);
	construirTextoSucesionPorEstado(raiz, posicion, salida, true);
	return salida.str();
}

MiembroFamilia* buscarJefeActual(MiembroFamilia* nodo) {
	if (nodo == nullptr) {
		return nullptr;
	}

	if (nodo->isBoss) {
		return nodo;
	}

	MiembroFamilia* jefeEnMayor = buscarJefeActual(nodo->hijoMayor);
	if (jefeEnMayor != nullptr) {
		return jefeEnMayor;
	}

	return buscarJefeActual(nodo->hijoMenor);
}

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
	interfaz_mostrarArbol(obtenerTextoArbol(raizArbol));
}

void controller_eventoAsignarJefe(int motivo) {
	if (raizArbol == nullptr) {
		interfaz_mostrarMensaje("ERROR: Base de datos vacia. Cargue datos primero.");
		return;
	}

	if (motivo != 1 && motivo != 2) {
		interfaz_mostrarMensaje("Motivo invalido. Use 1 (prision) o 2 (muerte).");
		return;
	}

	MiembroFamilia* jefeActual = buscarJefeActual(raizArbol);
	if (jefeActual == nullptr) {
		interfaz_mostrarMensaje("ERROR: No se encontro un jefe actual para reasignar.");
		return;
	}

	if (motivo == 1) {
		jefeActual->inJail = true;
		interfaz_mostrarMensaje("Motivo seleccionado: prision.");
	} else {
		jefeActual->isDead = true;
		interfaz_mostrarMensaje("Motivo seleccionado: muerte.");
	}

	interfaz_mostrarMensaje("Calculando sucesion...");

	modelo_limpiarJefes(raizArbol);
	MiembroFamilia* nuevoJefe = modelo_encontrarSucesor(raizArbol);
	if (nuevoJefe != nullptr) {
		nuevoJefe->isBoss = true;
		nuevoJefe->wasBoss = true;
	}

	if (modelo_guardarEnCSV(listaGlobal, "bin/familia.csv")) {
		interfaz_mostrarMensaje("Cambios guardados en CSV.");
	} else {
		interfaz_mostrarMensaje("ADVERTENCIA: No se pudieron guardar los cambios en CSV.");
	}

	interfaz_anunciarJefe(obtenerNombreJefe(nuevoJefe));
	interfaz_mostrarArbol(obtenerTextoArbol(raizArbol));
}

void controller_eventoMostrarSucesionVivos() {
	if (raizArbol == nullptr) {
		interfaz_mostrarMensaje("ERROR: Base de datos vacia. Cargue datos primero.");
		return;
	}

	interfaz_mostrarSucesionVivos(obtenerTextoSucesionVivos(raizArbol));
}
