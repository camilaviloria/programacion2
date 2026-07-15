-- ============================================================
--  CASINO DATABASE - PostgreSQL Schema
--  Normalizado hasta la 4ta Forma Normal (4FN)
-- ============================================================

-- ============================================================
-- ANÁLISIS DE NORMALIZACIÓN
-- 1FN: Todos los atributos son atómicos, sin grupos repetidos.
-- 2FN: Sin dependencias parciales (todas las tablas con PK simple
--       o dependencias completas en PK compuestas).
-- 3FN: Sin dependencias transitivas. Ej: Dirección extraída a
--       tabla propia para Casino y Centro de apuestas.
-- 4FN: Sin dependencias multivaluadas independientes. Ej:
--       Contactos de Casino separados; Uniformes de Equipo separados.
-- ============================================================

-- Limpiar si existe
DROP SCHEMA IF EXISTS casino CASCADE;
CREATE SCHEMA casino;
SET search_path = casino;

-- ============================================================
-- DOMINIO / CATÁLOGOS
-- ============================================================

CREATE TABLE divisa (
    id_divisa     SERIAL PRIMARY KEY,
    codigo        CHAR(3)      NOT NULL UNIQUE,   -- USD, VES, EUR…
    nombre        VARCHAR(60)  NOT NULL
);

CREATE TABLE metodo_pago (
    id_metodo     SERIAL PRIMARY KEY,
    descripcion   VARCHAR(80)  NOT NULL UNIQUE
);

-- ============================================================
-- CASINO
-- ============================================================

CREATE TABLE casino (
    id_casino           SERIAL PRIMARY KEY,
    rif                 VARCHAR(20)  NOT NULL UNIQUE,
    nombre_legal        VARCHAR(120) NOT NULL,
    nombre_comercial    VARCHAR(120),
    razon_social        VARCHAR(120),
    licencia            VARCHAR(60),
    cuenta_central      VARCHAR(40),
    fondo_garantia      NUMERIC(18,2),
    sitio_web           VARCHAR(200)
);

-- 4FN: Contactos separados (multivaluado independiente)
CREATE TABLE casino_contacto (
    id_contacto   SERIAL PRIMARY KEY,
    id_casino     INT          NOT NULL REFERENCES casino(id_casino) ON DELETE CASCADE,
    tipo          VARCHAR(40)  NOT NULL,   -- telefono, email, fax…
    valor         VARCHAR(120) NOT NULL
);

-- 3FN: Dirección fiscal en tabla propia (evita transitiva ciudad->estado)
CREATE TABLE casino_direccion_fiscal (
    id_casino     INT          PRIMARY KEY REFERENCES casino(id_casino) ON DELETE CASCADE,
    calle         VARCHAR(200),
    ciudad        VARCHAR(80),
    estado        VARCHAR(80),
    codigo_postal VARCHAR(20)
);

-- ============================================================
-- GERENTE (referenciado por Centro de apuestas)
-- ============================================================

CREATE TABLE gerente (
    id_gerente    SERIAL PRIMARY KEY,
    nombre        VARCHAR(120) NOT NULL,
    cedula        VARCHAR(20)  UNIQUE
);

-- ============================================================
-- CENTRO DE APUESTAS
-- ============================================================

CREATE TABLE centro_apuestas (
    id_centro           SERIAL PRIMARY KEY,
    id_casino           INT          NOT NULL REFERENCES casino(id_casino),
    id_gerente          INT          REFERENCES gerente(id_gerente),
    nro_local           VARCHAR(20),
    capacidad_maxima    INT,
    ip_servidor         VARCHAR(45),
    fondo               NUMERIC(18,2),
    turno               VARCHAR(40),
    estado_operativo    VARCHAR(40),
    -- Dirección propia (3FN)
    calle               VARCHAR(200),
    ciudad              VARCHAR(80),
    estado_dir          VARCHAR(80),
    codigo_postal       VARCHAR(20)
);

-- ============================================================
-- CLIENTE
-- ============================================================

CREATE TABLE cliente (
    id_cliente              SERIAL PRIMARY KEY,
    cedula                  VARCHAR(20)  NOT NULL UNIQUE,
    primer_nombre           VARCHAR(60)  NOT NULL,
    apellido                VARCHAR(60)  NOT NULL,
    nombre                  VARCHAR(120) GENERATED ALWAYS AS (primer_nombre || ' ' || apellido) STORED,
    telefono                VARCHAR(20),
    correo_electronico      VARCHAR(120),
    saldo_cuenta            NUMERIC(18,2) DEFAULT 0,
    metodo_cobro            VARCHAR(80),
    tipo_cuenta             VARCHAR(40),
    id_metodo_pago          INT REFERENCES metodo_pago(id_metodo),
    plataforma_financiera   VARCHAR(80),
    identificador_cuenta    VARCHAR(80)
);

-- ============================================================
-- TRANSACCIÓN  (superclase)
-- ============================================================

CREATE TABLE transaccion (
    id_transaccion    SERIAL PRIMARY KEY,
    id_cliente        INT          NOT NULL REFERENCES cliente(id_cliente),
    id_centro         INT          NOT NULL REFERENCES centro_apuestas(id_centro),
    id_divisa         INT          NOT NULL REFERENCES divisa(id_divisa),
    id_metodo_pago    INT          REFERENCES metodo_pago(id_metodo),
    monto             NUMERIC(18,2) NOT NULL,
    monto_pagado      NUMERIC(18,2),
    nro_referencia    VARCHAR(60),
    fecha_hora        TIMESTAMPTZ  NOT NULL DEFAULT now()
);

-- Subclase: Pago  (d = disjunto)
CREATE TABLE pago (
    id_transaccion    INT PRIMARY KEY REFERENCES transaccion(id_transaccion) ON DELETE CASCADE,
    origen_fondo      VARCHAR(80),
    nro_recibo        VARCHAR(60)
);

-- ============================================================
-- PREMIO
-- ============================================================

CREATE TABLE premio (
    id_premio             SERIAL PRIMARY KEY,
    id_centro             INT          NOT NULL REFERENCES centro_apuestas(id_centro),
    autorizacion          VARCHAR(80),
    comision_casa         NUMERIC(5,2),
    retencion_impuesto    NUMERIC(5,2)
);

-- ============================================================
-- EVENTO
-- ============================================================

CREATE TABLE evento (
    id_evento         SERIAL PRIMARY KEY,
    id_casino         INT          NOT NULL REFERENCES casino(id_casino),
    categoria         VARCHAR(80),
    fecha_hora_inicio TIMESTAMPTZ  NOT NULL,
    estado            VARCHAR(40),
    clima             VARCHAR(80),
    -- 3FN: año/mes/dia son derivados de fecha_hora_inicio; los eliminamos
    -- Atributo calculado: hora se extrae de fecha_hora_inicio
    fecha_publicacion DATE
);

-- ============================================================
-- RESULTADO
-- ============================================================

CREATE TABLE resultado (
    id_resultado      SERIAL PRIMARY KEY,
    id_evento         INT          NOT NULL UNIQUE REFERENCES evento(id_evento),
    puntaje_final     VARCHAR(40),
    posicion_final    VARCHAR(40)
);

-- ============================================================
-- JUGADOR
-- ============================================================

CREATE TABLE jugador (
    id_jugador    SERIAL PRIMARY KEY,
    posicion      VARCHAR(60),
    peso          NUMERIC(6,2),
    estatura      NUMERIC(5,2),
    estado_salud  VARCHAR(60),
    edad          INT,
    dorsal        VARCHAR(10)
);

-- ============================================================
-- ANIMAL  (carreras de animales)
-- ============================================================

CREATE TABLE animal (
    id_animal             SERIAL PRIMARY KEY,
    especie               VARCHAR(60),
    raza                  VARCHAR(60),
    genero                CHAR(1),
    edad                  INT,
    peso                  NUMERIC(6,2),
    establo               VARCHAR(80),
    estado_salud          VARCHAR(60),
    linaje                VARCHAR(200)
);

-- 4FN: historial_carreras es multivaluado independiente
CREATE TABLE animal_historial_carrera (
    id_historial  SERIAL PRIMARY KEY,
    id_animal     INT  NOT NULL REFERENCES animal(id_animal) ON DELETE CASCADE,
    descripcion   VARCHAR(300),
    fecha         DATE
);

-- ============================================================
-- EQUIPO
-- ============================================================

CREATE TABLE equipo (
    id_equipo         SERIAL PRIMARY KEY,
    nombre            VARCHAR(120) NOT NULL,
    ciudad_sede       VARCHAR(80),
    director_tecnico  VARCHAR(120),
    escudo_url        VARCHAR(300),
    fecha_fundacion   DATE,
    racha_actual      VARCHAR(40)
);

-- 4FN: Uniformes son multivaluado independiente
CREATE TABLE equipo_uniforme (
    id_uniforme   SERIAL PRIMARY KEY,
    id_equipo     INT          NOT NULL REFERENCES equipo(id_equipo) ON DELETE CASCADE,
    tipo          VARCHAR(40),    -- local, visitante, tercero
    descripcion   VARCHAR(200),
    color_primario VARCHAR(40),
    temporada     VARCHAR(20)
);

-- ============================================================
-- PARTICIPANTES  (generalización: Jugador | Animal | Equipo)
-- Se usa patrón de herencia con tabla puente
-- ============================================================

CREATE TABLE participante (
    id_participante   SERIAL PRIMARY KEY,
    tipo              VARCHAR(20)  NOT NULL CHECK (tipo IN ('jugador','animal','equipo')),
    id_jugador        INT  REFERENCES jugador(id_jugador),
    id_animal         INT  REFERENCES animal(id_animal),
    id_equipo         INT  REFERENCES equipo(id_equipo),
    nacionalidad      VARCHAR(80),
    nombre_oficial    VARCHAR(120),
    dorsal            VARCHAR(10),
    -- Solo uno de los tres FK debe estar poblado
    CONSTRAINT ck_one_entity CHECK (
        (id_jugador IS NOT NULL)::INT +
        (id_animal  IS NOT NULL)::INT +
        (id_equipo  IS NOT NULL)::INT = 1
    )
);

-- Participante ↔ Evento  (N:M  "Tiene")
CREATE TABLE evento_participante (
    id_evento         INT NOT NULL REFERENCES evento(id_evento),
    id_participante   INT NOT NULL REFERENCES participante(id_participante),
    estado_salud      VARCHAR(60),
    PRIMARY KEY (id_evento, id_participante)
);

-- ============================================================
-- APUESTA  (superclase)
-- ============================================================

CREATE TABLE apuesta (
    id_apuesta        SERIAL PRIMARY KEY,
    id_centro         INT          NOT NULL REFERENCES centro_apuestas(id_centro),
    id_cliente        INT          NOT NULL REFERENCES cliente(id_cliente),
    id_evento         INT          NOT NULL REFERENCES evento(id_evento),
    id_transaccion    INT          REFERENCES transaccion(id_transaccion),
    cuota_base        NUMERIC(8,4),
    monto_apuesta     NUMERIC(18,2) NOT NULL,
    nro_transaccion   VARCHAR(60),
    estado            VARCHAR(40),
    fecha_hora        TIMESTAMPTZ  NOT NULL DEFAULT now()
    -- año/mes/dia/hora son derivados; se eliminan (3FN)
);

-- Subclase: Simple  (d = disjunto)
CREATE TABLE apuesta_simple (
    id_apuesta    INT PRIMARY KEY REFERENCES apuesta(id_apuesta) ON DELETE CASCADE,
    seleccion     VARCHAR(200),
    pronostico    VARCHAR(200)
);

-- Subclase: Combinada  (d = disjunto)
CREATE TABLE apuesta_combinada (
    id_apuesta      INT PRIMARY KEY REFERENCES apuesta(id_apuesta) ON DELETE CASCADE,
    cuota_total     NUMERIC(8,4),
    multiplicador   NUMERIC(8,4)
);

-- Subclase: Handicap  (d = disjunto)
CREATE TABLE apuesta_handicap (
    id_apuesta          INT PRIMARY KEY REFERENCES apuesta(id_apuesta) ON DELETE CASCADE,
    tipo                VARCHAR(60),
    ventaja_puntos      NUMERIC(6,2),
    direccion           VARCHAR(40),    -- favor o en contra
    linea_juego         NUMERIC(8,4)
);

-- ============================================================
-- APUESTA ↔ PARTICIPANTE  ("Elige" N:M)
-- ============================================================

CREATE TABLE apuesta_participante (
    id_apuesta        INT NOT NULL REFERENCES apuesta(id_apuesta),
    id_participante   INT NOT NULL REFERENCES participante(id_participante),
    PRIMARY KEY (id_apuesta, id_participante)
);

-- ============================================================
-- RESULTADO ↔ PARTICIPANTE  ("Determina" 1:N)
-- ============================================================

CREATE TABLE resultado_participante (
    id_resultado      INT NOT NULL REFERENCES resultado(id_resultado),
    id_participante   INT NOT NULL REFERENCES participante(id_participante),
    posicion          INT,
    puntaje           VARCHAR(40),
    PRIMARY KEY (id_resultado, id_participante)
);

-- ============================================================
-- ÍNDICES ÚTILES
-- ============================================================

CREATE INDEX idx_apuesta_cliente   ON apuesta(id_cliente);
CREATE INDEX idx_apuesta_evento    ON apuesta(id_evento);
CREATE INDEX idx_apuesta_centro    ON apuesta(id_centro);
CREATE INDEX idx_transaccion_cli   ON transaccion(id_cliente);
CREATE INDEX idx_ev_part_evento    ON evento_participante(id_evento);
CREATE INDEX idx_ev_part_part      ON evento_participante(id_participante);