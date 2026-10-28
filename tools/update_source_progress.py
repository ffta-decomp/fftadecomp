"""Generate public source coverage from disjoint verified modules and code ranges."""
import hashlib
import json
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
def union(ranges):
    result=[]
    for start,end in sorted(ranges):
        if start<0 or end<=start: raise ValueError('Invalid original range')
        if result and start<=result[-1][1]: result[-1][1]=max(end,result[-1][1])
        else: result.append([start,end])
    return result
def measure(ranges): return sum(b-a for a,b in union(ranges))
def generate():
    load=lambda name:json.loads((ROOT/name).read_text())
    index=load('src/completed-index.json'); proof=load('data/completed-build-validation.json');catalogue=load('data/original-code-catalogue.json')
    assert proof['whole_image_identical'] and proof['input_sha256']==proof['output_sha256']==index['retail_sha256']==catalogue['retail_sha256']
    rows=index['modules'];spans=[[r['rom_offset'],r['rom_offset']+r['original_bytes']] for r in rows]
    covered=measure(spans)
    assert covered==sum(r['original_bytes'] for r in rows)==proof['compiled_original_bytes']
    assert len(rows)==proof['source_module_count']
    assert hashlib.sha256((ROOT/'src/completed-index.json').read_bytes()).hexdigest()==proof['published_input_hashes']['src/completed-index.json']
    ranges=union(catalogue['ranges']+spans);total=measure(ranges)
    return {'schema':'published-source-progress-v1','verified_date':proof['verified_date'],'scope':catalogue['scope'],'published_original_bytes':covered,'known_original_code_bytes':total,'percent':100*covered/total,'modules':len(rows),'historical_catalogue_bytes':measure(catalogue['ranges']),'verified_source_extension_bytes':total-measure(catalogue['ranges']),'upstream_import_original_bytes':sum(r['original_bytes'] for r in rows if r.get('origin')=='upstream_import'),'denominator_id':hashlib.sha256(json.dumps(ranges,separators=(',',':')).encode()).hexdigest(),'inputs':{name:hashlib.sha256((ROOT/name).read_bytes()).hexdigest() for name in ['src/completed-index.json','data/completed-build-validation.json','data/original-code-catalogue.json']}}
if __name__=='__main__':
    (ROOT/'data/published-source-progress.json').write_text(json.dumps(generate(),indent=2)+'\n')
