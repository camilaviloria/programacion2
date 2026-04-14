#ifndef GESTOR_ARCHIVO_H
#define GESTOR_ARCHIVO_H

#include <string> 
 
struct MiembroFamilia {
	int id;
	std::string name;
	std::string lastName;
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
	const std::string& name,
	const std::string& lastName,
	char gender,
	int age,
	int idBoss,
	bool isDead,
	bool inJail,
	bool wasBoss,
	bool isBoss
);

MiembroFamilia* modelo_cargarDesdeCSV(const std::string& rutaArchivo);
MiembroFamilia* modelo_construirArbol(MiembroFamilia* cabezaLista);
MiembroFamilia* modelo_encontrarSucesor(MiembroFamilia* nodo);
void modelo_limpiarJefes(MiembroFamilia* nodo);

#endif
