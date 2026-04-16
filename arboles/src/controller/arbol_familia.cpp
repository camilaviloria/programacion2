#include "arbol_familia.h"
#include "../model/gestor_archivo.h"
#include "../view/interfaz_usuario.h"

#include <cctype>
#include <iostream>
#include <limits>
#include <string>
#include <unordered_set>
#include <vector>

static MiembroFamilia* listaGlobal = nullptr;
static MiembroFamilia* raizArbol = nullptr;
static const char* kRutaCSV = "bin/familia.csv";

bool esElegible(MiembroFamilia* nodo, bool permitirCarcel) {
	if (nodo == nullptr || nodo->isDead) {
		return false;
	}

	return permitirCarcel || !nodo->inJail;
}

void limpiarEntradaConsola() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void limpiarEnlacesHijosLista(MiembroFamilia* cabezaLista) {
	MiembroFamilia* actual = cabezaLista;
	while (actual != nullptr) {
		actual->hijoMayor = nullptr;
		actual->hijoMenor = nullptr;
		actual = actual->siguienteEnLista;
	}
}

MiembroFamilia* buscarPorIdEnLista(MiembroFamilia* cabezaLista, int id) {
	MiembroFamilia* actual = cabezaLista;
	while (actual != nullptr) {
		if (actual->id == id) {
			return actual;
		}
		actual = actual->siguienteEnLista;
	}

	return nullptr;
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
		if (esElegible(nodo->hijoMayor, permitirCarcel)) {
			sucesorEnMayor = nodo->hijoMayor;
		} else {
			sucesorEnMayor = buscarPrimerSucesorEnDescendientes(nodo->hijoMayor, permitirCarcel);
		}
	}
	if (sucesorEnMayor != nullptr) {
		return sucesorEnMayor;
	}

	if (nodo->hijoMenor != nullptr) {
		if (esElegible(nodo->hijoMenor, permitirCarcel)) {
			return nodo->hijoMenor;
		}
		return buscarPrimerSucesorEnDescendientes(nodo->hijoMenor, permitirCarcel);
	}

	return nullptr;
}

MiembroFamilia* seleccionarDesdeCompanero(MiembroFamilia* companero, bool permitirCarcel) {
	if (companero == nullptr) {
		return nullptr;
	}

	MiembroFamilia* sucesorEnArbolCompanero = buscarPrimerSucesorEnDescendientes(companero, permitirCarcel);
	if (sucesorEnArbolCompanero != nullptr) {
		return sucesorEnArbolCompanero;
	}

	if (esElegible(companero, permitirCarcel)) {
		return companero;
	}

	return nullptr;
}

bool tieneDosSucesoresElegibles(MiembroFamilia* nodo, bool permitirCarcel) {
	if (nodo == nullptr || nodo->hijoMayor == nullptr || nodo->hijoMenor == nullptr) {
		return false;
	}

	return esElegible(nodo->hijoMayor, permitirCarcel) && esElegible(nodo->hijoMenor, permitirCarcel);
}

MiembroFamilia* buscarJefeCercanoConDosSucesores(MiembroFamilia* raiz, MiembroFamilia* referencia, bool permitirCarcel) {
	MiembroFamilia* actual = referencia;
	while (true) {
		MiembroFamilia* padre = buscarPadreDeNodo(raiz, actual);
		if (padre == nullptr) {
			return nullptr;
		}

		if (tieneDosSucesoresElegibles(padre, permitirCarcel)) {
			return padre;
		}

		actual = padre;
	}
}

MiembroFamilia* seleccionarNuevoJefeEnModo(MiembroFamilia* raiz, MiembroFamilia* jefeActual, bool permitirCarcel) {
	MiembroFamilia* nuevoJefe = buscarPrimerSucesorEnDescendientes(jefeActual, permitirCarcel);
	if (nuevoJefe != nullptr) {
		return nuevoJefe;
	}

	MiembroFamilia* nodoDeReferencia = jefeActual;
	while (true) {
		MiembroFamilia* padre = buscarPadreDeNodo(raiz, nodoDeReferencia);
		if (padre == nullptr) {
			break;
		}

		MiembroFamilia* companeroSucesor = (padre->hijoMayor == nodoDeReferencia) ? padre->hijoMenor : padre->hijoMayor;
		nuevoJefe = seleccionarDesdeCompanero(companeroSucesor, permitirCarcel);
		if (nuevoJefe != nullptr) {
			return nuevoJefe;
		}

		nodoDeReferencia = padre;
	}

	MiembroFamilia* jefeConDosSucesores = buscarJefeCercanoConDosSucesores(raiz, jefeActual, permitirCarcel);
	if (jefeConDosSucesores != nullptr) {
		nuevoJefe = buscarPrimerSucesorEnDescendientes(jefeConDosSucesores, permitirCarcel);
		if (nuevoJefe != nullptr) {
			return nuevoJefe;
		}
	}

	return nullptr;
}

MiembroFamilia* seleccionarNuevoJefePorReglas(MiembroFamilia* raiz, MiembroFamilia* jefeActual) {
	MiembroFamilia* nuevoJefe = seleccionarNuevoJefeEnModo(raiz, jefeActual, false);
	if (nuevoJefe != nullptr) {
		return nuevoJefe;
	}

	return seleccionarNuevoJefeEnModo(raiz, jefeActual, true);
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
	} else if (motivo == 2) {
		jefeActual->isDead = true;
		interfaz_mostrarMensaje("Motivo seleccionado: muerte.");
	} else {
		interfaz_mostrarMensaje("Motivo invalido.");
		return;
	}

	interfaz_mostrarMensaje("Calculando sucesion...");

	modelo_limpiarJefes(raizArbol);

	MiembroFamilia* nuevoJefe = nullptr;
	if (motivo == 1 || jefeActual->age > 70) {
		nuevoJefe = buscarPrimerSucesorEnDescendientes(jefeActual, false);
		if (jefeActual->age > 70 && motivo != 2) {
			interfaz_mostrarMensaje("Transferencia por edad mayor a 70: se prioriza sucesor libre del arbol del jefe.");
		}
	}

	if (nuevoJefe == nullptr) {
		nuevoJefe = seleccionarNuevoJefePorReglas(raizArbol, jefeActual);
	}

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

void controller_eventoEditarMiembro() {
	if (listaGlobal == nullptr || raizArbol == nullptr) {
		interfaz_mostrarMensaje("ERROR: Base de datos vacia. Cargue datos primero.");
		return;
	}

	int idBuscado = 0;
	std::cout << "\nIngrese el ID del nodo a editar: ";
	if (!(std::cin >> idBuscado)) {
		limpiarEntradaConsola();
		interfaz_mostrarMensaje("ID invalido.");
		return;
	}

	MiembroFamilia* nodo = buscarPorIdEnLista(listaGlobal, idBuscado);
	if (nodo == nullptr) {
		interfaz_mostrarMensaje("No se encontro un nodo con ese ID.");
		return;
	}

	bool editar = true;
	while (editar) {
		std::cout << "\nEditando: " << nodo->name << " " << nodo->lastName << " (ID " << nodo->id << ")" << std::endl;
		std::cout << "1. Nombre" << std::endl;
		std::cout << "2. Apellido" << std::endl;
		std::cout << "3. Genero (H/M)" << std::endl;
		std::cout << "4. Edad" << std::endl;
		std::cout << "5. Estado de muerte (0/1)" << std::endl;
		std::cout << "6. Estado de carcel (0/1)" << std::endl;
		std::cout << "7. Fue jefe (0/1)" << std::endl;
		std::cout << "8. Es jefe (0/1)" << std::endl;
		std::cout << "9. Finalizar edicion" << std::endl;
		std::cout << ">> ";

		int opcion = 0;
		if (!(std::cin >> opcion)) {
			limpiarEntradaConsola();
			interfaz_mostrarMensaje("Opcion invalida.");
			continue;
		}

		switch (opcion) {
			case 1: {
				std::string nombre;
				std::cout << "Nuevo nombre: ";
				std::cin >> nombre;
				nodo->name = nombre;
				break;
			}
			case 2: {
				std::string apellido;
				std::cout << "Nuevo apellido: ";
				std::cin >> apellido;
				nodo->lastName = apellido;
				break;
			}
			case 3: {
				char genero = 'H';
				std::cout << "Nuevo genero (H/M): ";
				std::cin >> genero;
				genero = static_cast<char>(std::toupper(static_cast<unsigned char>(genero)));
				if (genero == 'H' || genero == 'M') {
					nodo->gender = genero;
				} else {
					interfaz_mostrarMensaje("Genero invalido.");
				}
				break;
			}
			case 4: {
				int edad = 0;
				std::cout << "Nueva edad: ";
				if (std::cin >> edad && edad >= 0) {
					nodo->age = edad;
				} else {
					limpiarEntradaConsola();
					interfaz_mostrarMensaje("Edad invalida.");
				}
				break;
			}
			case 5: {
				int valor = 0;
				std::cout << "is_dead (0/1): ";
				if (std::cin >> valor && (valor == 0 || valor == 1)) {
					nodo->isDead = (valor == 1);
				} else {
					limpiarEntradaConsola();
					interfaz_mostrarMensaje("Valor invalido.");
				}
				break;
			}
			case 6: {
				int valor = 0;
				std::cout << "in_jail (0/1): ";
				if (std::cin >> valor && (valor == 0 || valor == 1)) {
					nodo->inJail = (valor == 1);
				} else {
					limpiarEntradaConsola();
					interfaz_mostrarMensaje("Valor invalido.");
				}
				break;
			}
			case 7: {
				int valor = 0;
				std::cout << "was_boss (0/1): ";
				if (std::cin >> valor && (valor == 0 || valor == 1)) {
					nodo->wasBoss = (valor == 1);
				} else {
					limpiarEntradaConsola();
					interfaz_mostrarMensaje("Valor invalido.");
				}
				break;
			}
			case 8: {
				int valor = 0;
				std::cout << "is_boss (0/1): ";
				if (std::cin >> valor && (valor == 0 || valor == 1)) {
					if (valor == 1) {
						modelo_limpiarJefes(raizArbol);
						nodo->isBoss = true;
						nodo->wasBoss = true;
					} else {
						nodo->isBoss = false;
					}
				} else {
					limpiarEntradaConsola();
					interfaz_mostrarMensaje("Valor invalido.");
				}
				break;
			}
			case 9:
				editar = false;
				break;
			default:
				interfaz_mostrarMensaje("Opcion invalida.");
				break;
		}
	}

	limpiarEnlacesHijosLista(listaGlobal);
	raizArbol = modelo_construirArbol(listaGlobal);

	if (modelo_guardarEnCSV(listaGlobal, kRutaCSV)) {
		interfaz_mostrarMensaje("Cambios guardados en CSV.");
	} else {
		interfaz_mostrarMensaje("ADVERTENCIA: No se pudieron guardar los cambios en CSV.");
	}

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
