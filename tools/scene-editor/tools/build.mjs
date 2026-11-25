import { mkdir, readFile, writeFile } from 'node:fs/promises';
import { dirname, resolve } from 'node:path';
import { fileURLToPath } from 'node:url';

const root = new URL('../', import.meta.url);
const sourceRoot = new URL('src/', root);
const read = url => readFile(url, 'utf8');
const map = {};

async function include(url) {
  if (!url.href.startsWith(sourceRoot.href)) throw new Error('Offline bundle imports must stay under src/');
  const name = 'ffta/' + url.href.slice(sourceRoot.href.length);
  if (Object.hasOwn(map, name)) return name;

  map[name] = '';
  const source = await read(url);
  const imports = /\bfrom\s+(['"])(\.{1,2}\/[^'"]+\.mjs)\1/g;
  const dependencies = new Map();
  for (const [, , specifier] of source.matchAll(imports)) {
    if (!dependencies.has(specifier)) dependencies.set(specifier, await include(new URL(specifier, url)));
  }
  const bundled = source.replace(imports, (_, quote, specifier) => `from ${quote}${dependencies.get(specifier)}${quote}`);
  map[name] = 'data:text/javascript;base64,' + Buffer.from(bundled).toString('base64');
  return name;
}

const entry = await include(new URL('app.mjs', sourceRoot));
const html = (await read(new URL('index.html', root)))
  .replace('<link rel="stylesheet" href="./style.css">', `<style>\n${await read(new URL('style.css', root))}\n</style>`)
  .replace('<script type="module" src="./src/app.mjs"></script>',
    `<script type="importmap">${JSON.stringify({ imports: map })}</script>\n<script type="module">import "${entry}";</script>`);
const output = process.argv[2] ? resolve(process.argv[2]) : fileURLToPath(new URL('dist/ffta-scene-editor.html', root));
await mkdir(dirname(output), { recursive: true });
await writeFile(output, html);
console.log(output);
