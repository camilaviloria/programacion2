# Sistema de Sucesion de la Familia (MVC C++)

Aplicacion de consola en C++ para gestionar la sucesion de mando de una familia a partir de datos en CSV.
El sistema carga los integrantes, arma un arbol familiar binario y calcula automaticamente quien debe asumir como nuevo jefe cuando el jefe actual cae en prision o muere.

## Que hace el programa

1. Carga datos de miembros desde `bin/familia.csv`.
2. Construye un arbol familiar usando la relacion `id_boss`.
3. Muestra el arbol en consola con estados (vivo/muerto, carcel, jefe).
4. Reasigna el jefe segun reglas de sucesion.
5. Permite editar miembros desde menu y guardar cambios en el CSV.
6. Calcula y muestra la linea de sucesion actual considerando solo vivos.

## Como esta organizado (MVC)

- `view/interfaz_usuario.*`:
	- Muestra menus, mensajes y el arbol.
	- Captura opciones del usuario.
	- Dispara eventos hacia el controlador.

- `controller/arbol_familia.*`:
	- Coordina el flujo principal del sistema.
	- Administra la lista global de miembros y la raiz del arbol.
	- Implementa la logica de sucesion y la edicion interactiva.

- `model/gestor_archivo.*`:
	- Define la estructura `MiembroFamilia`.
	- Carga/valida datos CSV.
	- Construye el arbol binario y guarda cambios en archivo.

## Estructura de datos principal

Cada miembro tiene campos:

- `id`, `name`, `last_name`, `gender`, `age`
- `id_boss` (id del superior directo)
- `is_dead`, `in_jail`, `was_boss`, `is_boss`

Y punteros:

- `hijoMayor`, `hijoMenor` para el arbol binario
- `siguienteEnLista` para la lista enlazada original

El sistema mantiene ambas vistas de los datos:

- Lista enlazada para recorrido y persistencia en CSV.
- Arbol binario para calcular y visualizar sucesion.

## Construccion del arbol

Durante la construccion:

- El nodo con `id_boss = 0` se toma como raiz.
- Cada nodo se conecta a su jefe buscando por `id`.
- Si un jefe tiene dos posibles hijos:
	- el de mayor edad queda en `hijoMayor`
	- el otro queda en `hijoMenor`

Esto define un arbol binario de prioridad por edad dentro de cada pareja de hijos.

## Reglas de sucesion (resumen de la logica real)

Cuando se asigna nuevo jefe (`opcion 2`), el sistema:

1. Encuentra el jefe actual (`is_boss = 1`).
2. Marca su causa de salida:
	 - prision (`in_jail = true`) o
	 - muerte (`is_dead = true`).
3. Limpia el estado de jefe en todo el arbol (`is_boss = false`).
4. Busca sucesor con prioridad:
	 - primero miembros vivos y libres (no presos),
	 - si no hay, miembros vivos en carcel.
5. Marca al nuevo jefe con:
	 - `is_boss = true`
	 - `was_boss = true`
6. Guarda cambios en `bin/familia.csv`.

### Prioridad de busqueda

La seleccion intenta, en orden:

1. Descendientes del jefe actual (primero rama `hijoMayor`, luego `hijoMenor`).
2. Si no alcanza, sube por ancestros y explora ramas "companeras".
3. Como respaldo, busca un ancestro cercano con dos sucesores elegibles.
4. Si no hay libres, repite permitiendo candidatos en carcel.

### Regla adicional por edad

Si el jefe supera los 70 anos, el controlador prioriza transferencia dentro de su propio arbol de descendientes libres antes de aplicar el resto de reglas.

## Linea de sucesion actual (opcion 3)

La opcion "Mostrar linea de sucesion actual (solo vivos)" hace una simulacion:

1. Toma el jefe actual como punto inicial.
2. Simula su salida marcandolo temporalmente como muerto.
3. Recalcula el siguiente jefe repetidamente.
4. Lista primero sucesores vivos y libres.
5. Luego lista vivos en carcel como elegibles de respaldo.
6. Restaura el estado original de `is_dead` al terminar.

Esto evita alterar definitivamente los datos solo para mostrar la proyeccion de sucesion.

## Edicion de miembros (opcion 4)

Permite editar por ID:

- nombre, apellido, genero, edad
- estado de muerte y carcel
- historial de jefatura y jefe actual

Al finalizar:

1. Se limpian enlaces de hijos.
2. Se reconstruye el arbol con los nuevos datos.
3. Se guarda el CSV actualizado.

## Formato del CSV

Cabecera esperada:

`id,name,last_name,gender,age,id_boss,is_dead,in_jail,was_boss,is_boss`

Validaciones aplicadas al cargar:

- Deben existir exactamente 10 columnas por fila.
- `gender` debe ser `H` o `M`.
- `is_dead`, `in_jail`, `was_boss`, `is_boss` deben ser `0` o `1`.
- Campos numericos (`id`, `age`, `id_boss`) deben ser enteros validos.

Si una fila es invalida, se ignora y se muestra advertencia en consola.

## Compilacion

Desde la raiz del proyecto:

```bash
g++ src/main.cpp src/controller/arbol_familia.cpp src/model/gestor_archivo.cpp src/view/interfaz_usuario.cpp -o bin/programa.exe
```

## Ejecucion

Desde la raiz del proyecto:

```bash
./bin/programa.exe
```

En Windows PowerShell tambien puedes usar el script:

```powershell
./run.ps1
```

El script compila y ejecuta. Si existe `entrada.txt`, usa ese archivo como entrada estandar.

## Flujo recomendado de uso

1. Elegir `1` para cargar datos desde CSV.
2. Elegir `3` para revisar la sucesion actual.
3. Elegir `2` para simular cambio de jefe por prision o muerte.
4. Elegir `4` para corregir o actualizar miembros.
5. Revisar el CSV generado con los cambios persistidos.
