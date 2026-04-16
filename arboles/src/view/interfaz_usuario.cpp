#include "interfaz_usuario.h"

#include "../controller/arbol_familia.h"

#include <iostream>

namespace {

void imprimirNodo(MiembroFamilia* nodo, int nivel) {
	if (nodo == nullptr) {
		return;
	}

	for (int i = 0; i < nivel; ++i) {
		std::cout << "   ";
	}

	std::cout << (nodo->isDead ? "[X] " : "[ ] ")
			  << nodo->name << " " << nodo->lastName
			  << " (" << nodo->gender << ", " << nodo->age << ")";

	if (nodo->inJail) {
		std::cout << " [CARCEL]";
	}
	if (nodo->isBoss) {
		std::cout << " <--- JEFE";
	}

	std::cout << std::endl;

	imprimirNodo(nodo->hijoMayor, nivel + 1);
	imprimirNodo(nodo->hijoMenor, nivel + 1);
}

}

void interfaz_mostrarMensaje(const std::string& mensaje) {
	std::cout << "\n[SISTEMA]: " << mensaje << std::endl;
}

void interfaz_anunciarJefe(MiembroFamilia* jefe) {
	std::cout << "--------------------------------" << std::endl;
	if (jefe != nullptr) {
		std::cout << "NUEVO JEFE: " << jefe->name << " " << jefe->lastName << std::endl;
	} else {
		std::cout << "NO HAY SUCESOR DISPONIBLE." << std::endl;
	}
	std::cout << "--------------------------------" << std::endl;
}

void interfaz_mostrarArbol(MiembroFamilia* raiz) {
	std::cout << "\n=== ARBOL DE LA FAMILIA ===" << std::endl;
	if (raiz == nullptr) {
		std::cout << "(Vacio)" << std::endl;
	} else {
		imprimirNodo(raiz, 0);
	}
	std::cout << "===========================\n" << std::endl;
}

void interfaz_iniciarSistema() {
	int opcion = 0;
	bool ejecutar = true;

	while (ejecutar) {
		std::cout << "\n1. Cargar datos desde CSV" << std::endl;
		std::cout << "2. Asignar nuevo jefe" << std::endl;
		std::cout << "3. Mostrar linea de sucesion actual (solo vivos)" << std::endl;
		std::cout << "4. Editar datos de un nodo" << std::endl;
		std::cout << "5. Salir" << std::endl;
		std::cout << ">> ";

		if (!(std::cin >> opcion)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			opcion = 0;
		}

		switch (opcion) {
			case 1:
				controller_eventoCargarDatos();
				break;
			case 2: {
				int motivo = 0;
				std::cout << "\nMotivo de cambio de jefe:" << std::endl;
				std::cout << "1. Prision" << std::endl;
				std::cout << "2. Muerte" << std::endl;
				std::cout << ">> ";

				if (!(std::cin >> motivo)) {
					std::cin.clear();
					std::cin.ignore(1000, '\n');
					motivo = 0;
				}

				controller_eventoAsignarJefe(motivo);
				break;
			}
			case 3:
				controller_eventoMostrarSucesionVivos();
				break;
			case 4:
				controller_eventoEditarMiembro();
				break;
			case 5:
				ejecutar = false;
				interfaz_mostrarMensaje("Saliendo...");
				break;
			default:
				interfaz_mostrarMensaje("Opcion invalida.");
				break;
		}
	}
}
