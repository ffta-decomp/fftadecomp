'use strict';
(async()=>{
  const data=await fetch('data/functions.json').then(r=>{if(!r.ok)throw Error('Catalogue unavailable');return r.json()});
  const group=document.getElementById('group'),find=document.getElementById('find');let page=0;
  for(const g of data.groups){const opt=document.createElement('option');opt.value=g.id;opt.textContent=`${g.priority}. ${g.id} (${g.state})`;group.append(opt)}
  function render(){
    const q=find.value.trim().toLowerCase(),rows=data.functions.filter(f=>(group.value==='all'||f.group===group.value)&&[f.name,f.id,f.address].some(v=>v.toLowerCase().includes(q))).sort((a,b)=>a.original_bytes-b.original_bytes||a.rom_offset-b.rom_offset);
    page=Math.max(0,Math.min(page,Math.max(0,Math.ceil(rows.length/100)-1)));const body=document.getElementById('functions');body.replaceChildren();
    for(const f of rows.slice(page*100,page*100+100)){
      const tr=document.createElement('tr');for(const text of [`${f.name}\n${f.id}`,`${f.group} / ${f.semantic_group}`,f.address,`${f.original_bytes} (${f.entry_kind})`,f.recorded_state]){const td=document.createElement('td');td.textContent=text;tr.append(td)}
      const td=document.createElement('td');if(f.entry_kind==='declared_function'&&f.group===data.active_group&&['unassessed','queued_internal'].includes(f.recorded_state)){
        const a=document.createElement('a');const url=new URL('https://github.com/ffta-decomp/fftadecomp/issues/new');url.searchParams.set('template','group-function-claim.yml');url.searchParams.set('title',`[Claim] ${f.address} — ${f.name} / ${f.id}`);a.href=url.toString();a.textContent='Request';td.append(a)
      }else td.textContent='Check status';tr.append(td);body.append(tr)
    }
    document.getElementById('summary').textContent=`${rows.length} entries · page ${page+1} · snapshot ${data.as_of}`;document.getElementById('previous').disabled=page===0;document.getElementById('next').disabled=(page+1)*100>=rows.length
  }
  document.getElementById('scope').textContent=data.scope;group.onchange=find.oninput=()=>{page=0;render()};document.getElementById('previous').onclick=()=>{page--;render()};document.getElementById('next').onclick=()=>{page++;render()};group.value=data.active_group;render()
})().catch(e=>{document.getElementById('error').textContent=e.message});
