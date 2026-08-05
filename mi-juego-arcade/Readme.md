# 🐍 Snake Arcade Game (MVC)

Implementación del clásico juego **Snake** desarrollada en Java utilizando la biblioteca gráfica **Swing** y aplicando el patrón de arquitectura **Model-View-Controller (MVC)**.

---

## 📋 Descripción del Proyecto

El juego recrea la dinámica arcade clásica en un tablero grid dinámico. El jugador controla la serpiente para comer alimentos, aumentar su longitud y acumular puntos, evitando chocar contra las paredes del mapa o con su propio cuerpo.

### Características Principales
* **Arquitectura MVC:** Separación limpia de responsabilidades entre la vista (`view`), la lógica del dominio (`model`) y el controlador de entrada/bucle (`controller`).
* **Interfaz Swing:** Gráficos e interactividad en tiempo real manejados sobre el *Event Dispatch Thread* (EDT).
* **Persistencia de Puntuaciones:** Registro y gestión de los mejores puntajes del jugador.

---

## 🛠️ Requisitos del Sistema

* **Java Development Kit (JDK):** Versión 21 LTS (Recomendada).
* **Entorno de Desarrollo:** Visual Studio Code o Windsurf.
* **Extensiones Sugeridas:** Extension Pack for Java, Code Runner.

---

## 📁 Estructura del Repositorio

```text
.
├── bin/                      # Archivos de código compilado (.class)
├── src/                      # Código fuente del proyecto
│   ├── controller/           # Controladores de entrada de teclado y ciclo de juego
│   ├── model/                # Lógica del juego, estado de la serpiente y puntajes
│   ├── view/                 # Componentes visuales y ventanas Swing
│   └── Main.java             # Punto de entrada de la aplicación
├── .gitignore
└── README.md
🚀 Compilación y Ejecución
Opción 1: Mediante la extensión Code Runner (Recomendado para VS Code / Windsurf)
Puedes configurar Code Runner para compilar recursivamente la estructura MVC dentro del directorio bin/ y ejecutar la aplicación de forma automática.

1. Configuración de settings.json
Abre la paleta de comandos (Cmd + Shift + P en macOS / Ctrl + Shift + P en Windows/Linux), selecciona Preferences: Open User Settings (JSON) y añade estas propiedades dentro del objeto principal:

JSON


"code-runner.executorMap": {
    "java": "cd $workspaceRoot && find src -name '*.java' | xargs javac -d bin && java -cp bin Main"
},
"code-runner.runInTerminal": true,
"code-runner.saveAllFilesBeforeRun": true
2. Ejecutar el Proyecto
Con la configuración guardada, abre el archivo src/Main.java y ejecuta el juego usando cualquiera de estos métodos:

Atajo de teclado:

macOS: Control + Option + N

Windows / Linux: Ctrl + Alt + N

Interfaz: Haz clic en el botón Play (▶️) situado en la esquina superior derecha del editor.

Opción 2: Desde la Terminal
Si prefieres ejecutar el proyecto de forma manual desde la consola del sistema:

Clonar el repositorio:

Bash

git clone [https://github.com/camilaviloria/mi-juego-arcade.git](https://github.com/camilaviloria/mi-juego-arcade.git)
cd mi-juego-arcade
Compilar las clases:

Bash

find src -name "*.java" | xargs javac -d bin
Ejecutar la aplicación:

Bash


java -cp bin Main
🎮 Controles del Juego
Flechas de Dirección / WASD: Mover la serpiente (Arriba, Abajo, Izquierda, Derecha).