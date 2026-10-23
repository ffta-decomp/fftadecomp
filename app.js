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
function renderDaily(daily){
 const summary=document.querySelector('#daily-summary'),chart=document.querySelector('#daily-chart'),body=document.querySelector('#daily-rows');
 function render(){
  if(!daily?.days?.length || !daily.known_original_asm_bytes){
   summary.textContent='Dated decompilation history is unavailable for this snapshot.';
   body.innerHTML='<tr><td colspan="8">No verified daily data</td></tr>';chart.innerHTML='';return;
  }
  const range=document.querySelector('#daily-range').value,rows=range==='all'?daily.days:daily.days.slice(-Number(range));
  const total=rows.reduce((sum,row)=>sum+row.new_exact_asm_bytes,0),last=rows.at(-1);
  summary.textContent=`${fmt(total)} original ASM bytes newly matched across ${rows.length} displayed days · ${fmt(last.cumulative_registered_exact_asm_bytes)} B with dated local receipts · ${fmt(daily.current_exact_asm_bytes_without_local_date)} B of current progress without a local delivery date.`;
  body.innerHTML=[...rows].reverse().map(row=>`<tr><td>${esc(row.date)}${row.partial?' · in progress':''}</td><td>${fmt(row.new_exact_methods)}</td><td>${fmt(row.new_pure_c_asm_bytes)}</td><td>${fmt(row.new_eligible_mixed_asm_bytes)}</td><td class="exact">${fmt(row.new_exact_asm_bytes)}</td><td>${fmt(row.new_integrated_asm_bytes)}</td><td>${fmt(row.cumulative_registered_exact_asm_bytes)}</td><td>${row.registered_percent==null?'—':row.registered_percent.toFixed(3)+'%'}</td></tr>`).join('');
  const width=1000,height=230,left=74,right=24,top=26,bottom=40;
  const max=Math.max(1,...rows.flatMap(row=>[row.cumulative_registered_exact_asm_bytes,row.cumulative_registered_integrated_asm_bytes]));
  const x=i=>left+(width-left-right)*(rows.length===1?.5:i/(rows.length-1));
  const y=value=>height-bottom-(height-top-bottom)*value/max;
  const path=key=>rows.map((row,i)=>`${i?'L':'M'}${x(i).toFixed(1)},${y(row[key]).toFixed(1)}`).join(' ');
  const ticks=[0,.5,1].map(t=>`<line x1="${left}" x2="${width-right}" y1="${y(max*t)}" y2="${y(max*t)}" class="grid"/><text x="${left-10}" y="${y(max*t)+4}" text-anchor="end">${fmt(max*t)} B</text>`).join('');
  chart.innerHTML=`<svg viewBox="0 0 ${width} ${height}" role="img" aria-labelledby="daily-chart-title daily-chart-desc"><title id="daily-chart-title">Cumulative dated decompilation progress</title><desc id="daily-chart-desc">Original ASM bytes with dated local exact and integration receipts. The table below provides each day's values. Missing historical receipts are excluded.</desc>${ticks}<path class="local-line" d="${path('cumulative_registered_exact_asm_bytes')}"/><path class="integrated-line" d="${path('cumulative_registered_integrated_asm_bytes')}"/>${rows.map((row,i)=>`<circle class="local-point" cx="${x(i)}" cy="${y(row.cumulative_registered_exact_asm_bytes)}" r="3"><title>${esc(row.date)}: ${fmt(row.cumulative_registered_exact_asm_bytes)} B matched; ${fmt(row.new_exact_asm_bytes)} B new</title></circle>`).join('')}<text x="${left}" y="${height-10}">${esc(rows[0].date)}</text>${rows.length>1?`<text x="${width-right}" y="${height-10}" text-anchor="end">${esc(last.date)}</text>`:''}</svg><p class="chart-legend"><span>━ Dated local exact</span><span>┄ Dated integration</span></p>`;
  document.querySelector('#daily-scope').textContent=`Cumulative values cover dated ledger receipts only, divided by ${fmt(daily.known_original_asm_bytes)} known original ASM bytes; this is not whole-game completion. Pure C and eligible mixed are separate. Integration is a separate gate, not additional recovery. Missing history is unknown; revoked receipts are removed. The current day is partial.`;
 }
 document.querySelector('#daily-range').addEventListener('change',render);render();
}
async function start(){
 const response=await fetch('data/progress.json',{cache:'no-cache'});if(!response.ok)throw new Error('Could not load current progress');
 const payload=await response.json(),d=payload.dashboard;if(d?.schema_version!==2)throw new Error('Unified progress snapshot unavailable');
 renderDaily(d.daily);
 const age=(Date.now()-Date.parse(d.as_of))/3600000;
 document.querySelector('#updated').textContent=`${new Date(d.as_of).toLocaleString()}${age>2?' · update delayed':''}`;
 const names={team:'All lanes',main:'Main',worker2:'Worker 2',worker3:'Worker 3',sol_a:'Sol A',sol_b:'Sol B',sol_c:'Sol C',astra_handoff:'Astra handoff',other:'Other actors'};
 document.querySelector('#performance').innerHTML=d.performance.map(row=>`<tr class="${row.id==='team'?'team':''}"><td class="${row.id==='team'?'':'lane'}">${esc(names[row.id]||row.id)}</td><td>${fmt(row.exact_B_per_hour)}</td><td>${fmt(row.previous_exact_B_per_hour)}</td><td>${fmt(row.exact_methods_last_hour)}</td><td>${fmt(row.peer_exact_B_per_hour)}</td><td>${fmt(row.integrated_exact_B_per_hour)}</td><td>${fmt(row.median_seconds)} / ${fmt(row.p90_seconds)} s</td></tr>`).join('');
 const o=d.overview,m=d.asm_rewrite||d.c_match;
 document.querySelector('#overview').innerHTML=[
  ['Original ASM rewritten',m?.percent == null ? 'Unknown' : m.percent.toFixed(3),'%',m?.percent == null ? 'Original ASM catalogue unavailable' : `${fmt(m.rewritten_original_asm_bytes??m.matched_asm_bytes)} / ${fmt(m.known_original_asm_bytes??m.total_asm_bytes)} known original ASM bytes`],
  ['Original ASM matched',fmt(o.exact_available_bytes),'B',`${fmt(o.integrated_exact_bytes)} in ROM + ${fmt(o.pending_exact_bytes)} local`],
  ['Generated C in ROM',fmt(o.integrated_c_bytes),'B',`${fmt(o.mixed_bytes)} mixed C / ASM bytes tracked separately`],
  ['Matched ASM awaiting integration',fmt(o.pending_exact_bytes),'B',`${fmt(o.pending_peer_exact_bytes)} independently accepted bytes`],
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
