/* Aggregate activity only. The verified ROM snapshot is a separate accounting gate. */
(async () => {
  const escape = value => String(value).replace(/[&<>"']/g, c => ({'&':'&amp;','<':'&lt;','>':'&gt;','"':'&quot;',"'":'&#39;'}[c]));
  const number = value => value === null ? '—' : Number(value).toLocaleString('en-US', {maximumFractionDigits: 1});
  const load = async path => {const response = await fetch(path, {cache:'no-cache'}); if (!response.ok) throw new Error('Activity snapshot unavailable'); return response.json();};
  try {
    const [data, catalog] = await Promise.all([load('data/workflow.json'), load('data/submodules.json')]);
    const ageHours = (Date.now() - Date.parse(data.as_of)) / 3600000;
    document.querySelector('#activity-date').textContent = `Updated ${new Date(data.as_of).toLocaleString()}${ageHours > 2 ? ' · delayed update' : ''}`;
    const gates = [
      ['local_exact','Local whole-function exact'], ['peer_exact','Independently accepted exact'],
      ['integrated_exact','Integrated exact'], ['local_semantic','New semantic C'], ['integrated','All integrated C']
    ];
    document.querySelector('#activity-speed').innerHTML = `<table><caption class="sr-only">Registered recovery delivery speed</caption><thead><tr><th>Gate</th><th>Retained B</th><th>Last hour methods</th><th>Last hour B/h</th><th>Previous B/h</th></tr></thead><tbody>${gates.map(([id,title]) => {
      const row = data.totals.gates[id];
      return `<tr><td>${title}</td><td>${number(row.retained.original_bytes)}</td><td>${number(row.last_hour.functions)}</td><td>${number(row.last_hour.original_B_per_hour)}</td><td>${number(row.previous_hour.original_B_per_hour)}</td></tr>`;
    }).join('')}</tbody></table>`;
    const round = data.rounds.last_hour;
    const classification = data.totals.classification;
    document.querySelector('#activity-summary').textContent = `${data.totals.tasks} scoped tasks: ${classification.mapped} mapped to submodules, ${classification.provisional} provisional system-only, ${classification.unmapped} unclassified. Last-hour decision median ${number(round.median_seconds)}s / p90 ${number(round.p90_seconds)}s (${round.completed_decision_intervals} samples).`;
    document.querySelector('#activity-lanes').innerHTML = `<table><thead><tr><th>Implementation lane</th><th>Active tasks</th><th>Local exact B/h</th><th>Peer exact B/h</th><th>Integrated exact B/h</th></tr></thead><tbody>${data.actors.filter(x=>x.id!=='other'||x.active_tasks).map(x => `<tr><td>${escape(x.id)}</td><td>${x.active_tasks}</td>${['local_exact','peer_exact','integrated_exact'].map(g=>`<td>${number(x.delivery[g].last_hour.original_B_per_hour)}</td>`).join('')}</tr>`).join('')}</tbody></table>`;
    const titles = Object.fromEntries(catalog.groups.map(x=>[x.id,x.title]));
    document.querySelector('#activity-systems').innerHTML = `<table><thead><tr><th>System</th><th>Ready</th><th>Active</th><th>Frozen</th><th>Blocked</th><th>Local exact B/h</th><th>Provisional tasks</th></tr></thead><tbody>${data.systems.filter(x=>x.tasks).map(x=>`<tr><td>${escape(titles[x.id]||'Unclassified')}</td>${['ready','active','frozen','blocked'].map(s=>`<td>${x.states[s]}</td>`).join('')}<td>${number(x.gates.local_exact.last_hour.original_B_per_hour)}</td><td>${x.classification.provisional}</td></tr>`).join('')}</tbody></table>`;
    const rows = data.submodules.filter(x=>x.tasks);
    const moduleTitles = Object.fromEntries(catalog.submodules.map(x=>[x.id,x.title]));
    document.querySelector('#activity-submodules').innerHTML = `<table><thead><tr><th>Submodule</th><th>Scoped tasks</th><th>Active</th><th>Frozen / blocked</th><th>Local exact retained B</th><th>Local exact B/h</th><th>Peer exact retained B</th><th>Integrated exact retained B</th></tr></thead><tbody>${rows.map(x=>`<tr><td>${escape(moduleTitles[x.id]||x.id)}</td><td>${x.tasks}</td><td>${x.states.active}</td><td>${x.states.frozen} / ${x.states.blocked}</td><td>${number(x.gates.local_exact.retained.original_bytes)}</td><td>${number(x.gates.local_exact.last_hour.original_B_per_hour)}</td><td>${number(x.gates.peer_exact.retained.original_bytes)}</td><td>${number(x.gates.integrated_exact.retained.original_bytes)}</td></tr>`).join('')}</tbody></table>`;
    document.querySelector('#activity-limits').textContent = `Registered credits only; missing historical receipts can undercount results. ${data.recording_gaps.pending_peer_exact} local-exact methods await registered peer credit. Frozen does not mean accepted. Last/previous windows observe ${number(data.windows.last_hour.observed_seconds/60)} / ${number(data.windows.previous_hour.observed_seconds/60)} minutes. Pending results are excluded from the verified ROM snapshot; gate columns are not additive. Provisional tasks have no assigned submodule. Whole-system completion remains unknown.`;
  } catch (error) {
    document.querySelector('#activity-date').textContent = error.message;
  }
})();
