/* ═══════════ DATA ═══════════ */
let CASINOS_DATA = [];
let CENTROS = [];
let CLIENTS = [];
let EVENTOS = [];
let APUESTAS = [];

/* ═══════════ THEME ═══════════ */
let isDark = true;
function toggleTheme() {
  isDark = !isDark;
  document.documentElement.setAttribute('data-theme', isDark ? 'dark' : 'light');
  const tog = document.getElementById('theme-toggle');
  const label = document.getElementById('theme-label-text');
  const moon = document.getElementById('theme-icon-moon');
  const sun = document.getElementById('theme-icon-sun');
  if (isDark) {
    tog.classList.add('on'); label.textContent = 'Modo oscuro';
    moon.style.display=''; sun.style.display='none';
  } else {
    tog.classList.remove('on'); label.textContent = 'Modo claro';
    moon.style.display='none'; sun.style.display='';
  }
  // Re-render charts after theme change
  setTimeout(() => { destroyCharts(); initCharts(); }, 50);
}

/* ═══════════ NAVIGATION ═══════════ */
const PAGE_META = {
  overview: {title:'Resumen general',       sub:'Vista consolidada del dashboard'},
  events:   {title:'Eventos deportivos',    sub:'Gestión y seguimiento de eventos'},
  clients:  {title:'Gestión de clientes',   sub:'Cartera de clientes registrados'},
  centros:  {title:'Centros de apuestas',   sub:'Rendimiento operativo por local'},
  apuestas: {title:'Libro de apuestas',     sub:'Registro completo de transacciones'},
};

function navigate(page, el) {
  document.querySelectorAll('.nav-item').forEach(n => n.classList.remove('active'));
  document.querySelectorAll('.page').forEach(p => p.classList.remove('active'));
  el.classList.add('active');
  document.getElementById('page-' + page).classList.add('active');
  const m = PAGE_META[page];
  document.getElementById('topbar-title').textContent = m.title;
  document.getElementById('topbar-sub').textContent = m.sub;
}

function bindUiEvents() {
  document.querySelectorAll('.nav-item[data-page]').forEach((item) => {
    item.addEventListener('click', () => navigate(item.dataset.page, item));
  });

  const themeSwitch = document.querySelector('.theme-switch');
  if (themeSwitch) {
    themeSwitch.addEventListener('click', toggleTheme);
  }

  document.querySelectorAll('.events-filter[data-filter]').forEach((btn) => {
    btn.addEventListener('click', () => filterEvents(btn.dataset.filter, btn));
  });

  const eventSearch = document.getElementById('event-search');
  if (eventSearch) {
    eventSearch.addEventListener('input', renderEvents);
  }

  document.querySelectorAll('.clients-filter[data-filter]').forEach((btn) => {
    btn.addEventListener('click', () => filterClients(btn.dataset.filter, btn));
  });

  const clientSearch = document.getElementById('client-search');
  if (clientSearch) {
    clientSearch.addEventListener('input', renderClients);
  }

  document.querySelectorAll('.js-client-sort[data-sort-key]').forEach((th) => {
    th.addEventListener('click', () => sortClients(th.dataset.sortKey));
  });

  document.querySelectorAll('.centros-sort[data-sort-key]').forEach((btn) => {
    btn.addEventListener('click', () => sortCentros(btn.dataset.sortKey, btn));
  });

  document.querySelectorAll('.apuestas-filter[data-filter]').forEach((btn) => {
    btn.addEventListener('click', () => filterApuestas(btn.dataset.filter, btn));
  });

  const apuestaSearch = document.getElementById('apuesta-search');
  if (apuestaSearch) {
    apuestaSearch.addEventListener('input', renderApuestas);
  }
}

/* ═══════════ CLOCK ═══════════ */
function updateClock() {
  const now = new Date();
  const s = now.toLocaleDateString('es-VE',{day:'2-digit',month:'2-digit',year:'numeric'})
    + ' ' + now.toLocaleTimeString('es-VE',{hour:'2-digit',minute:'2-digit',second:'2-digit'});
  document.getElementById('live-clock').textContent = s;
}
setInterval(updateClock, 1000); updateClock();

/* ═══════════ HELPERS ═══════════ */
function fmt(n) { return '$' + n.toLocaleString(); }
function pct(v, max) { return max > 0 ? Math.round(v/max*100) : 0; }
function eff(c) { return c.vol > 0 ? (c.vol/c.fondo*100).toFixed(2) : '0.00'; }
function statusBadge(s) {
  if (s==='Ganada'||s==='Activo'||s==='Finalizado') return 'badge-green';
  if (s==='Perdida'||s==='Inactivo') return 'badge-red';
  if (s==='En curso') return 'badge-amber';
  if (s==='Programado') return 'badge-blue';
  return 'badge-gray';
}
function makeBars(items, valFn, labelFn, colors) {
  const max = Math.max(...items.map(valFn), 1);
  return items.map((item, i) => {
    const v = valFn(item);
    const w = pct(v, max);
    const col = colors ? colors[i % colors.length] : 'var(--gold)';
    return `<div class="bar-row-item">
      <div class="bar-meta"><span>${labelFn(item)}</span><strong>${fmt(v)}</strong></div>
      <div class="bar-track"><div class="bar-fill" style="width:${w}%;background:${col}"></div></div>
    </div>`;
  }).join('');
}

const EVENT_ICON_BY_CATEGORY = {
  'Fútbol': '⚽',
  'Baloncesto': '🏀',
  'Béisbol': '⚾',
  'Tenis': '🎾',
  'Carreras': '🏇',
  'Boxeo': '🥊',
  'Fútbol Sala': '⚽'
};

function eventIconByCategory(category) {
  return EVENT_ICON_BY_CATEGORY[category] || '🎯';
}

async function loadUiData() {
  const response = await fetch('/api/ui-data');
  const payload = await response.json();

  if (!response.ok || !payload.ok) {
    throw new Error(payload?.error || `Fallo API: ${response.status}`);
  }

  CASINOS_DATA = payload.data?.casinos || [];
  CENTROS = payload.data?.centros || [];
  CLIENTS = payload.data?.clients || [];
  EVENTOS = (payload.data?.eventos || []).map((evento) => ({
    ...evento,
    nombre: evento.nombre || evento.name || `Evento #${evento.id}`,
    icon: eventIconByCategory(evento.cat)
  }));
  APUESTAS = payload.data?.apuestas || [];

  const eventsBadge = document.getElementById('badge-events');
  if (eventsBadge) {
    eventsBadge.textContent = String(EVENTOS.length);
  }

  const clientsBadge = document.querySelector('.nav-item[data-page="clients"] .nav-badge');
  if (clientsBadge) {
    clientsBadge.textContent = String(CLIENTS.length);
  }

  const apuestasBadge = document.querySelector('.nav-item[data-page="apuestas"] .nav-badge');
  if (apuestasBadge) {
    apuestasBadge.textContent = String(APUESTAS.length);
  }
}

/* ═══════════ OVERVIEW ═══════════ */
function buildOverview() {
  // Vol bars
  const byC = CASINOS_DATA.map(c => {
    const vol = APUESTAS.filter(a => CENTROS.find(ce=>ce.loc===a.centro&&ce.id_casino===c.id)).reduce((s,a)=>s+a.monto,0);
    return {...c, vol};
  }).filter(c=>c.vol>0).sort((a,b)=>b.vol-a.vol).slice(0,6);
  const colors = ['#c9a84c','#4a8fff','#3ecf8e','#f5a623','#a78bfa','#f06060'];
  document.getElementById('vol-bars-overview').innerHTML = makeBars(byC, c=>c.vol, c=>c.short, colors);

  // Top clients
  const sorted = [...CLIENTS].sort((a,b)=>b.total-a.total);
  document.getElementById('top-clients-tbl').innerHTML = sorted.map((c,i)=>{
    const rc = i===0?'rank-1':i===1?'rank-2':i===2?'rank-3':'rank-n';
    const dot = c.activo ? '#3ecf8e' : 'var(--text3)';
    return `<tr>
      <td><span class="rank ${rc}">${i+1}</span></td>
      <td style="font-weight:500">${c.nombre}</td>
      <td class="mono">${fmt(c.total)}</td>
      <td><span style="display:inline-block;width:8px;height:8px;border-radius:50%;background:${dot}"></span></td>
    </tr>`;
  }).join('');

  // Recent events
  document.getElementById('recent-events').innerHTML = EVENTOS.slice(0,5).map(e=>`
    <div class="event-row">
      <div class="event-cat-icon">${e.icon}</div>
      <div class="event-info">
        <div class="event-name">${e.nombre}</div>
        <div class="event-meta-row">${e.casino} · ${e.cat}</div>
      </div>
      <div class="event-right">
        <span class="badge ${statusBadge(e.status)}">${e.status}</span>
        <div class="event-time">${e.hora}</div>
      </div>
    </div>`).join('');
}

/* ═══════════ EVENTS ═══════════ */
let eventFilter = 'all';
function filterEvents(f, el) {
  eventFilter = f;
  document.querySelectorAll('#page-events .filter-chip').forEach(b=>b.classList.remove('active'));
  el.classList.add('active');
  renderEvents();
}
function renderEvents() {
  const q = document.getElementById('event-search').value.toLowerCase();
  let list = eventFilter==='all' ? EVENTOS : EVENTOS.filter(e=>e.status===eventFilter);
  if (q) list = list.filter(e=>e.nombre.toLowerCase().includes(q)||e.cat.toLowerCase().includes(q));
  const el = document.getElementById('events-full-list');
  const empty = document.getElementById('events-empty');
  if (!list.length) { el.innerHTML=''; empty.style.display=''; return; }
  empty.style.display='none';
  el.innerHTML = list.map(e=>`
    <div class="event-row">
      <div class="event-cat-icon">${e.icon}</div>
      <div class="event-info">
        <div class="event-name">${e.nombre}</div>
        <div class="event-meta-row">${e.casino} · ${e.cat} · ${e.parts} participantes</div>
      </div>
      <div class="event-right">
        <span class="badge ${statusBadge(e.status)}">${e.status}</span>
        <div class="event-time">${e.hora} · ${e.monto>0?fmt(e.monto):'—'}</div>
      </div>
    </div>`).join('');
  document.getElementById('f-all-count').textContent = '(' + EVENTOS.length + ')';
}

/* ═══════════ CLIENTS ═══════════ */
let clientFilter='all', clientSort={key:'total',asc:false};
function filterClients(f,el) {
  clientFilter=f;
  document.querySelectorAll('#page-clients .filter-chip').forEach(b=>b.classList.remove('active'));
  el.classList.add('active'); renderClients();
}
function sortClients(k) {
  if(clientSort.key===k) clientSort.asc=!clientSort.asc;
  else { clientSort.key=k; clientSort.asc=false; }
  renderClients();
}
function renderClients() {
  const q = document.getElementById('client-search').value.toLowerCase();
  let list = clientFilter==='all' ? CLIENTS : CLIENTS.filter(c=>(clientFilter==='activo')===c.activo);
  if(q) list=list.filter(c=>c.nombre.toLowerCase().includes(q)||c.cedula.includes(q));
  list=[...list].sort((a,b)=>{
    const v = clientSort.key==='nombre'
      ? a.nombre.localeCompare(b.nombre)
      : (b[clientSort.key]||0)-(a[clientSort.key]||0);
    return clientSort.asc?-v:v;
  });
  document.getElementById('clients-tbl').innerHTML = list.map((c,i)=>{
    const rc=i===0?'rank-1':i===1?'rank-2':i===2?'rank-3':'rank-n';
    return `<tr>
      <td><span class="rank ${rc}">${i+1}</span></td>
      <td style="font-weight:500">${c.nombre}<br><span style="font-size:10px;color:var(--text3);font-family:'DM Mono',monospace">${c.cedula}</span></td>
      <td class="mono">${fmt(c.saldo)}</td>
      <td class="mono">${fmt(c.total)}</td>
      <td>${c.metodo}</td>
      <td style="font-size:11px;color:var(--text2)">${c.plataforma}</td>
      <td><span class="badge ${c.activo?'badge-green':'badge-red'}">${c.activo?'Activo':'Inactivo'}</span></td>
    </tr>`;
  }).join('');

  // Métodos bars
  const metodos = {};
  CLIENTS.forEach(c=>{ metodos[c.metodo]=(metodos[c.metodo]||0)+c.saldo; });
  const metArr = Object.entries(metodos).sort((a,b)=>b[1]-a[1]).slice(0,6);
  const mColors=['#c9a84c','#4a8fff','#3ecf8e','#a78bfa','#f5a623','#f06060'];
  document.getElementById('metodos-bars').innerHTML = metArr.map(([k,v],i)=>`
    <div class="bar-row-item">
      <div class="bar-meta"><span>${k}</span><strong>${fmt(v)}</strong></div>
      <div class="bar-track"><div class="bar-fill" style="width:${pct(v,metArr[0][1])}%;background:${mColors[i]}"></div></div>
    </div>`).join('');
}

/* ═══════════ CENTROS ═══════════ */
let centroSort='vol';
function sortCentros(k, el) {
  centroSort=k;
  document.querySelectorAll('#page-centros .filter-chip').forEach(b=>b.classList.remove('active'));
  el.classList.add('active'); renderCentros();
}
function renderCentros() {
  const sorted=[...CENTROS].sort((a,b)=>{
    if(centroSort==='vol') return b.vol-a.vol;
    if(centroSort==='eff') return parseFloat(eff(b))-parseFloat(eff(a));
    if(centroSort==='cap') return b.cap-a.cap;
    return 0;
  });
  const maxVol=Math.max(...CENTROS.map(c=>c.vol),1);
  document.getElementById('centros-tbl').innerHTML = sorted.map((c,i)=>{
    const e=parseFloat(eff(c));
    const ec=e>=2?'var(--green)':e>=0.5?'var(--amber)':'var(--red)';
    const wp=pct(c.vol,maxVol);
    const rc=i===0?'rank-1':i===1?'rank-2':i===2?'rank-3':'rank-n';
    return `<tr>
      <td><span class="rank ${rc}">${i+1}</span></td>
      <td class="mono" style="font-size:11px">${c.loc}</td>
      <td style="font-size:12px">${c.casino}</td>
      <td style="font-size:11px;color:var(--text2)">${c.ciudad}</td>
      <td>
        <span class="mono" style="font-weight:500">${fmt(c.vol)}</span>
        <div class="bar-track" style="margin-top:3px"><div class="bar-fill" style="width:${wp}%;background:var(--gold)"></div></div>
      </td>
      <td style="text-align:center">${c.aps}</td>
      <td class="mono">${c.aps>0?fmt(Math.round(c.vol/c.aps)):'—'}</td>
      <td><span style="color:${ec};font-weight:500;font-family:'DM Mono',monospace">${e.toFixed(2)}%</span></td>
      <td class="mono" style="font-size:11px">$${Math.round(c.fondo/1000)}K</td>
      <td style="text-align:center">${c.cap}</td>
      <td><span class="badge badge-gray">${c.turno}</span></td>
      <td><span class="badge ${c.activo?'badge-green':'badge-red'}">${c.activo?'Activo':'Inactivo'}</span></td>
    </tr>`;
  }).join('');

  // Eff bars
  const topEff=[...CENTROS].filter(c=>c.vol>0).sort((a,b)=>parseFloat(eff(b))-parseFloat(eff(a))).slice(0,5);
  const eColors=['#c9a84c','#4a8fff','#3ecf8e','#f5a623','#a78bfa'];
  document.getElementById('eff-bars-centros').innerHTML=topEff.map((c,i)=>{
    const e=parseFloat(eff(c));
    const maxE=parseFloat(eff(topEff[0]));
    return `<div class="bar-row-item">
      <div class="bar-meta"><span>${c.loc}</span><strong>${e.toFixed(2)}%</strong></div>
      <div class="bar-track"><div class="bar-fill" style="width:${pct(e,maxE)}%;background:${eColors[i]}"></div></div>
    </div>`;
  }).join('');
}

/* ═══════════ APUESTAS ═══════════ */
let apuestaFilter='all';
function filterApuestas(f,el) {
  apuestaFilter=f;
  document.querySelectorAll('#page-apuestas .filter-chip').forEach(b=>b.classList.remove('active'));
  el.classList.add('active'); renderApuestas();
}
function renderApuestas() {
  const q = document.getElementById('apuesta-search').value.toLowerCase();
  let list = apuestaFilter==='all' ? APUESTAS : APUESTAS.filter(a=>a.estado===apuestaFilter);
  if(q) list=list.filter(a=>a.cliente.toLowerCase().includes(q)||a.evento.toLowerCase().includes(q)||a.centro.toLowerCase().includes(q));
  const el=document.getElementById('apuestas-tbl');
  const empty=document.getElementById('apuestas-empty');
  if(!list.length){el.innerHTML='';empty.style.display='';return;}
  empty.style.display='none';
  el.innerHTML=list.map((a,i)=>{
    const tb=a.tipo==='Simple'?'badge-blue':a.tipo==='Combinada'?'badge-purple':'badge-amber';
    return `<tr>
      <td><span class="rank rank-n">${a.id}</span></td>
      <td class="mono" style="font-size:10px;color:var(--text3)">AP-${String(a.id).padStart(4,'0')}</td>
      <td style="font-size:12px;white-space:nowrap">${a.cliente}</td>
      <td style="font-size:11px;color:var(--text2)">${a.evento}</td>
      <td class="mono" style="font-size:10px">${a.centro}</td>
      <td class="mono" style="color:var(--text2)">${a.cuota.toFixed(2)}x</td>
      <td class="mono" style="font-weight:500">${fmt(a.monto)}</td>
      <td><span class="badge ${tb}">${a.tipo}</span></td>
      <td><span class="badge ${statusBadge(a.estado)}">${a.estado}</span></td>
      <td style="font-size:10px;color:var(--text3);font-family:'DM Mono',monospace">${a.fecha}</td>
    </tr>`;
  }).join('');

  // Vol por evento
  const byE={};
  APUESTAS.forEach(a=>{ byE[a.evento]=(byE[a.evento]||0)+a.monto; });
  const evArr=Object.entries(byE).sort((a,b)=>b[1]-a[1]).slice(0,6);
  const eColors=['#c9a84c','#4a8fff','#3ecf8e','#a78bfa','#f5a623','#f06060'];
  document.getElementById('vol-evento-bars').innerHTML=evArr.map(([k,v],i)=>`
    <div class="bar-row-item">
      <div class="bar-meta"><span style="font-size:11px">${k}</span><strong>${fmt(v)}</strong></div>
      <div class="bar-track"><div class="bar-fill" style="width:${pct(v,evArr[0][1])}%;background:${eColors[i]}"></div></div>
    </div>`).join('');
}

/* ═══════════ CHARTS ═══════════ */
const chartInstances = {};
function destroyCharts() {
  Object.values(chartInstances).forEach(c=>{ try{c.destroy();}catch(e){} });
  Object.keys(chartInstances).forEach(k=>delete chartInstances[k]);
}

function makeDonut(id, labels, data, colors, legendId) {
  const ctx = document.getElementById(id);
  if(!ctx) return;
  if(chartInstances[id]) chartInstances[id].destroy();
  const chart = new Chart(ctx, {
    type:'doughnut',
    data:{ labels, datasets:[{ data, backgroundColor:colors, borderWidth:0, hoverOffset:4 }]},
    options:{
      responsive:true, maintainAspectRatio:false, cutout:'68%',
      plugins:{ legend:{display:false}, tooltip:{callbacks:{label:c=>c.label+': '+c.raw}} }
    }
  });
  chartInstances[id]=chart;
  if(legendId){
    const total=data.reduce((a,b)=>a+b,0);
    document.getElementById(legendId).innerHTML=labels.map((l,i)=>`
      <div class="donut-leg-row">
        <span class="donut-sq" style="background:${colors[i]}"></span>
        <span class="donut-leg-label">${l}</span>
        <span class="donut-leg-val">${Math.round(data[i]/total*100)}%</span>
      </div>`).join('');
  }
}

function makeBar(id, labels, datasets, maxH) {
  const ctx=document.getElementById(id);
  if(!ctx) return;
  if(chartInstances[id]) chartInstances[id].destroy();
  const isDarkMode = document.documentElement.getAttribute('data-theme')==='dark';
  const gridColor = isDarkMode?'rgba(255,255,255,0.06)':'rgba(0,0,0,0.06)';
  const tickColor = isDarkMode?'#5a5970':'#9997b5';
  const chart = new Chart(ctx,{
    type:'bar',
    data:{ labels, datasets },
    options:{
      responsive:true, maintainAspectRatio:false,
      plugins:{legend:{display:false}},
      scales:{
        x:{ticks:{font:{size:10},color:tickColor,maxRotation:30},grid:{display:false}},
        y:{ticks:{font:{size:10},color:tickColor,callback:v=>'$'+v.toLocaleString()},grid:{color:gridColor}}
      }
    }
  });
  chartInstances[id]=chart;
}

function initCharts() {
  // Overview donuts
  const tiposApuesta = { Simple: 0, Combinada: 0, Handicap: 0 };
  APUESTAS.forEach((apuesta) => {
    const tipo = apuesta.tipo;
    if (tiposApuesta[tipo] !== undefined) {
      tiposApuesta[tipo] += 1;
    }
  });
  makeDonut(
    'donut-tipos',
    Object.keys(tiposApuesta),
    Object.values(tiposApuesta),
    ['#c9a84c', '#4a8fff', '#a78bfa'],
    'donut-tipos-legend'
  );

  const turnosCentro = {};
  CENTROS.forEach((centro) => {
    turnosCentro[centro.turno] = (turnosCentro[centro.turno] || 0) + 1;
  });
  const turnosLabels = Object.keys(turnosCentro);
  const turnosValues = Object.values(turnosCentro);
  makeDonut(
    'donut-turnos',
    turnosLabels,
    turnosValues,
    ['#4a8fff', '#3ecf8e', '#c9a84c', '#a78bfa', '#f5a623'].slice(0, turnosLabels.length),
    'donut-turnos-legend'
  );

  // Centros turno donut
  const turnoCount={};
  CENTROS.forEach(c=>{ turnoCount[c.turno]=(turnoCount[c.turno]||0)+1; });
  const tk=Object.keys(turnoCount), tv=Object.values(turnoCount);
  const tColors=['#4a8fff','#c9a84c','#3ecf8e','#a78bfa','#f5a623'];
  makeDonut('donut-turnos-centros', tk, tv, tColors.slice(0,tk.length), 'turnos-centros-legend');

  // Apuestas estados donut
  const estados={Ganada:0,Perdida:0,'En curso':0};
  APUESTAS.forEach(a=>{ estados[a.estado]=(estados[a.estado]||0)+1; });
  makeDonut('donut-estados',
    Object.keys(estados), Object.values(estados),
    ['#3ecf8e','#f06060','#f5a623'],'estados-legend');

  // Client saldos bar
  const topC=[...CLIENTS].sort((a,b)=>b.saldo-a.saldo).slice(0,8);
  makeBar('chart-saldos',
    topC.map(c=>c.nombre.split(' ')[0]),
    [{label:'Saldo',data:topC.map(c=>c.saldo),backgroundColor:'#c9a84c',borderRadius:4}],
    220);
}

/* ═══════════ INIT ═══════════ */
async function initApp() {
  bindUiEvents();

  try {
    await loadUiData();
  } catch (error) {
    console.error('No se pudieron cargar los datos desde la base de datos:', error);
  }

  buildOverview();
  renderEvents();
  renderClients();
  renderCentros();
  renderApuestas();
  setTimeout(initCharts, 100);
}

initApp();