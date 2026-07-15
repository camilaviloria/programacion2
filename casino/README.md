# Casino Dashboard App

Aplicacion web con frontend vanilla (HTML, CSS, JS) y backend Node.js para consultar PostgreSQL.

## Requisitos
- Node.js 18+
- PostgreSQL local con el esquema cargado en schema.sql

## Instalacion
1. Instalar dependencias:
   npm install
2. Crear archivo .env a partir de .env.example
3. Ajustar credenciales de base de datos en .env
4. Levantar servidor:
   npm run dev

## Endpoints API
- GET /api/health
- GET /api/dashboard
- GET /api/kpis/volumenCasino
- GET /api/kpis/participantesPopulares
- GET /api/kpis/actividadClientes
- GET /api/kpis/centrosOlimpiadas
- GET /api/kpis/rendimientoEvento

## Migrar a PostgreSQL en la nube
Cuando uses un proveedor cloud (Neon, Supabase, Render, Railway, etc):
1. Configura DATABASE_URL en .env
2. Activa PGSSL=true si el proveedor lo solicita
3. Manten el mismo esquema SQL en la instancia remota

Con eso, la app cambia a nube sin modificar el codigo.
