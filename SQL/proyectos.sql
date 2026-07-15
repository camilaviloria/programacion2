-- 1. Crear la segunda tabla
CREATE TABLE proyectos (
    id_proyecto INTEGER PRIMARY KEY,
    nombre_proyecto TEXT,
    departamento_encargado TEXT,
    presupuesto INT
);

-- 2. Insertar registros en la nueva tabla
INSERT INTO proyectos (nombre_proyecto, departamento_encargado, presupuesto) VALUES ('Sistema Biométrico', 'TI', 12000);
INSERT INTO proyectos (nombre_proyecto, departamento_encargado, presupuesto) VALUES ('Campaña Redes', 'Ventas', 5000);
INSERT INTO proyectos (nombre_proyecto, departamento_encargado, presupuesto) VALUES ('Migración Cloud', 'TI', 25000);

SELECT * FROM proyectos;

-- IMPLICITA 

SELECT COUNT(*) AS total_proyectos, SUM(presupuesto) AS total_presupuesto, AVG(presupuesto) AS promedio_presupuesto
FROM proyectos;

--- EXPLICITA

SELECT departamento_encargado, COUNT(*) AS total_proyectos, SUM(presupuesto) AS total_presupuesto
FROM proyectos
GROUP BY departamento_encargado;