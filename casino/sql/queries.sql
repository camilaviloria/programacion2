-- 1. Volumen de Apuestas por Casino
SELECT 
    c.nombre_legal, 
    SUM(a.monto_apuesta) AS monto_total
FROM casino.casino c
JOIN casino.centro_apuestas ca ON c.id_casino = ca.id_casino
JOIN casino.apuesta a ON ca.id_centro = a.id_centro
GROUP BY c.id_casino, c.nombre_legal
ORDER BY monto_total DESC;

-- 2. Participantes Populares
SELECT 
    p.nombre_oficial, 
    COUNT(ap.id_apuesta) AS total_apuestas
FROM casino.participante p
JOIN casino.apuesta_participante ap ON p.id_participante = ap.id_participante
GROUP BY p.id_participante, p.nombre_oficial
HAVING COUNT(ap.id_apuesta) > 100;

-- 3. Actividad de Clientes (Carreras > 500$)
SELECT 
    cl.nombre, 
    SUM(a.monto_apuesta) AS total_invertido
FROM casino.cliente cl
JOIN casino.apuesta a ON cl.id_cliente = a.id_cliente
JOIN casino.evento e ON a.id_evento = e.id_evento
WHERE e.categoria = 'Carreras'
GROUP BY cl.id_cliente, cl.nombre
HAVING SUM(a.monto_apuesta) > 500;

-- 4. Centros de Apuestas (Las Vegas Strip / Olimpiadas)
SELECT DISTINCT 
    ca.nro_local, 
    ca.calle
FROM casino.centro_apuestas ca
JOIN casino.apuesta a ON ca.id_centro = a.id_centro
JOIN casino.evento e ON a.id_evento = e.id_evento
WHERE ca.calle = 'Las Vegas Strip' 
  AND e.categoria = 'Olimpiadas'
ORDER BY ca.nro_local;

-- 5. Rendimiento por Evento
SELECT 
    id_evento, 
    AVG(monto_apuesta) AS promedio_apuesta
FROM casino.apuesta
GROUP BY id_evento
HAVING AVG(monto_apuesta) > 50
ORDER BY promedio_apuesta DESC;