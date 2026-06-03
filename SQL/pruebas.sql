-- Crear la tabla
CREATE TABLE empleados (
    id INTEGER PRIMARY KEY,
    nombre TEXT,
    departamento TEXT,
    salario INT
);

-- Insertar los datos
INSERT INTO empleados (nombre, departamento, salario) VALUES ('Ana', 'Ventas', 3000);
INSERT INTO empleados (nombre, departamento, salario) VALUES ('Luis', 'Ventas', 3500);
INSERT INTO empleados (nombre, departamento, salario) VALUES ('María', 'TI', 4000);
INSERT INTO empleados (nombre, departamento, salario) VALUES ('Carlos', 'TI', 4500);

-- 1. PROBAR AGRUPACIÓN IMPLÍCITA (Toda la tabla junta)
SELECT COUNT(*) AS total_empleados, SUM(salario) AS suma_salarios, AVG(salario) AS promedio
FROM empleados;

-- 2. PROBAR AGRUPACIÓN EXPLÍCITA (Separado por departamento)
SELECT departamento, COUNT(*) AS total, SUM(salario) AS total_salario
FROM empleados
GROUP BY departamento;

SELECT * FROM empleados;