# 📊 CSV Manager Library

Una librería modular en Java diseñada para la carga, manipulación, procesamiento y visualización de archivos estructurados mediante delimitadores (como archivos CSV o de texto plano). 

El núcleo central del proyecto está estructurado bajo principios de diseño que garantizan el desacoplamiento total entre el almacenamiento de datos, las estrategias de entrada/salida y las reglas de negocio. Esto permite expandir todas las capacidades de la aplicación de manera externa sin alterar en absoluto el código base original.

---

## 🛠️ Especificaciones de la Arquitectura

La librería basa su flexibilidad en cuatro abstracciones principales que dividen de manera estricta las responsabilidades del sistema:

### 1. Gestión de Datos (`CsvTable`)
* **Responsabilidad:** Define el contrato para la abstracción del almacenamiento bidimensional de la información.
* **Operaciones Estructuradas:** * Inserción dinámica de registros completos (filas).
  * Eliminación de registros específicos mediante índices de posicionamiento.
  * Incorporación de nuevos campos verticales (columnas) con soporte de homogeneización de datos faltantes.
  * Remoción de columnas completas a lo largo de toda la matriz de datos.
  * Acceso seguro a la estructura interna bidimensional para su posterior procesamiento.

### 2. Estrategia de Lectura (`CsvReader`)
* **Responsabilidad:** Abstrae el mecanismo por el cual los datos son parseados e introducidos al sistema.
* **Características:** Permite definir implementaciones concretas orientadas a cualquier origen de datos o codificación de caracteres, aislando por completo la lógica del lector (como el manejo del delimitador por comas, punto y coma, o tabuladores) del resto de la aplicación.

### 3. Inyección de Reglas de Negocio (`CsvModifier`)
* **Responsabilidad:** Actúa como el punto de extensión principal para la manipulación y transformación de datos "al vuelo".
* **Características:** Cualquier mutación requerida sobre la información (como filtrados por criterios numéricos, transformaciones de texto a mayúsculas/minúsculas, o limpiezas de campos vacíos) se inyecta externamente a través de este contrato, permitiendo aplicar lógica personalizada de manera secuencial.

### 4. Formateo y Visualización de Salida (`CsvPrinter`)
* **Responsabilidad:** Desacopla la representación visual o exportación final de los datos tabulares.
* **Características:** Permite desvincular el destino físico de la salida. Facilita la creación de extensiones que formateen la matriz de datos hacia texto plano en consola, estructuras jerárquicas como objetos JSON, etiquetas HTML para entornos web, o flujos directos hacia nuevos archivos físicos.

---

## 🧩 Filosofía de Extensión (Principio Abierto/Cerrado)

La librería está diseñada para cumplir estrictamente con el principio de **Abierto para la extensión, Cerrado para la modificación**:

* **Código Base Intacto:** El motor o gestor central (`CsvManager`) y la representación por defecto de la tabla de datos (`DefaultCsvTable`) permanecen inmutables ante nuevos requerimientos de software.
* **Polimorfismo:** Cuando el sistema requiera soportar un nuevo formato de archivo, una transformación específica sobre las celdas, o una nueva interfaz de salida para el usuario, el desarrollador simplemente debe crear una clase nueva que implemente la interfaz correspondiente e inyectarla en tiempo de ejecución.