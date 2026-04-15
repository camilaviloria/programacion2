#ifndef GESTOR_ARCHIVO_H
#define GESTOR_ARCHIVO_H

#include <string> 

using namespace std;

struct MiembroFamilia {
	int id;
	string name;
	string lastName;
	char gender;
	int age;
	int idBoss;
	bool isDead;
	bool inJail;
	bool wasBoss;
	bool isBoss;
	MiembroFamilia* hijoMayor;
	MiembroFamilia* hijoMenor;
	MiembroFamilia* siguienteEnLista;
};

MiembroFamilia* modelo_crearMiembro(
	int id,
	const string& name,
	const string& lastName,
	char gender,
	int age,
	int idBoss,
	bool isDead,
	bool inJail,
	bool wasBoss,
	bool isBoss
);

MiembroFamilia* modelo_cargarDesdeCSV(const string& rutaArchivo);
bool modelo_guardarEnCSV(MiembroFamilia* cabezaLista, const string& rutaArchivo);
MiembroFamilia* modelo_construirArbol(MiembroFamilia* cabezaLista);
MiembroFamilia* modelo_encontrarSucesor(MiembroFamilia* nodo);
void modelo_limpiarJefes(MiembroFamilia* nodo);
int modelo_contarVivos(MiembroFamilia* nodo);
void modelo_imprimirSucesionVivos(MiembroFamilia* nodo, int& posicion);

#endif
