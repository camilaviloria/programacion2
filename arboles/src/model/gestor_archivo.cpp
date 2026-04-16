#include "gestor_archivo.h"

#include <fstream>
#include <iostream>

namespace {

std::string obtenerCampo(const std::string& linea, int indice) {
	std::string campo = "";
	int comas = 0;

	for (char c : linea) {
		if (c == ',') {
			++comas;
			if (comas > indice) {
				break;
			}
		} else if (comas == indice) {
			campo += c;
		}
	}

	return campo;
}

int contarComas(const std::string& linea) {
	int total = 0;
	for (char c : linea) {
		if (c == ',') {
			++total;
		}
	}
	return total;
}

bool convertirEntero(const std::string& texto, int& valor) {
	try {
		std::size_t idx = 0;
		int numero = std::stoi(texto, &idx);
		if (idx != texto.size()) {
			return false;
		}
		valor = numero;
		return true;
	} catch (...) {
		return false;
	}
}

bool convertirBool01(const std::string& texto, bool& valor) {
	if (texto == "0") {
		valor = false;
		return true;
	}
	if (texto == "1") {
		valor = true;
		return true;
	}
	return false;
}

MiembroFamilia* buscarPorId(MiembroFamilia* cabeza, int id) {
	MiembroFamilia* actual = cabeza;
	while (actual != nullptr) {
		if (actual->id == id) {
			return actual;
		}
		actual = actual->siguienteEnLista;
	}
	return nullptr;
}

MiembroFamilia* encontrarSucesorPorEstado(MiembroFamilia* nodo, bool incluirPrision) {
	if (nodo == nullptr) {
		return nullptr;
	}

	if (!nodo->isDead && (incluirPrision || !nodo->inJail)) {
		return nodo;
	}

	MiembroFamilia* candidatoMayor = encontrarSucesorPorEstado(nodo->hijoMayor, incluirPrision);
	if (candidatoMayor != nullptr) {
		return candidatoMayor;
	}

	return encontrarSucesorPorEstado(nodo->hijoMenor, incluirPrision);
}

bool cumpleFiltroSucesion(MiembroFamilia* nodo, bool incluirPrision) {
	return !nodo->isDead && (incluirPrision ? nodo->inJail : !nodo->inJail);
}

MiembroFamilia* buscarJefeEnArbol(MiembroFamilia* nodo) {
	if (nodo == nullptr) {
		return nullptr;
	}

	if (nodo->isBoss) {
		return nodo;
	}

	MiembroFamilia* jefeEnMayor = buscarJefeEnArbol(nodo->hijoMayor);
	if (jefeEnMayor != nullptr) {
		return jefeEnMayor;
	}

	return buscarJefeEnArbol(nodo->hijoMenor);
}

void imprimirSucesionPorEstado(MiembroFamilia* nodo, int& posicion, bool incluirPrision, int idExcluido) {
	if (nodo == nullptr) {
		return;
	}

	if (nodo->id != idExcluido && cumpleFiltroSucesion(nodo, incluirPrision)) {
		std::cout << posicion << ". " << nodo->name << " " << nodo->lastName;
		if (nodo->isBoss) {
			std::cout << " <--- JEFE ACTUAL";
		}
		if (nodo->inJail) {
			std::cout << " [CARCEL]";
		}
		std::cout << std::endl;
		++posicion;
	}

	imprimirSucesionPorEstado(nodo->hijoMayor, posicion, incluirPrision, idExcluido);
	imprimirSucesionPorEstado(nodo->hijoMenor, posicion, incluirPrision, idExcluido);
}

}

MiembroFamilia* modelo_crearMiembro(
	int id,
	const std::string& name,
	const std::string& lastName,
	char gender,
	int age,
	int idBoss,
	bool isDead,
	bool inJail,
	bool wasBoss,
	bool isBoss
) {
	MiembroFamilia* miembro = new MiembroFamilia;
	miembro->id = id;
	miembro->name = name;
	miembro->lastName = lastName;
	miembro->gender = gender;
	miembro->age = age;
	miembro->idBoss = idBoss;
	miembro->isDead = isDead;
	miembro->inJail = inJail;
	miembro->wasBoss = wasBoss;
	miembro->isBoss = isBoss;
	miembro->hijoMayor = nullptr;
	miembro->hijoMenor = nullptr;
	miembro->siguienteEnLista = nullptr;
	return miembro;
}

MiembroFamilia* modelo_cargarDesdeCSV(const std::string& rutaArchivo) {
	std::ifstream archivo(rutaArchivo);
	if (!archivo.is_open()) {
		return nullptr;
	}

	std::string linea;
	std::getline(archivo, linea);

	MiembroFamilia* cabeza = nullptr;
	MiembroFamilia* ultimo = nullptr;
	int numeroLinea = 1;

	while (std::getline(archivo, linea)) {
		++numeroLinea;
		if (linea.empty()) {
			continue;
		}

		if (contarComas(linea) != 9) {
			std::cout << "[ADVERTENCIA] Linea " << numeroLinea
					  << " ignorada: se esperaban 10 columnas." << std::endl;
			continue;
		}

		std::string campoId = obtenerCampo(linea, 0);
		std::string campoName = obtenerCampo(linea, 1);
		std::string campoLastName = obtenerCampo(linea, 2);
		std::string campoGender = obtenerCampo(linea, 3);
		std::string campoAge = obtenerCampo(linea, 4);
		std::string campoIdBoss = obtenerCampo(linea, 5);
		std::string campoIsDead = obtenerCampo(linea, 6);
		std::string campoInJail = obtenerCampo(linea, 7);
		std::string campoWasBoss = obtenerCampo(linea, 8);
		std::string campoIsBoss = obtenerCampo(linea, 9);

		int id = 0;
		int age = 0;
		int idBoss = 0;
		bool isDead = false;
		bool inJail = false;
		bool wasBoss = false;
		bool isBoss = false;

		const std::string& name = campoName;
		const std::string& lastName = campoLastName;

		bool idOk = convertirEntero(campoId, id);
		bool ageOk = convertirEntero(campoAge, age);
		bool idBossOk = convertirEntero(campoIdBoss, idBoss);
		bool deadOk = convertirBool01(campoIsDead, isDead);
		bool jailOk = convertirBool01(campoInJail, inJail);
		bool wasBossOk = convertirBool01(campoWasBoss, wasBoss);
		bool isBossOk = convertirBool01(campoIsBoss, isBoss);
		bool genderOk = (campoGender.size() == 1 && (campoGender[0] == 'H' || campoGender[0] == 'M'));

		if (!(idOk && ageOk && idBossOk && deadOk && jailOk && wasBossOk && isBossOk && genderOk)) {
			std::cout << "[ADVERTENCIA] Linea " << numeroLinea
					  << " ignorada: valores invalidos (genero o banderas)." << std::endl;
			continue;
		}

		MiembroFamilia* nuevo = modelo_crearMiembro(
			id,
			name,
			lastName,
			campoGender[0],
			age,
			idBoss,
			isDead,
			inJail,
			wasBoss,
			isBoss
		);

		if (cabeza == nullptr) {
			cabeza = nuevo;
			ultimo = nuevo;
		} else {
			ultimo->siguienteEnLista = nuevo;
			ultimo = nuevo;
		}
	}

	return cabeza;
}

bool modelo_guardarEnCSV(MiembroFamilia* cabezaLista, const std::string& rutaArchivo) {
	std::ofstream archivo(rutaArchivo);
	if (!archivo.is_open()) {
		return false;
	}

	archivo << "id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss\n";

	MiembroFamilia* actual = cabezaLista;
	while (actual != nullptr) {
		archivo << actual->id << ","
				<< actual->name << ","
				<< actual->lastName << ","
				<< actual->gender << ","
				<< actual->age << ","
				<< actual->idBoss << ","
				<< (actual->isDead ? 1 : 0) << ","
				<< (actual->inJail ? 1 : 0) << ","
				<< (actual->wasBoss ? 1 : 0) << ","
				<< (actual->isBoss ? 1 : 0) << "\n";

		actual = actual->siguienteEnLista;
	}

	return true;
}

MiembroFamilia* modelo_construirArbol(MiembroFamilia* cabezaLista) {
	MiembroFamilia* raiz = nullptr;
	MiembroFamilia* actual = cabezaLista;

	while (actual != nullptr) {
		if (actual->idBoss == 0) {
			if (raiz == nullptr) {
				raiz = actual;
			}
			actual = actual->siguienteEnLista;
			continue;
		}

		MiembroFamilia* jefe = buscarPorId(cabezaLista, actual->idBoss);
		if (jefe != nullptr) {
			if (jefe->hijoMayor == nullptr) {
				jefe->hijoMayor = actual;
			} else if (actual->age > jefe->hijoMayor->age) {
				jefe->hijoMenor = jefe->hijoMayor;
				jefe->hijoMayor = actual;
			} else {
				jefe->hijoMenor = actual;
			}
		}

		actual = actual->siguienteEnLista;
	}

	return raiz;
}

MiembroFamilia* modelo_encontrarSucesor(MiembroFamilia* nodo) {
	if (nodo == nullptr) {
		return nullptr;
	}

	MiembroFamilia* sucesorLibre = encontrarSucesorPorEstado(nodo, false);
	if (sucesorLibre != nullptr) {
		return sucesorLibre;
	}

	return encontrarSucesorPorEstado(nodo, true);
}

void modelo_limpiarJefes(MiembroFamilia* nodo) {
	if (nodo == nullptr) {
		return;
	}

	nodo->isBoss = false;
	modelo_limpiarJefes(nodo->hijoMayor);
	modelo_limpiarJefes(nodo->hijoMenor);
}

int modelo_contarVivos(MiembroFamilia* nodo) {
	if (nodo == nullptr) {
		return 0;
	}

	int vivosEnNodo = nodo->isDead ? 0 : 1;
	return vivosEnNodo + modelo_contarVivos(nodo->hijoMayor) + modelo_contarVivos(nodo->hijoMenor);
}

void modelo_imprimirSucesionVivos(MiembroFamilia* nodo, int& posicion) {
	if (nodo == nullptr) {
		return;
	}

	int idJefeImpreso = -1;
	MiembroFamilia* jefeActual = buscarJefeEnArbol(nodo);
	if (jefeActual != nullptr && cumpleFiltroSucesion(jefeActual, false)) {
		std::cout << posicion << ". " << jefeActual->name << " " << jefeActual->lastName << " <--- JEFE ACTUAL" << std::endl;
		++posicion;
		idJefeImpreso = jefeActual->id;
	}

	imprimirSucesionPorEstado(nodo, posicion, false, idJefeImpreso);
	imprimirSucesionPorEstado(nodo, posicion, true, idJefeImpreso);
}
