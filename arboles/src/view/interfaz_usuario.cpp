#include "interfaz_usuario.h"

#include "../controller/arbol_familia.h"

#include <iostream>

using namespace std;

void interfaz_mostrarMensaje(const string& mensaje) {
	cout << "\n[SISTEMA]: " << mensaje << endl;
}

void interfaz_anunciarJefe(const string& nombreJefe) {
	cout << "--------------------------------" << endl;
	if (!nombreJefe.empty()) {
		cout << "NUEVO JEFE: " << nombreJefe << endl;
	} else {
		cout << "NO HAY SUCESOR DISPONIBLE." << endl;
	}
	cout << "--------------------------------" << endl;
}

void interfaz_mostrarArbol(const string& arbolTexto) {
	cout << "\n=== ARBOL DE LA FAMILIA ===" << endl;
	cout << arbolTexto;
	cout << "===========================\n" << endl;
}

void interfaz_mostrarSucesionVivos(const string& sucesionTexto) {
	cout << "\n=== LINEA DE SUCESION ACTUAL (SOLO VIVOS) ===" << endl;
	cout << sucesionTexto;
	cout << "=============================================\n" << endl;
}

void interfaz_iniciarSistema() {
	int opcion = 0;
	bool ejecutar = true;

	while (ejecutar) {
		cout << "\n1. Cargar datos desde CSV" << endl;
		cout << "2. Asignar nuevo jefe" << endl;
		cout << "3. Mostrar linea de sucesion actual (solo vivos)" << endl;
		cout << "4. Salir" << endl;
		cout << ">> ";

		if (!(cin >> opcion)) {
			cin.clear();
			cin.ignore(1000, '\n');
			opcion = 0;
		}

		switch (opcion) {
			case 1:
				controller_eventoCargarDatos();
				break;
			case 2: {
				int motivo = 0;
				cout << "\nMotivo de cambio de jefe:" << endl;
				cout << "1. Prision" << endl;
				cout << "2. Muerte" << endl;
				cout << ">> ";

				if (!(cin >> motivo)) {
					cin.clear();
					cin.ignore(1000, '\n');
					motivo = 0;
				}

				controller_eventoAsignarJefe(motivo);
				break;
			}
			case 3:
				controller_eventoMostrarSucesionVivos();
				break;
			case 4:
				ejecutar = false;
				interfaz_mostrarMensaje("Saliendo...");
				break;
			default:
				interfaz_mostrarMensaje("Opcion invalida.");
				break;
		}
	}
}
