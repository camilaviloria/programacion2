const fs = require("fs");
const path = require("path");
const dotenv = require("dotenv");
const express = require("express");
const cors = require("cors");
const { Pool } = require("pg");

const envFilePath = path.join(__dirname, ".env");
dotenv.config({ path: fs.existsSync(envFilePath) ? envFilePath : undefined });

const app = express();
const PORT = Number(process.env.PORT || 3000);
const useSSL = String(process.env.PGSSL || "false").toLowerCase() === "true";
const publicDir = path.join(__dirname, "public");

const poolConfig = process.env.DATABASE_URL
  ? {
      connectionString: process.env.DATABASE_URL,
      ssl: useSSL ? { rejectUnauthorized: false } : false
    }
  : {
      host: process.env.PGHOST || "localhost",
      port: Number(process.env.PGPORT || 5432),
      user: process.env.PGUSER || "postgres",
      password: process.env.PGPASSWORD || "postgres",
      database: process.env.PGDATABASE || "postgres",
      ssl: useSSL ? { rejectUnauthorized: false } : false
    };

const pool = new Pool(poolConfig);

const SQL_QUERIES = {
  volumenCasino: `
    SELECT
      c.nombre_legal,
      SUM(a.monto_apuesta) AS monto_total
    FROM casino.casino c
    JOIN casino.centro_apuestas ca ON c.id_casino = ca.id_casino
    JOIN casino.apuesta a ON ca.id_centro = a.id_centro
    GROUP BY c.id_casino, c.nombre_legal
    ORDER BY monto_total DESC;
  `,
  participantesPopulares: `
    SELECT
      p.nombre_oficial,
      COUNT(ap.id_apuesta) AS total_apuestas
    FROM casino.participante p
    JOIN casino.apuesta_participante ap ON p.id_participante = ap.id_participante
    GROUP BY p.id_participante, p.nombre_oficial
    HAVING COUNT(ap.id_apuesta) > 100;
  `,
  actividadClientes: `
    SELECT
      cl.nombre,
      SUM(a.monto_apuesta) AS total_invertido
    FROM casino.cliente cl
    JOIN casino.apuesta a ON cl.id_cliente = a.id_cliente
    JOIN casino.evento e ON a.id_evento = e.id_evento
    WHERE e.categoria = 'Carreras'
    GROUP BY cl.id_cliente, cl.nombre
    HAVING SUM(a.monto_apuesta) > 500;
  `,
  centrosOlimpiadas: `
    SELECT DISTINCT
      ca.nro_local,
      ca.calle
    FROM casino.centro_apuestas ca
    JOIN casino.apuesta a ON ca.id_centro = a.id_centro
    JOIN casino.evento e ON a.id_evento = e.id_evento
    WHERE ca.calle = 'Las Vegas Strip'
      AND e.categoria = 'Olimpiadas'
    ORDER BY ca.nro_local;
  `,
  rendimientoEvento: `
    SELECT
      id_evento,
      AVG(monto_apuesta) AS promedio_apuesta
    FROM casino.apuesta
    GROUP BY id_evento
    HAVING AVG(monto_apuesta) > 50
    ORDER BY promedio_apuesta DESC;
  `
};

const UI_SQL_QUERIES = {
  casinos: `
    SELECT
      c.id_casino AS id,
      c.nombre_legal AS nombre,
      COALESCE(NULLIF(c.nombre_comercial, ''), c.nombre_legal) AS short
    FROM casino.casino c
    ORDER BY c.id_casino;
  `,
  centros: `
    SELECT
      ca.nro_local AS loc,
      ca.id_casino,
      COALESCE(NULLIF(c.nombre_comercial, ''), c.nombre_legal) AS casino,
      ca.ciudad,
      ca.fondo,
      ca.capacidad_maxima AS cap,
      ca.turno,
      LOWER(COALESCE(ca.estado_operativo, '')) = 'activo' AS activo,
      COALESCE(SUM(a.monto_apuesta), 0) AS vol,
      COUNT(a.id_apuesta) AS aps
    FROM casino.centro_apuestas ca
    JOIN casino.casino c ON c.id_casino = ca.id_casino
    LEFT JOIN casino.apuesta a ON a.id_centro = ca.id_centro
    GROUP BY
      ca.id_centro,
      ca.nro_local,
      ca.id_casino,
      c.nombre_comercial,
      c.nombre_legal,
      ca.ciudad,
      ca.fondo,
      ca.capacidad_maxima,
      ca.turno,
      ca.estado_operativo
    ORDER BY ca.id_centro;
  `,
  clients: `
    SELECT
      cl.id_cliente AS id,
      cl.nombre,
      cl.cedula,
      COALESCE(cl.saldo_cuenta, 0) AS saldo,
      COALESCE(SUM(a.monto_apuesta), 0) AS total,
      COALESCE(NULLIF(cl.metodo_cobro, ''), mp.descripcion, 'N/D') AS metodo,
      COALESCE(NULLIF(cl.plataforma_financiera, ''), 'N/D') AS plataforma,
      COALESCE(cl.saldo_cuenta, 0) > 0 AS activo
    FROM casino.cliente cl
    LEFT JOIN casino.metodo_pago mp ON mp.id_metodo = cl.id_metodo_pago
    LEFT JOIN casino.apuesta a ON a.id_cliente = cl.id_cliente
    GROUP BY
      cl.id_cliente,
      cl.nombre,
      cl.cedula,
      cl.saldo_cuenta,
      cl.metodo_cobro,
      cl.plataforma_financiera,
      mp.descripcion
    ORDER BY cl.id_cliente;
  `,
  eventos: `
    SELECT
      e.id_evento AS id,
      e.categoria AS cat,
      COALESCE(pn.nombre_evento, e.categoria || ' #' || e.id_evento::text) AS name,
      e.estado AS status,
      TO_CHAR(e.fecha_hora_inicio, 'HH24:MI') AS hora,
      COALESCE(NULLIF(c.nombre_comercial, ''), c.nombre_legal) AS casino,
      COALESCE(SUM(a.monto_apuesta), 0) AS monto,
      COALESCE(pn.parts, 0) AS parts
    FROM casino.evento e
    JOIN casino.casino c ON c.id_casino = e.id_casino
    LEFT JOIN casino.apuesta a ON a.id_evento = e.id_evento
    LEFT JOIN LATERAL (
      SELECT
        string_agg(p.nombre_oficial, ' vs ' ORDER BY p.nombre_oficial) AS nombre_evento,
        COUNT(*) AS parts
      FROM casino.evento_participante ep
      JOIN casino.participante p ON p.id_participante = ep.id_participante
      WHERE ep.id_evento = e.id_evento
    ) pn ON true
    GROUP BY
      e.id_evento,
      e.categoria,
      e.estado,
      e.fecha_hora_inicio,
      c.nombre_comercial,
      c.nombre_legal,
      pn.nombre_evento,
      pn.parts
    ORDER BY e.id_evento;
  `,
  apuestas: `
    SELECT
      a.id_apuesta AS id,
      cl.nombre AS cliente,
      COALESCE(pn.nombre_evento, e.categoria || ' #' || e.id_evento::text) AS evento,
      ca.nro_local AS centro,
      COALESCE(a.cuota_base, 1) AS cuota,
      a.monto_apuesta AS monto,
      CASE
        WHEN ac.id_apuesta IS NOT NULL THEN 'Combinada'
        WHEN ah.id_apuesta IS NOT NULL THEN 'Handicap'
        ELSE 'Simple'
      END AS tipo,
      a.estado,
      TO_CHAR(a.fecha_hora::date, 'YYYY-MM-DD') AS fecha
    FROM casino.apuesta a
    JOIN casino.cliente cl ON cl.id_cliente = a.id_cliente
    JOIN casino.centro_apuestas ca ON ca.id_centro = a.id_centro
    JOIN casino.evento e ON e.id_evento = a.id_evento
    LEFT JOIN casino.apuesta_combinada ac ON ac.id_apuesta = a.id_apuesta
    LEFT JOIN casino.apuesta_handicap ah ON ah.id_apuesta = a.id_apuesta
    LEFT JOIN LATERAL (
      SELECT string_agg(p.nombre_oficial, ' vs ' ORDER BY p.nombre_oficial) AS nombre_evento
      FROM casino.evento_participante ep
      JOIN casino.participante p ON p.id_participante = ep.id_participante
      WHERE ep.id_evento = e.id_evento
    ) pn ON true
    ORDER BY a.id_apuesta;
  `
};

app.use(cors());
app.use(express.json());
app.use(express.static(publicDir));

app.get("/api/health", async (_req, res) => {
  try {
    await pool.query("SELECT 1");
    res.json({ ok: true, db: "connected" });
  } catch (error) {
    res.status(500).json({ ok: false, db: "disconnected", error: error.message });
  }
});

app.get("/api/kpis/:name", async (req, res) => {
  const queryName = req.params.name;
  const sql = SQL_QUERIES[queryName];

  if (!sql) {
    res.status(404).json({ ok: false, error: "Consulta no encontrada" });
    return;
  }

  try {
    const { rows } = await pool.query(sql);
    res.json({ ok: true, rows });
  } catch (error) {
    res.status(500).json({ ok: false, error: error.message });
  }
});

app.get("/api/dashboard", async (_req, res) => {
  try {
    const entries = await Promise.all(
      Object.entries(SQL_QUERIES).map(async ([key, sql]) => {
        const { rows } = await pool.query(sql);
        return [key, rows];
      })
    );

    res.json({
      ok: true,
      generatedAt: new Date().toISOString(),
      data: Object.fromEntries(entries)
    });
  } catch (error) {
    res.status(500).json({ ok: false, error: error.message });
  }
});

app.get("/api/ui-data", async (_req, res) => {
  const toNumber = (value) => {
    const parsed = Number(value);
    return Number.isFinite(parsed) ? parsed : 0;
  };

  try {
    const [casinosResult, centrosResult, clientsResult, eventosResult, apuestasResult] = await Promise.all([
      pool.query(UI_SQL_QUERIES.casinos),
      pool.query(UI_SQL_QUERIES.centros),
      pool.query(UI_SQL_QUERIES.clients),
      pool.query(UI_SQL_QUERIES.eventos),
      pool.query(UI_SQL_QUERIES.apuestas)
    ]);

    const data = {
      casinos: casinosResult.rows.map((row) => ({
        id: toNumber(row.id),
        nombre: row.nombre,
        short: row.short
      })),
      centros: centrosResult.rows.map((row) => ({
        loc: row.loc,
        id_casino: toNumber(row.id_casino),
        casino: row.casino,
        ciudad: row.ciudad,
        fondo: toNumber(row.fondo),
        cap: toNumber(row.cap),
        turno: row.turno,
        activo: Boolean(row.activo),
        vol: toNumber(row.vol),
        aps: toNumber(row.aps)
      })),
      clients: clientsResult.rows.map((row) => ({
        id: toNumber(row.id),
        nombre: row.nombre,
        cedula: row.cedula,
        saldo: toNumber(row.saldo),
        total: toNumber(row.total),
        metodo: row.metodo,
        plataforma: row.plataforma,
        activo: Boolean(row.activo)
      })),
      eventos: eventosResult.rows.map((row) => ({
        id: toNumber(row.id),
        cat: row.cat,
        name: row.name,
        status: row.status,
        hora: row.hora,
        casino: row.casino,
        monto: toNumber(row.monto),
        parts: toNumber(row.parts)
      })),
      apuestas: apuestasResult.rows.map((row) => ({
        id: toNumber(row.id),
        cliente: row.cliente,
        evento: row.evento,
        centro: row.centro,
        cuota: toNumber(row.cuota),
        monto: toNumber(row.monto),
        tipo: row.tipo,
        estado: row.estado,
        fecha: row.fecha
      }))
    };

    res.json({
      ok: true,
      generatedAt: new Date().toISOString(),
      data
    });
  } catch (error) {
    res.status(500).json({ ok: false, error: error.message });
  }
});

app.get("/{*path}", (_req, res) => {
  const entryFile = ["index.html", "casino_dashboard.html"]
    .map((name) => path.join(publicDir, name))
    .find((filePath) => fs.existsSync(filePath));

  if (!entryFile) {
    res.status(404).json({
      ok: false,
      error: "No se encontro un archivo de entrada en public/"
    });
    return;
  }

  res.sendFile(entryFile);
});

app.listen(PORT, () => {
  console.log(`Casino app en http://localhost:${PORT}`);
});
