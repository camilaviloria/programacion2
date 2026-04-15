#ifndef INTERFAZ_USUARIO_H
#define INTERFAZ_USUARIO_H

#include <string> 

using namespace std;

void interfaz_iniciarSistema();
void interfaz_mostrarMensaje(const string& mensaje);
void interfaz_mostrarArbol(const string& arbolTexto);
void interfaz_anunciarJefe(const string& nombreJefe);
void interfaz_mostrarSucesionVivos(const string& sucesionTexto);

#endif
