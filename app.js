'use strict';
const fmt = value => value == null ? '—' : Number(value).toLocaleString('en-US',{maximumFractionDigits:1});
const esc = value => String(value).replace(/[&<>"']/g,c=>({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));
const compact = value => value >= 1e6 ? `${(value/1e6).toFixed(2)} MB` : `${(value/1e3).toFixed(1)} kB`;
const status = states => `${states.active ? `<b><span class="dot"></span>${states.active} active</b> · ` : ''}${states.ready} ready · ${states.frozen} frozen${states.blocked ? ` · ${states.blocked} blocked` : ''}`;
const metricCells = row => `<td>${fmt(row.integrated_c_bytes)}</td><td class="exact">${fmt(row.exact_available_bytes)}</td><td class="pending">${row.pending_exact_bytes ? fmt(row.pending_exact_bytes) : '—'}</td><td>${fmt(row.last_hour_exact_B_per_hour)}</td><td class="status">${status(row.states)}</td>`;
function aggregate(rows){
 const out={integrated_c_bytes:0,exact_available_bytes:0,pending_exact_bytes:0,last_hour_exact_B_per_hour:0,states:{ready:0,active:0,frozen:0,blocked:0}};
 for(const row of rows){for(const key of ['integrated_c_bytes','exact_available_bytes','pending_exact_bytes','last_hour_exact_B_per_hour'])out[key]+=row[key]||0;for(const state of Object.keys(out.states))out.states[state]+=row.states[state];}return out;
}
async function start(){
 const response=await fetch('data/progress.json',{cache:'no-cache'});if(!response.ok)throw new Error('Could not load current progress');
 const payload=await response.json(),d=payload.dashboard;if(d?.schema_version!==2)throw new Error('Unified progress snapshot unavailable');
 const age=(Date.now()-Date.parse(d.as_of))/3600000;
 document.querySelector('#updated').textContent=`${new Date(d.as_of).toLocaleString()}${age>2?' · update delayed':''}`;
 const names={team:'All lanes',main:'Main',worker2:'Worker 2',worker3:'Worker 3',other:'Other'};
 document.querySelector('#performance').innerHTML=d.performance.map(row=>`<tr class="${row.id==='team'?'team':''}"><td class="${row.id==='team'?'':'lane'}">${esc(names[row.id]||row.id)}</td><td>${fmt(row.exact_B_per_hour)}</td><td>${fmt(row.previous_exact_B_per_hour)}</td><td>${fmt(row.exact_methods_last_hour)}</td><td>${fmt(row.peer_exact_B_per_hour)}</td><td>${fmt(row.integrated_exact_B_per_hour)}</td><td>${fmt(row.median_seconds)} / ${fmt(row.p90_seconds)} s</td></tr>`).join('');
 const o=d.overview;
 document.querySelector('#overview').innerHTML=[
  ['C match / known ASM',d.c_match?.percent == null ? 'Unknown' : d.c_match.percent.toFixed(3),'%',d.c_match?.percent == null ? 'Original ASM catalogue unavailable' : `${fmt(d.c_match.matched_asm_bytes)} / ${fmt(d.c_match.total_asm_bytes)} original ASM span bytes; includes migrated code`],
  ['Exact C available',fmt(o.exact_available_bytes),'B',`${fmt(o.integrated_exact_bytes)} in ROM + ${fmt(o.pending_exact_bytes)} local`],
  ['Readable C in ROM',fmt(o.integrated_c_bytes),'B',`${fmt(o.mixed_bytes)} mixed C / ASM bytes tracked separately`],
  ['Exact C not yet in ROM',fmt(o.pending_exact_bytes),'B',`${fmt(o.pending_peer_exact_bytes)} independently accepted bytes`],
  ['Tasks in progress',fmt(o.states.active),'',`${fmt(o.states.ready)} ready · ${fmt(o.states.frozen)} frozen · ${fmt(o.states.blocked)} blocked`]
 ].map(([label,value,unit,note])=>`<article class="card"><div class="card-label">${label}</div><div class="card-value">${value}<small>${unit}</small></div><p>${note}</p></article>`).join('');
 document.querySelector('#inventory').textContent=`Reconstructed resources ${compact(payload.resource_inventory.resource_bytes_excluding_padding)} · Source ASM ${compact(payload.source_assembly.span_bytes)} · Original-byte dependencies ${compact(payload.original_byte_dependency.span_bytes)}`;
 const all=d.systems.flatMap(x=>x.modules);
 document.querySelector('#scope').textContent=`${all.length} groups · ${o.tasks} tasks`;
 document.querySelector('#system').innerHTML='<option value="all">All systems</option>'+d.systems.map(x=>`<option value="${esc(x.id)}">${esc(x.title)}</option>`).join('');
 let activeOnly=false,sortExact=false;
 function render(){
  const query=document.querySelector('#search').value.trim().toLowerCase(),system=document.querySelector('#system').value;
  const selected=d.systems.filter(x=>system==='all'||x.id===system).map(group=>({...group,modules:group.modules.filter(row=>(!activeOnly||row.states.active>0)&&`${row.title} ${group.title}`.toLowerCase().includes(query))})).filter(x=>x.modules.length);
  const visible=selected.flatMap(x=>x.modules);
  let html='';
  if(sortExact){html=[...visible].sort((a,b)=>b.exact_available_bytes-a.exact_available_bytes).map(row=>`<tr class="module"><td>${esc(row.title)}</td>${metricCells(row)}</tr>`).join('');}
  else{html=selected.map(group=>`<tr class="group"><td>${esc(group.title)}</td>${metricCells(aggregate(group.modules))}</tr>`+group.modules.map(row=>`<tr class="module"><td>${esc(row.title)}</td>${metricCells(row)}</tr>`).join('')).join('');}
  document.querySelector('#modules').innerHTML=html||'<tr><td colspan="6">No matching modules</td></tr>';
  document.querySelector('#module-total').innerHTML=`<tr><td>${visible.length===all.length?'Total':'Filtered total'}</td>${metricCells(aggregate(visible))}</tr>`;
  document.querySelector('#filtered').textContent=`${visible.length} of ${all.length} groups shown · all byte columns are deduplicated; exact total includes local results.`;
 }
 document.querySelector('#search').addEventListener('input',render);document.querySelector('#system').addEventListener('change',render);
 document.querySelector('#active-only').addEventListener('click',event=>{activeOnly=!activeOnly;event.currentTarget.setAttribute('aria-pressed',String(activeOnly));render();});
 document.querySelector('#sort').addEventListener('click',event=>{sortExact=!sortExact;event.currentTarget.textContent=sortExact?'Sort: exact bytes':'Sort: system';render();});
 document.querySelector('#data-scope').textContent=`ROM snapshot ${payload.snapshot_revision}; current activity ${d.as_of}. ${d.classification.provisional} tasks have provisional system-only classification. Window observation: ${fmt(d.windows.last_hour.observed_seconds/60)} / ${fmt(d.windows.previous_hour.observed_seconds/60)} minutes (current / previous).`;
 render();
}
start().catch(error=>{document.querySelector('#error').textContent=error.message;document.querySelector('#updated').textContent='Unavailable';});
