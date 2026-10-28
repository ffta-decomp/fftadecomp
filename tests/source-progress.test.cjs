'use strict';
const assert=require('node:assert/strict'),fs=require('node:fs'),vm=require('node:vm');
async function check(bad){
 const nodes=new Map(),el=id=>{if(!nodes.has(id))nodes.set(id,{textContent:'',innerHTML:'',value:'14',addEventListener(){},setAttribute(){}});return nodes.get(id)};
 const context=vm.createContext({Date,document:{querySelector:el},fetch:async url=>({ok:true,json:async()=>{const d=JSON.parse(fs.readFileSync(url));if(bad&&url.includes('completed-build'))d.compiled_original_bytes++;return d}})});
 vm.runInContext(fs.readFileSync('app.js','utf8'),context);await new Promise(setImmediate);
 if(bad){assert.equal(el('#source-overview').innerHTML,'');assert.match(el('#source-scope').textContent,/unavailable/)}
 else {assert.match(el('#source-overview').innerHTML,/36\.654/);assert.match(el('#source-overview').innerHTML,/1,278,650/);assert.match(el('#source-overview').innerHTML,/468,682/);assert.match(el('#source-overview').innerHTML,/161,102/);assert.match(el('#source-scope').textContent,/do not add/)}
}
(async()=>{await check(false);await check(true);console.log('Verified source totals and mismatched-proof refusal passed')})().catch(e=>{console.error(e);process.exitCode=1});
