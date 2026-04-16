#ifndef INTERFAZ_USUARIO_H
#define INTERFAZ_USUARIO_H

#include <string>

#include "../model/gestor_archivo.h"

void interfaz_iniciarSistema();
void interfaz_mostrarMensaje(const std::string& mensaje);
void interfaz_mostrarArbol(MiembroFamilia* raiz);
void interfaz_anunciarJefe(MiembroFamilia* jefe);

#endif
