#include "arbol_familia.h"
#include "../model/gestor_archivo.h"
#include "../view/interfaz_usuario.h"

#include <iostream>
#include <unordered_set>
#include <vector>

static MiembroFamilia* listaGlobal = nullptr;
static MiembroFamilia* raizArbol = nullptr;
static const char* kRutaCSV = "bin/familia.csv";

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

MiembroFamilia* buscarPadreDeNodo(MiembroFamilia* raiz, MiembroFamilia* objetivo) {
	if (raiz == nullptr || objetivo == nullptr) {
		return nullptr;
	}

	if (raiz->hijoMayor == objetivo || raiz->hijoMenor == objetivo) {
		return raiz;
	}

	MiembroFamilia* padreEnMayor = buscarPadreDeNodo(raiz->hijoMayor, objetivo);
	if (padreEnMayor != nullptr) {
		return padreEnMayor;
	}

	return buscarPadreDeNodo(raiz->hijoMenor, objetivo);
}

MiembroFamilia* buscarPrimerSucesorEnDescendientes(MiembroFamilia* nodo, bool permitirCarcel) {
	if (nodo == nullptr) {
		return nullptr;
	}

	MiembroFamilia* sucesorEnMayor = nullptr;
	if (nodo->hijoMayor != nullptr) {
		if (!nodo->hijoMayor->isDead && (!nodo->hijoMayor->inJail || permitirCarcel)) {
			sucesorEnMayor = nodo->hijoMayor;
		} else {
			sucesorEnMayor = buscarPrimerSucesorEnDescendientes(nodo->hijoMayor, permitirCarcel);
		}
	}
	if (sucesorEnMayor != nullptr) {
		return sucesorEnMayor;
	}

	if (nodo->hijoMenor != nullptr) {
		if (!nodo->hijoMenor->isDead && (!nodo->hijoMenor->inJail || permitirCarcel)) {
			return nodo->hijoMenor;
		}
		return buscarPrimerSucesorEnDescendientes(nodo->hijoMenor, permitirCarcel);
	}

	return nullptr;
}

MiembroFamilia* seleccionarDesdeCompanero(MiembroFamilia* companero) {
	if (companero == nullptr) {
		return nullptr;
	}

	MiembroFamilia* sucesorEnArbolCompanero = buscarPrimerSucesorEnDescendientes(companero, false);
	if (sucesorEnArbolCompanero != nullptr) {
		return sucesorEnArbolCompanero;
	}

	if (!companero->isDead && !companero->inJail) {
		return companero;
	}

	sucesorEnArbolCompanero = buscarPrimerSucesorEnDescendientes(companero, true);
	if (sucesorEnArbolCompanero != nullptr) {
		return sucesorEnArbolCompanero;
	}

	if (!companero->isDead && companero->inJail) {
		return companero;
	}

	return nullptr;
}

MiembroFamilia* seleccionarNuevoJefePorReglas(MiembroFamilia* raiz, MiembroFamilia* jefeActual) {
	MiembroFamilia* nuevoJefe = buscarPrimerSucesorEnDescendientes(jefeActual, false);
	if (nuevoJefe != nullptr) {
		return nuevoJefe;
	}

	nuevoJefe = buscarPrimerSucesorEnDescendientes(jefeActual, true);
	if (nuevoJefe != nullptr) {
		return nuevoJefe;
	}

	MiembroFamilia* nodoDeReferencia = jefeActual;
	while (true) {
		MiembroFamilia* padre = buscarPadreDeNodo(raiz, nodoDeReferencia);
		if (padre == nullptr) {
			return nullptr;
		}

		MiembroFamilia* companeroSucesor = nullptr;
		if (padre->hijoMayor == nodoDeReferencia) {
			companeroSucesor = padre->hijoMenor;
		} else {
			companeroSucesor = padre->hijoMayor;
		}

		nuevoJefe = seleccionarDesdeCompanero(companeroSucesor);
		if (nuevoJefe != nullptr) {
			return nuevoJefe;
		}

		nodoDeReferencia = padre;
	}
}

void recolectarNodos(MiembroFamilia* nodo, std::vector<MiembroFamilia*>& nodos) {
	if (nodo == nullptr) {
		return;
	}

	nodos.push_back(nodo);
	recolectarNodos(nodo->hijoMayor, nodos);
	recolectarNodos(nodo->hijoMenor, nodos);
}

void recolectarVivosEnCarcel(MiembroFamilia* nodo, std::vector<MiembroFamilia*>& presos) {
	if (nodo == nullptr) {
		return;
	}

	if (!nodo->isDead && nodo->inJail) {
		presos.push_back(nodo);
	}

	recolectarVivosEnCarcel(nodo->hijoMayor, presos);
	recolectarVivosEnCarcel(nodo->hijoMenor, presos);
}

void controller_eventoCargarDatos() {
	interfaz_mostrarMensaje("Cargando datos desde CSV...");

	listaGlobal = modelo_cargarDesdeCSV(kRutaCSV);
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
	MiembroFamilia* nuevoJefe = seleccionarNuevoJefePorReglas(raizArbol, jefeActual);
	if (nuevoJefe != nullptr) {
		nuevoJefe->isBoss = true;
		nuevoJefe->wasBoss = true;
	}

	if (modelo_guardarEnCSV(listaGlobal, kRutaCSV)) {
		interfaz_mostrarMensaje("Cambios guardados en CSV.");
	} else {
		interfaz_mostrarMensaje("ADVERTENCIA: No se pudieron guardar los cambios en CSV.");
	}

	interfaz_anunciarJefe(nuevoJefe);
	interfaz_mostrarArbol(raizArbol);
}

void controller_eventoMostrarSucesionVivos() {
	if (raizArbol == nullptr) {
		interfaz_mostrarMensaje("ERROR: Base de datos vacia. Cargue datos primero.");
		return;
	}

	std::cout << "\n=== LINEA DE SUCESION ACTUAL (SOLO VIVOS) ===" << std::endl;

	MiembroFamilia* jefeActual = buscarJefeActual(raizArbol);
	if (jefeActual == nullptr) {
		std::cout << "No hay jefe actual definido para calcular la sucesion." << std::endl;
		std::cout << "=============================================\n" << std::endl;
		return;
	}

	std::vector<MiembroFamilia*> nodos;
	recolectarNodos(raizArbol, nodos);
	std::vector<bool> estadoOriginalMuerte;
	estadoOriginalMuerte.reserve(nodos.size());
	for (MiembroFamilia* nodo : nodos) {
		estadoOriginalMuerte.push_back(nodo->isDead);
	}

	int posicion = 1;
	std::unordered_set<int> idsImpresos;
	std::vector<MiembroFamilia*> sucesoresCalculados;

	if (!jefeActual->isDead && !jefeActual->inJail) {
		sucesoresCalculados.push_back(jefeActual);
		idsImpresos.insert(jefeActual->id);
	}

	MiembroFamilia* jefeSimulado = jefeActual;
	while (jefeSimulado != nullptr) {
		jefeSimulado->isDead = true;

		MiembroFamilia* siguiente = seleccionarNuevoJefePorReglas(raizArbol, jefeSimulado);
		if (siguiente == nullptr) {
			break;
		}
		if (idsImpresos.count(siguiente->id) > 0) {
			break;
		}

		sucesoresCalculados.push_back(siguiente);
		idsImpresos.insert(siguiente->id);

		jefeSimulado = siguiente;
	}

	for (MiembroFamilia* sucesor : sucesoresCalculados) {
		if (!sucesor->inJail) {
			std::cout << posicion << ". " << sucesor->name << " " << sucesor->lastName;
			if (sucesor->isBoss) {
				std::cout << " <--- JEFE ACTUAL";
			}
			std::cout << std::endl;
			++posicion;
		}
	}

	for (MiembroFamilia* sucesor : sucesoresCalculados) {
		if (sucesor->inJail) {
			std::cout << posicion << ". " << sucesor->name << " " << sucesor->lastName << " [CARCEL]" << std::endl;
			++posicion;
		}
	}

	if (sucesoresCalculados.empty()) {
		std::cout << "No hay sucesores vivos." << std::endl;
	}

	for (std::size_t i = 0; i < nodos.size(); ++i) {
		nodos[i]->isDead = estadoOriginalMuerte[i];
	}

	std::vector<MiembroFamilia*> presosVivos;
	recolectarVivosEnCarcel(raizArbol, presosVivos);
	if (!presosVivos.empty()) {
		std::cout << "\n--- VIVOS EN CARCEL (ELEGIBLES SOLO SI NO HAY LIBRES) ---" << std::endl;
		for (std::size_t i = 0; i < presosVivos.size(); ++i) {
			std::cout << (i + 1) << ". " << presosVivos[i]->name << " " << presosVivos[i]->lastName
					  << " [CARCEL]" << std::endl;
		}
	}

	std::cout << "=============================================\n" << std::endl;
}
