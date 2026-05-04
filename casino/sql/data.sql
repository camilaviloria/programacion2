-- ============================================================
--  CASINO DATABASE - Datos de prueba
-- ============================================================

SET search_path = casino;

-- ============================================================
-- DIVISAS
-- ============================================================
INSERT INTO divisa (codigo, nombre) VALUES
  ('USD', 'Dólar Estadounidense'),
  ('EUR', 'Euro'),
  ('VES', 'Bolívar Venezolano'),
  ('GBP', 'Libra Esterlina'),
  ('BRL', 'Real Brasileño'),
  ('COP', 'Peso Colombiano'),
  ('ARS', 'Peso Argentino'),
  ('MXN', 'Peso Mexicano'),
  ('CLP', 'Peso Chileno'),
  ('PEN', 'Sol Peruano'),
  ('CAD', 'Dólar Canadiense'),
  ('JPY', 'Yen Japonés');

-- ============================================================
-- MÉTODOS DE PAGO
-- ============================================================
INSERT INTO metodo_pago (descripcion) VALUES
  ('Efectivo'),
  ('Transferencia Bancaria'),
  ('Tarjeta de Crédito'),
  ('Tarjeta de Débito'),
  ('PayPal'),
  ('Criptomoneda'),
  ('Pago Móvil'),
  ('Zelle'),
  ('Binance Pay'),
  ('Cheque'),
  ('Western Union'),
  ('MoneyGram');

-- ============================================================
-- CASINO
-- ============================================================
INSERT INTO casino (rif, nombre_legal, nombre_comercial, razon_social, licencia, cuenta_central, fondo_garantia, sitio_web) VALUES
  ('J-12345678-9', 'Grand Fortune C.A.',         'Grand Fortune Casino',    'Grand Fortune C.A.',      'LIC-001-2020', '0102-1234-56-0123456789', 500000.00, 'https://grandffortune.com'),
  ('J-23456789-0', 'Royal Bet Investments C.A.', 'Royal Bet',               'Royal Bet Investments',   'LIC-002-2020', '0105-2345-67-0234567890', 750000.00, 'https://royalbet.com'),
  ('J-34567890-1', 'Lucky Star Entretenimiento', 'Lucky Star',              'Lucky Star E. C.A.',      'LIC-003-2019', '0108-3456-78-0345678901', 300000.00, 'https://luckystar.com'),
  ('J-45678901-2', 'Diamante Negro C.A.',        'Diamante Negro Casino',   'Diamante Negro C.A.',     'LIC-004-2021', '0134-4567-89-0456789012', 450000.00, 'https://diamanteneg.com'),
  ('J-56789012-3', 'El Dorado Gaming S.A.',      'El Dorado',               'El Dorado Gaming S.A.',   'LIC-005-2018', '0175-5678-90-0567890123', 600000.00, 'https://eldoradogaming.com'),
  ('J-67890123-4', 'Ases & Reyes C.A.',          'Ases & Reyes',            'Ases & Reyes C.A.',       'LIC-006-2022', '0102-6789-01-0678901234', 250000.00, 'https://asesyreyes.com'),
  ('J-78901234-5', 'Fortuna Global C.A.',        'Fortuna Global',          'Fortuna Global C.A.',     'LIC-007-2021', '0105-7890-12-0789012345', 820000.00, 'https://fortunaglobal.com'),
  ('J-89012345-6', 'Casino Imperial S.A.',       'Imperial Casino',         'Casino Imperial S.A.',    'LIC-008-2019', '0108-8901-23-0890123456', 1000000.00,'https://imperialcasino.com'),
  ('J-90123456-7', 'Vegas del Sur C.A.',         'Vegas del Sur',           'Vegas del Sur C.A.',      'LIC-009-2020', '0134-9012-34-0901234567', 390000.00, 'https://vegasdelsur.com'),
  ('J-01234567-8', 'Caribe Bets C.A.',           'Caribe Bets',             'Caribe Bets C.A.',        'LIC-010-2023', '0175-0123-45-0012345678', 475000.00, 'https://caribebets.com'),
  ('J-11223344-5', 'Platino Bets S.A.',          'Platino Bets',            'Platino Bets S.A.',       'LIC-011-2022', '0102-1122-33-0112233445', 560000.00, 'https://platinobets.com');

-- ============================================================
-- CASINO CONTACTOS
-- ============================================================
INSERT INTO casino_contacto (id_casino, tipo, valor) VALUES
  (1, 'telefono', '+58-212-555-0101'), (1, 'email', 'info@grandfortune.com'),
  (2, 'telefono', '+58-212-555-0202'), (2, 'email', 'contacto@royalbet.com'),
  (3, 'telefono', '+58-241-555-0303'), (3, 'email', 'info@luckystar.com'),
  (4, 'telefono', '+58-243-555-0404'), (4, 'email', 'admin@diamanteneg.com'),
  (5, 'telefono', '+58-261-555-0505'), (5, 'email', 'hola@eldoradogaming.com'),
  (6, 'telefono', '+58-251-555-0606'), (6, 'email', 'soporte@asesyreyes.com'),
  (7, 'telefono', '+58-212-555-0707'), (7, 'email', 'info@fortunaglobal.com'),
  (8, 'telefono', '+58-212-555-0808'), (8, 'email', 'reservas@imperialcasino.com'),
  (9, 'telefono', '+58-274-555-0909'), (9, 'email', 'info@vegasdelsur.com'),
  (10,'telefono', '+58-293-555-1010'), (10,'email', 'hola@caribebets.com'),
  (11,'telefono', '+58-212-555-1111'), (11,'email', 'info@platinobets.com');

-- ============================================================
-- CASINO DIRECCION FISCAL
-- ============================================================
INSERT INTO casino_direccion_fiscal (id_casino, calle, ciudad, estado, codigo_postal) VALUES
  (1,  'Av. Principal 100',    'Caracas',      'Distrito Capital', '1010'),
  (2,  'Calle 5 #200',         'Caracas',      'Distrito Capital', '1020'),
  (3,  'Av. Bolívar 301',      'Valencia',     'Carabobo',         '2001'),
  (4,  'Urb. Las Acacias 15',  'Maracay',      'Aragua',           '2101'),
  (5,  'Calle 72 #400',        'Maracaibo',    'Zulia',            '4001'),
  (6,  'Av. Los Jabillos 55',  'Barquisimeto', 'Lara',             '3001'),
  (7,  'C.C. Sambil Local 3',  'Caracas',      'Distrito Capital', '1060'),
  (8,  'Av. Miranda 900',      'Caracas',      'Distrito Capital', '1040'),
  (9,  'Calle Real 10',        'San Cristóbal','Táchira',          '5001'),
  (10, 'Av. Intercomunal 22',  'Barcelona',    'Anzoátegui',       '6001'),
  (11, 'Urb. Prado Humboldt',  'Caracas',      'Distrito Capital', '1080');

-- ============================================================
-- GERENTES
-- ============================================================
INSERT INTO gerente (nombre, cedula) VALUES
  ('Carlos Mendoza',    'V-10123456'),
  ('Ana Rodríguez',     'V-11234567'),
  ('Pedro González',    'V-12345678'),
  ('María López',       'V-13456789'),
  ('José Ramírez',      'V-14567890'),
  ('Laura Martínez',    'V-15678901'),
  ('Roberto Díaz',      'V-16789012'),
  ('Sofía Hernández',   'V-17890123'),
  ('Miguel Torres',     'V-18901234'),
  ('Andrea Castillo',   'V-19012345'),
  ('Fernando Morales',  'V-20123456'),
  ('Valentina Reyes',   'V-21234567');

-- ============================================================
-- CENTROS DE APUESTAS
-- ============================================================
INSERT INTO centro_apuestas (id_casino, id_gerente, nro_local, capacidad_maxima, ip_servidor, fondo, turno, estado_operativo, calle, ciudad, estado_dir, codigo_postal) VALUES
  (1,  1,  'LOC-001', 200, '192.168.1.10',  80000.00, 'Mañana',  'Activo',   'Av. Principal 100',    'Caracas',      'Distrito Capital', '1010'),
  (1,  2,  'LOC-002', 150, '192.168.1.11',  60000.00, 'Tarde',   'Activo',   'Av. Principal 102',    'Caracas',      'Distrito Capital', '1010'),
  (2,  3,  'LOC-003', 300, '192.168.2.10',  120000.00,'Noche',   'Activo',   'Calle 5 #200',         'Caracas',      'Distrito Capital', '1020'),
  (3,  4,  'LOC-004', 180, '192.168.3.10',  70000.00, 'Mañana',  'Activo',   'Av. Bolívar 301',      'Valencia',     'Carabobo',         '2001'),
  (4,  5,  'LOC-005', 220, '192.168.4.10',  90000.00, 'Tarde',   'Activo',   'Urb. Las Acacias 15',  'Maracay',      'Aragua',           '2101'),
  (5,  6,  'LOC-006', 400, '192.168.5.10',  150000.00,'24h',     'Activo',   'Calle 72 #400',        'Maracaibo',    'Zulia',            '4001'),
  (6,  7,  'LOC-007', 100, '192.168.6.10',  40000.00, 'Mañana',  'Inactivo', 'Av. Los Jabillos 55',  'Barquisimeto', 'Lara',             '3001'),
  (7,  8,  'LOC-008', 250, '192.168.7.10',  100000.00,'Noche',   'Activo',   'C.C. Sambil Local 3',  'Caracas',      'Distrito Capital', '1060'),
  (8,  9,  'LOC-009', 500, '192.168.8.10',  200000.00,'24h',     'Activo',   'Av. Miranda 900',      'Caracas',      'Distrito Capital', '1040'),
  (9,  10, 'LOC-010', 160, '192.168.9.10',  65000.00, 'Tarde',   'Activo',   'Calle Real 10',        'San Cristóbal','Táchira',          '5001'),
  (10, 11, 'LOC-011', 130, '192.168.10.10', 52000.00, 'Mañana',  'Activo',   'Av. Intercomunal 22',  'Barcelona',    'Anzoátegui',       '6001'),
  (11, 12, 'LOC-012', 280, '192.168.11.10', 110000.00,'24h',     'Activo',   'Urb. Prado Humboldt',  'Caracas',      'Distrito Capital', '1080');

-- ============================================================
-- CLIENTES
-- ============================================================
INSERT INTO cliente (cedula, primer_nombre, apellido, telefono, correo_electronico, saldo_cuenta, metodo_cobro, tipo_cuenta, id_metodo_pago, plataforma_financiera, identificador_cuenta) VALUES
  ('V-20001111', 'Luis',      'Pérez',     '+58-414-1001111', 'luis.perez@email.com',      1500.00, 'Transferencia', 'Corriente', 2, 'Mercantil',   '0105-001-111'),
  ('V-20002222', 'Carmen',    'Suárez',    '+58-424-2002222', 'carmen.s@email.com',        800.00,  'PayPal',        'Ahorro',    5, 'PayPal',      'carmen.s@email.com'),
  ('V-20003333', 'Jorge',     'Vargas',    '+58-416-3003333', 'jorge.v@email.com',         3200.00, 'Criptomoneda',  'Cripto',    6, 'Binance',     '1A2B3C4D5E'),
  ('V-20004444', 'Patricia',  'Núñez',     '+58-412-4004444', 'patricia.n@email.com',      500.00,  'Efectivo',      'Corriente', 1, 'Banesco',     '0134-004-444'),
  ('V-20005555', 'Ricardo',   'Moreno',    '+58-426-5005555', 'r.moreno@email.com',        7000.00, 'Zelle',         'Corriente', 8, 'Bank of America','ricardo@email.com'),
  ('V-20006666', 'Alejandra', 'Castro',    '+58-414-6006666', 'ale.castro@email.com',      1200.00, 'Pago Móvil',    'Corriente', 7, 'Venezuela',   '04146006666'),
  ('V-20007777', 'Andrés',    'Blanco',    '+58-424-7007777', 'andres.b@email.com',        9500.00, 'Transferencia', 'Ahorro',    2, 'Provincial',  '0108-007-777'),
  ('V-20008888', 'Daniela',   'Rojas',     '+58-416-8008888', 'dani.r@email.com',          450.00,  'Tarjeta',       'Débito',    4, 'BBVA',        '4111-8888'),
  ('V-20009999', 'Fernando',  'Salcedo',   '+58-412-9009999', 'f.salcedo@email.com',       2800.00, 'Transferencia', 'Corriente', 2, 'Mercantil',   '0105-009-999'),
  ('V-20010000', 'Gabriela',  'Méndez',    '+58-426-1001000', 'gabi.m@email.com',          600.00,  'Binance Pay',   'Cripto',    9, 'Binance',     'GABI10000XYZ'),
  ('V-20011111', 'Héctor',    'Ibarra',    '+58-414-1011111', 'h.ibarra@email.com',        3600.00, 'Zelle',         'Corriente', 8, 'Chase',       'hector@email.com'),
  ('V-20012222', 'Isabel',    'Fuentes',   '+58-424-1021222', 'isa.f@email.com',           150.00,  'Efectivo',      'Corriente', 1, 'BNC',         '0191-012-222');

-- ============================================================
-- TRANSACCIONES
-- ============================================================
INSERT INTO transaccion (id_cliente, id_centro, id_divisa, id_metodo_pago, monto, monto_pagado, nro_referencia, fecha_hora) VALUES
  (1,  1, 1, 2, 500.00,  500.00,  'REF-0001', '2024-01-10 10:30:00'),
  (2,  1, 1, 5, 200.00,  200.00,  'REF-0002', '2024-01-11 11:00:00'),
  (3,  3, 1, 6, 1000.00, 1000.00, 'REF-0003', '2024-01-12 14:15:00'),
  (4,  4, 1, 1, 150.00,  150.00,  'REF-0004', '2024-01-13 09:45:00'),
  (5,  6, 1, 8, 3000.00, 3000.00, 'REF-0005', '2024-01-14 16:20:00'),
  (6,  2, 1, 7, 400.00,  400.00,  'REF-0006', '2024-01-15 13:00:00'),
  (7,  8, 1, 2, 2500.00, 2500.00, 'REF-0007', '2024-01-16 20:30:00'),
  (8,  5, 1, 4, 100.00,  100.00,  'REF-0008', '2024-01-17 08:00:00'),
  (9,  9, 1, 2, 800.00,  800.00,  'REF-0009', '2024-01-18 17:45:00'),
  (10, 11,1, 9, 250.00,  250.00,  'REF-0010', '2024-01-19 12:10:00'),
  (11, 12,1, 8, 1500.00, 1500.00, 'REF-0011', '2024-01-20 21:00:00'),
  (12, 10,1, 1, 75.00,   75.00,   'REF-0012', '2024-01-21 10:00:00');

-- ============================================================
-- PAGOS (subclase de Transacción)
-- ============================================================
INSERT INTO pago (id_transaccion, origen_fondo, nro_recibo) VALUES
  (1,  'Saldo cuenta',    'REC-001'),
  (2,  'PayPal personal', 'REC-002'),
  (3,  'Wallet crypto',   'REC-003'),
  (4,  'Efectivo físico', 'REC-004'),
  (5,  'Cuenta bancaria', 'REC-005'),
  (6,  'Pago móvil',      'REC-006'),
  (7,  'Cuenta ahorro',   'REC-007'),
  (8,  'Tarjeta débito',  'REC-008'),
  (9,  'Cuenta corriente','REC-009'),
  (10, 'Binance wallet',  'REC-010'),
  (11, 'Zelle transfer',  'REC-011'),
  (12, 'Efectivo físico', 'REC-012');

-- ============================================================
-- PREMIOS
-- ============================================================
INSERT INTO premio (id_centro, autorizacion, comision_casa, retencion_impuesto) VALUES
  (1, 'AUT-001', 5.00, 3.00),
  (2, 'AUT-002', 5.00, 3.00),
  (3, 'AUT-003', 4.50, 2.50),
  (4, 'AUT-004', 5.00, 3.00),
  (5, 'AUT-005', 6.00, 3.50),
  (6, 'AUT-006', 4.00, 2.00),
  (7, 'AUT-007', 5.50, 3.00),
  (8, 'AUT-008', 5.00, 3.00),
  (9, 'AUT-009', 4.50, 2.50),
  (10,'AUT-010', 5.00, 3.00),
  (11,'AUT-011', 4.00, 2.00),
  (12,'AUT-012', 6.00, 4.00);

-- ============================================================
-- EVENTOS
-- ============================================================
INSERT INTO evento (id_casino, categoria, fecha_hora_inicio, estado, clima, fecha_publicacion) VALUES
  (1, 'Fútbol',        '2024-02-01 15:00:00', 'Finalizado',  'Soleado',   '2024-01-25'),
  (1, 'Baloncesto',    '2024-02-05 18:00:00', 'Finalizado',  'Nublado',   '2024-01-29'),
  (2, 'Béisbol',       '2024-02-10 14:00:00', 'Finalizado',  'Soleado',   '2024-02-04'),
  (3, 'Tenis',         '2024-02-15 10:00:00', 'Finalizado',  'Ventoso',   '2024-02-09'),
  (4, 'Carreras',      '2024-02-20 12:00:00', 'Finalizado',  'Soleado',   '2024-02-14'),
  (5, 'Fútbol',        '2024-03-01 20:00:00', 'Finalizado',  'Lluvia',    '2024-02-23'),
  (6, 'Boxeo',         '2024-03-05 21:00:00', 'Finalizado',  'Interior',  '2024-02-28'),
  (7, 'Baloncesto',    '2024-03-10 19:00:00', 'Finalizado',  'Soleado',   '2024-03-04'),
  (8, 'Béisbol',       '2024-03-15 15:00:00', 'En curso',    'Soleado',   '2024-03-09'),
  (9, 'Tenis',         '2024-03-20 11:00:00', 'Programado',  'Despejado', '2024-03-14'),
  (10,'Carreras',      '2024-03-25 13:00:00', 'Programado',  'Soleado',   '2024-03-19'),
  (11,'Fútbol Sala',   '2024-03-28 20:00:00', 'Programado',  'Interior',  '2024-03-22');

-- ============================================================
-- RESULTADOS
-- ============================================================
INSERT INTO resultado (id_evento, puntaje_final, posicion_final) VALUES
  (1, '3-1',  '1er lugar: Caracas FC'),
  (2, '98-85','1er lugar: Leones Caracas'),
  (3, '7-4',  '1er lugar: Tigres Aragua'),
  (4, '6-4',  '1er lugar: Carlos Medina'),
  (5, '1er: Relámpago',  '1'),
  (6, '1-0',  '1er lugar: Mineros Guayana'),
  (7, 'KO R5','1er lugar: Boxeador A'),
  (8, '110-95','1er lugar: Trotamundos');

-- ============================================================
-- JUGADORES
-- ============================================================
INSERT INTO jugador (posicion, peso, estatura, estado_salud, edad, dorsal) VALUES
  ('Delantero',    75.5, 1.80, 'Óptimo',    25, '9'),
  ('Portero',      82.0, 1.88, 'Óptimo',    28, '1'),
  ('Defensa',      79.0, 1.82, 'Lesionado', 31, '4'),
  ('Mediocampista',70.0, 1.75, 'Óptimo',    23, '8'),
  ('Pivot',        95.0, 2.01, 'Óptimo',    27, '5'),
  ('Base',         80.0, 1.90, 'Óptimo',    24, '3'),
  ('Alero',        88.0, 1.98, 'Recuperación',29,'7'),
  ('Lanzador',     85.0, 1.87, 'Óptimo',    32, 'N/A'),
  ('Receptor',     90.0, 1.90, 'Óptimo',    26, 'N/A'),
  ('Tenista',      73.0, 1.85, 'Óptimo',    22, 'N/A'),
  ('Boxeador',    78.0,  1.78, 'Óptimo',    30, 'N/A'),
  ('Boxeador',    77.5,  1.76, 'Óptimo',    28, 'N/A');

-- ============================================================
-- ANIMALES
-- ============================================================
INSERT INTO animal (especie, raza, genero, edad, peso, establo, estado_salud, linaje) VALUES
  ('Caballo', 'Pura Sangre',   'M', 4, 520.0, 'Establo Relámpago', 'Óptimo',    'Trueno Negro x Viento Libre'),
  ('Caballo', 'Cuarto de Milla','M',3, 490.0, 'Establo Veloz',     'Óptimo',    'Rayo Veloz x Luna Dorada'),
  ('Caballo', 'Appaloosa',     'H', 5, 505.0, 'Establo Estrella',  'Óptimo',    'Centellas x Mar Sereno'),
  ('Caballo', 'Pura Sangre',   'M', 6, 530.0, 'Establo Tormenta',  'Lesionado', 'Tornado x Cielo Claro'),
  ('Galgo',   'Greyhound',     'M', 3, 30.0,  'Perrera Viento',    'Óptimo',    'Ventisco x Corriente Suave'),
  ('Galgo',   'Greyhound',     'H', 2, 27.0,  'Perrera Rápida',    'Óptimo',    'Relámpago x Brisa Fina'),
  ('Galgo',   'Whippet',       'M', 4, 20.0,  'Perrera Estrella',  'Óptimo',    'Ágil x Luz Veloz'),
  ('Caballo', 'Árabe',         'H', 4, 460.0, 'Establo Desierto',  'Óptimo',    'Sahara x Noche Árabe'),
  ('Caballo', 'Andaluz',       'M', 5, 510.0, 'Establo Ibérico',   'Óptimo',    'Ebro x Flamenco Real'),
  ('Galgo',   'Greyhound',     'H', 3, 28.5,  'Perrera Ráfaga',    'Recuperación','Niebla x Claridad'),
  ('Caballo', 'Pura Sangre',   'M', 3, 498.0, 'Establo Cumbre',    'Óptimo',    'Cima x Horizonte'),
  ('Galgo',   'Borzoi',        'M', 4, 40.0,  'Perrera Siberia',   'Óptimo',    'Nieve x Estepa');

-- ============================================================
-- ANIMAL HISTORIAL CARRERAS
-- ============================================================
INSERT INTO animal_historial_carrera (id_animal, descripcion, fecha) VALUES
  (1, '1er lugar - Gran Premio Caracas 2023',    '2023-05-15'),
  (1, '2do lugar - Clásico Valencia 2023',       '2023-09-20'),
  (2, '1er lugar - Copa Aragua 2023',            '2023-06-10'),
  (3, '3er lugar - Gran Premio Caracas 2023',    '2023-05-15'),
  (4, '1er lugar - Derby Zulia 2022',            '2022-11-30'),
  (5, '1er lugar - Carrera Galgos Caracas 2023', '2023-07-22'),
  (6, '2do lugar - Copa Canina 2023',            '2023-08-14'),
  (7, '1er lugar - Sprint Lara 2023',            '2023-04-05'),
  (8, '2do lugar - Premio Árabe 2023',           '2023-10-01'),
  (9, '1er lugar - Clásico Ibérico 2023',        '2023-11-15'),
  (10,'3er lugar - Copa Galgos 2023',            '2023-09-30'),
  (11,'1er lugar - Gran Premio Zulia 2023',      '2023-12-10');

-- ============================================================
-- EQUIPOS
-- ============================================================
INSERT INTO equipo (nombre, ciudad_sede, director_tecnico, escudo_url, fecha_fundacion, racha_actual) VALUES
  ('Caracas FC',           'Caracas',      'Rafael Silva',     'https://img/cfc.png',   '1998-03-15', 'W3'),
  ('Mineros de Guayana',   'Puerto Ordaz', 'Carlos León',      'https://img/min.png',   '1985-07-20', 'L1'),
  ('Deportivo Táchira',    'San Cristóbal','Pedro Rivas',      'https://img/dep.png',   '1974-05-10', 'W5'),
  ('Zulia FC',             'Maracaibo',    'Jorge Urdaneta',   'https://img/zul.png',   '2003-09-01', 'D2'),
  ('Leones de Caracas',    'Caracas',      'Luis Dorante',     'https://img/leo.png',   '1952-01-01', 'W2'),
  ('Tigres de Aragua',     'Maracay',      'Andrés Giménez',   'https://img/tig.png',   '1969-06-01', 'W1'),
  ('Navegantes del Magallanes','Valencia', 'Omar López',       'https://img/nav.png',   '1946-04-15', 'L2'),
  ('Trotamundos de Carabobo','Valencia',   'Antonio Pérez',    'https://img/tro.png',   '1963-11-01', 'W4'),
  ('Cocodrilos de Caracas','Caracas',      'Simón Castro',     'https://img/coc.png',   '2002-03-20', 'L1'),
  ('Anzoátegui FC',        'Barcelona',    'Eduardo Ferrer',   'https://img/anz.png',   '2009-01-10', 'D1'),
  ('La Guaira FC',         'La Guaira',    'Manuel Díaz',      'https://img/lag.png',   '2007-08-05', 'W2'),
  ('Llaneros de Guanare',  'Guanare',      'Félix Martínez',   'https://img/lla.png',   '2012-02-28', 'L3');

-- ============================================================
-- EQUIPO UNIFORMES
-- ============================================================
INSERT INTO equipo_uniforme (id_equipo, tipo, descripcion, color_primario, temporada) VALUES
  (1, 'Local',    'Camiseta roja con rayas negras', 'Rojo',    '2023-2024'),
  (1, 'Visitante','Camiseta blanca con franja roja','Blanco',  '2023-2024'),
  (2, 'Local',    'Camiseta azul con amarillo',     'Azul',    '2023-2024'),
  (2, 'Visitante','Camiseta blanca con azul',       'Blanco',  '2023-2024'),
  (3, 'Local',    'Camiseta verdinegra',            'Verde',   '2023-2024'),
  (4, 'Local',    'Camiseta azul cielo',            'Azul',    '2023-2024'),
  (5, 'Local',    'Camiseta roja con blanco',       'Rojo',    '2023-2024'),
  (6, 'Local',    'Camiseta naranja y negro',       'Naranja', '2023-2024'),
  (7, 'Local',    'Camiseta azul marino',           'Azul',    '2023-2024'),
  (8, 'Local',    'Camiseta roja con letras',       'Rojo',    '2023-2024'),
  (9, 'Local',    'Camiseta verde y dorado',        'Verde',   '2023-2024'),
  (10,'Local',    'Camiseta granate',               'Granate', '2023-2024');

-- ============================================================
-- PARTICIPANTES
-- ============================================================
INSERT INTO participante (tipo, id_jugador, nombre_oficial, nacionalidad, dorsal) VALUES
  ('jugador', 1,  'Carlos Medina',       'Venezolana', '9'),
  ('jugador', 2,  'Roberto Salas',       'Venezolana', '1'),
  ('jugador', 3,  'Miguel Ángel Pérez',  'Venezolana', '4'),
  ('jugador', 4,  'Andrés Montilla',     'Venezolana', '8'),
  ('jugador', 5,  'Juan Carlos Rivas',   'Venezolana', '5'),
  ('jugador', 6,  'Pedro Bello',         'Venezolana', '3'),
  ('jugador', 7,  'Felipe Araujo',       'Venezolana', '7'),
  ('jugador', 8,  'Ernesto García',      'Venezolana', NULL),
  ('jugador', 9,  'Marcos Herrera',      'Venezolana', NULL),
  ('jugador', 10, 'Sebastián López',     'Venezolana', NULL),
  ('jugador', 11, 'Ramón Fuentes',       'Venezolana', NULL),
  ('jugador', 12, 'Óscar Matute',        'Venezolana', NULL);

INSERT INTO participante (tipo, id_animal, nombre_oficial, nacionalidad, dorsal) VALUES
  ('animal', 1,  'Relámpago del Sur',    'Venezuela', '1'),
  ('animal', 2,  'Viento Veloz',         'Venezuela', '2'),
  ('animal', 3,  'Estrella de Mar',      'Venezuela', '3'),
  ('animal', 4,  'Tornado Negro',        'Venezuela', '4'),
  ('animal', 5,  'Rayo de Luz',          'Venezuela', '1'),
  ('animal', 6,  'Brisa Veloz',          'Venezuela', '2'),
  ('animal', 7,  'Ágil Sombra',          'Venezuela', '3'),
  ('animal', 8,  'Sahara Dream',         'Venezuela', '5'),
  ('animal', 9,  'Ibericus Rex',         'España',    '6'),
  ('animal', 10, 'Niebla Rápida',        'Venezuela', '4'),
  ('animal', 11, 'Cima Dorada',          'Venezuela', '7'),
  ('animal', 12, 'Nieve Rusa',           'Rusia',     '8');

INSERT INTO participante (tipo, id_equipo, nombre_oficial, nacionalidad) VALUES
  ('equipo', 1,  'Caracas FC',            'Venezuela'),
  ('equipo', 2,  'Mineros de Guayana',    'Venezuela'),
  ('equipo', 3,  'Deportivo Táchira',     'Venezuela'),
  ('equipo', 4,  'Zulia FC',              'Venezuela'),
  ('equipo', 5,  'Leones de Caracas',     'Venezuela'),
  ('equipo', 6,  'Tigres de Aragua',      'Venezuela'),
  ('equipo', 7,  'Navegantes del Magallanes','Venezuela'),
  ('equipo', 8,  'Trotamundos de Carabobo','Venezuela'),
  ('equipo', 9,  'Cocodrilos de Caracas', 'Venezuela'),
  ('equipo', 10, 'Anzoátegui FC',         'Venezuela'),
  ('equipo', 11, 'La Guaira FC',          'Venezuela'),
  ('equipo', 12, 'Llaneros de Guanare',   'Venezuela');

-- ============================================================
-- EVENTO ↔ PARTICIPANTE
-- ============================================================
-- Evento 1 (Fútbol): Caracas FC vs Deportivo Táchira
INSERT INTO evento_participante (id_evento, id_participante, estado_salud) VALUES
  (1, 25, 'Óptimo'),   -- Caracas FC (equipo participante id=25)
  (1, 27, 'Óptimo'),   -- Deportivo Táchira (id=27)
-- Evento 2 (Baloncesto): Trotamundos vs Cocodrilos
  (2, 32, 'Óptimo'),   -- Trotamundos (id=32)
  (2, 33, 'Óptimo'),   -- Cocodrilos (id=33)
-- Evento 3 (Béisbol): Leones vs Navegantes
  (3, 29, 'Óptimo'),   -- Leones (id=29)
  (3, 31, 'Óptimo'),   -- Navegantes (id=31)
-- Evento 4 (Tenis): Carlos Medina vs Sebastián López
  (4, 1,  'Óptimo'),   -- Carlos Medina (jugador id=1)
  (4, 10, 'Óptimo'),   -- Sebastián López (jugador id=10)
-- Evento 5 (Carreras): Caballos
  (5, 13, 'Óptimo'),   -- Relámpago del Sur (animal participante id=13)
  (5, 14, 'Óptimo'),   -- Viento Veloz (id=14)
  (5, 15, 'Óptimo'),   -- Estrella de Mar (id=15)
  (5, 16, 'Lesionado'),-- Tornado Negro (id=16)
-- Evento 6 (Fútbol): Mineros vs Zulia FC
  (6, 26, 'Óptimo'),   -- Mineros (id=26)
  (6, 28, 'Óptimo'),   -- Zulia FC (id=28)
-- Evento 7 (Boxeo): Jugadores 11 y 12
  (7, 11, 'Óptimo'),
  (7, 12, 'Óptimo'),
-- Evento 8 (Baloncesto): Leones vs Anzoátegui
  (8, 29, 'Óptimo'),
  (8, 34, 'Óptimo');

-- ============================================================
-- RESULTADOS ↔ PARTICIPANTES
-- ============================================================
INSERT INTO resultado_participante (id_resultado, id_participante, posicion, puntaje) VALUES
  (1, 25, 1, '3'),    -- Caracas FC 1er lugar
  (1, 27, 2, '1'),    -- Deportivo Táchira 2do
  (2, 32, 1, '98'),   -- Trotamundos 1er
  (2, 33, 2, '85'),   -- Cocodrilos 2do
  (3, 29, 1, '7'),    -- Leones 1er
  (3, 31, 2, '4'),    -- Navegantes 2do
  (4, 1,  1, '6'),    -- Carlos Medina 1er
  (4, 10, 2, '4'),    -- Sebastián 2do
  (5, 13, 1, NULL),   -- Relámpago 1er carrera
  (5, 14, 2, NULL),   -- Viento Veloz 2do
  (5, 15, 3, NULL),   -- Estrella 3ro
  (6, 26, 1, '1'),    -- Mineros 1er
  (6, 28, 2, '0'),    -- Zulia 2do
  (7, 11, 1, 'KO R5'),
  (7, 12, 2, NULL),
  (8, 32, 1, '110'),
  (8, 34, 2, '95');

-- ============================================================
-- APUESTAS
-- ============================================================
INSERT INTO apuesta (id_centro, id_cliente, id_evento, id_transaccion, cuota_base, monto_apuesta, nro_transaccion, estado, fecha_hora) VALUES
  (1,  1,  1, 1,  1.85, 200.00,  'TXN-0001', 'Ganada',    '2024-02-01 14:00:00'),
  (1,  2,  1, 2,  2.10, 100.00,  'TXN-0002', 'Perdida',   '2024-02-01 14:05:00'),
  (3,  3,  2, 3,  1.65, 500.00,  'TXN-0003', 'Ganada',    '2024-02-05 17:00:00'),
  (4,  4,  3, 4,  1.90, 75.00,   'TXN-0004', 'Ganada',    '2024-02-10 13:00:00'),
  (6,  5,  4, 5,  2.25, 1000.00, 'TXN-0005', 'Ganada',    '2024-02-15 09:00:00'),
  (2,  6,  5, 6,  3.00, 150.00,  'TXN-0006', 'Perdida',   '2024-02-20 11:00:00'),
  (8,  7,  6, 7,  1.75, 800.00,  'TXN-0007', 'Ganada',    '2024-03-01 19:00:00'),
  (5,  8,  7, 8,  2.50, 50.00,   'TXN-0008', 'Ganada',    '2024-03-05 20:00:00'),
  (9,  9,  8, 9,  1.60, 300.00,  'TXN-0009', 'En curso',  '2024-03-15 14:00:00'),
  (11, 10, 1, 10, 1.95, 125.00,  'TXN-0010', 'Perdida',   '2024-02-01 14:10:00'),
  (12, 11, 2, 11, 1.80, 600.00,  'TXN-0011', 'Ganada',    '2024-02-05 17:30:00'),
  (10, 12, 3, 12, 2.00, 40.00,   'TXN-0012', 'Ganada',    '2024-02-10 13:15:00');

-- ============================================================
-- APUESTAS SIMPLES
-- ============================================================
INSERT INTO apuesta_simple (id_apuesta, seleccion, pronostico) VALUES
  (1,  'Caracas FC',          'Victoria local'),
  (2,  'Deportivo Táchira',   'Victoria visitante'),
  (4,  'Leones de Caracas',   'Victoria en 7 juegos'),
  (5,  'Carlos Medina',       'Victoria en 3 sets'),
  (8,  'Ramón Fuentes',       'Victoria por KO'),
  (10, 'Deportivo Táchira',   'Victoria visitante'),
  (12, 'Leones de Caracas',   'Victoria en 5 juegos');

-- ============================================================
-- APUESTAS COMBINADAS
-- ============================================================
INSERT INTO apuesta_combinada (id_apuesta, cuota_total, multiplicador) VALUES
  (3,  5.40, 3.00),
  (7,  4.20, 2.40),
  (9,  3.80, 2.00),
  (11, 6.10, 3.50);

-- ============================================================
-- APUESTAS HANDICAP
-- ============================================================
INSERT INTO apuesta_handicap (id_apuesta, tipo, ventaja_puntos, direccion, linea_juego) VALUES
  (6,  'Spread',  -2.5, 'favor',     3.00),
  (2,  'Spread',  +1.5, 'en contra', 2.10);

-- ============================================================
-- APUESTA ↔ PARTICIPANTE (Elige)
-- ============================================================
INSERT INTO apuesta_participante (id_apuesta, id_participante) VALUES
  (1,  25),  -- Apuesta 1 → Caracas FC
  (2,  27),  -- Apuesta 2 → Deportivo Táchira
  (3,  32),  -- Apuesta 3 → Trotamundos
  (4,  29),  -- Apuesta 4 → Leones
  (5,  1),   -- Apuesta 5 → Carlos Medina
  (6,  13),  -- Apuesta 6 → Relámpago del Sur
  (7,  26),  -- Apuesta 7 → Mineros
  (8,  11),  -- Apuesta 8 → Ramón Fuentes
  (9,  32),  -- Apuesta 9 → Trotamundos (en curso)
  (10, 27),  -- Apuesta 10 → Deportivo Táchira
  (11, 32),  -- Apuesta 11 → Trotamundos
  (12, 29);  -- Apuesta 12 → Leones

-- ============================================================
-- DATA EXTRA PARA REPORTES
-- ============================================================

-- 1) Actividad de clientes en categoria Carreras (> 500)
INSERT INTO apuesta (id_centro, id_cliente, id_evento, id_transaccion, cuota_base, monto_apuesta, nro_transaccion, estado, fecha_hora) VALUES
  (2, 5, 5,  NULL, 2.80, 220.00, 'TXN-CARR-0001', 'Ganada',  '2024-04-02 12:00:00'),
  (2, 5, 11, NULL, 2.60, 260.00, 'TXN-CARR-0002', 'Ganada',  '2024-04-03 15:20:00'),
  (2, 5, 5,  NULL, 2.95, 180.00, 'TXN-CARR-0003', 'Ganada',  '2024-04-04 17:10:00'),
  (2, 3, 11, NULL, 2.45, 190.00, 'TXN-CARR-0004', 'Perdida', '2024-04-05 09:45:00'),
  (2, 3, 5,  NULL, 2.70, 170.00, 'TXN-CARR-0005', 'Ganada',  '2024-04-05 13:10:00'),
  (2, 3, 11, NULL, 2.55, 210.00, 'TXN-CARR-0006', 'Ganada',  '2024-04-06 11:25:00');

-- 2) Centro y evento para filtro exacto: Las Vegas Strip + Olimpiadas
WITH centro_lv AS (
  INSERT INTO centro_apuestas (id_casino, id_gerente, nro_local, capacidad_maxima, ip_servidor, fondo, turno, estado_operativo, calle, ciudad, estado_dir, codigo_postal)
  VALUES (2, 2, 'LOC-013', 350, '192.168.12.10', 180000.00, '24h', 'Activo', 'Las Vegas Strip', 'Las Vegas', 'Nevada', '88901')
  RETURNING id_centro
),
evento_ol AS (
  INSERT INTO evento (id_casino, categoria, fecha_hora_inicio, estado, clima, fecha_publicacion)
  VALUES (2, 'Olimpiadas', '2024-04-08 20:00:00', 'Programado', 'Interior', '2024-04-01')
  RETURNING id_evento
)
INSERT INTO apuesta (id_centro, id_cliente, id_evento, id_transaccion, cuota_base, monto_apuesta, nro_transaccion, estado, fecha_hora)
SELECT c.id_centro, 7, e.id_evento, NULL, 1.95, 320.00, 'TXN-OL-0001', 'Ganada', '2024-04-08 19:10:00'
FROM centro_lv c
CROSS JOIN evento_ol e;

-- 3) Participante popular (id_participante=32) con mas de 100 apuestas
WITH nuevas_apuestas AS (
  INSERT INTO apuesta (id_centro, id_cliente, id_evento, id_transaccion, cuota_base, monto_apuesta, nro_transaccion, estado, fecha_hora)
  SELECT
    8,
    ((gs - 1) % 12) + 1,
    CASE WHEN gs % 2 = 0 THEN 2 ELSE 8 END,
    NULL,
    1.60 + ((gs % 6) * 0.15),
    60 + (gs % 40),
    'TXN-POP-' || LPAD(gs::text, 4, '0'),
    'Ganada',
    TIMESTAMP '2024-04-10 10:00:00' + (gs || ' minutes')::interval
  FROM generate_series(1, 110) AS gs
  RETURNING id_apuesta
)
INSERT INTO apuesta_participante (id_apuesta, id_participante)
SELECT id_apuesta, 32
FROM nuevas_apuestas;

-- ============================================================
-- FIN DEL SEED
-- ============================================================