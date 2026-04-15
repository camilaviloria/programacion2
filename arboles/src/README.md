# Sistema de Sucesion de la Familia (MVC C++)

Aplicacion de consola en C++ que carga miembros de una familia mafiosa desde un CSV, construye un arbol binario de sucesion y asigna al proximo jefe disponible.

## Reglas del CSV
Columnas esperadas:

id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss

- gender: solo H o M
- is_dead, in_jail, was_boss, is_boss: solo 0 o 1

Las filas invalidas se ignoran con advertencia en consola.

## Compilacion
Desde la carpeta arboles, ejecutar:

g++ src/main.cpp src/controller/arbol_familia.cpp src/model/gestor_archivo.cpp src/view/interfaz_usuario.cpp -o bin/programa.exe

## Ejecucion
Desde la carpeta arboles:

./bin/programa.exe
