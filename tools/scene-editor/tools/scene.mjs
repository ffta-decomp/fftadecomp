import { readFile, writeFile } from 'node:fs/promises';
import { resolve } from 'node:path';
import { check } from '../src/binary.mjs';
import { catalog } from '../src/rom.mjs';
import { describeStory } from '../src/story.mjs';
import { buildBattleListenerProbe, buildBattleVictoryProbe } from '../src/battle-probes.mjs';
import { build, importProject, inspectRom, openRom, plan, previewBuild } from '../src/project.mjs';

process.stdout.on('error', error => {
  if (error.code === 'EPIPE') process.exit(0);
  throw error;
});

const [, , command, input, ...args] = process.argv;
const json = document => JSON.stringify(document, null, 2) + '\n';
const readJson = async path => JSON.parse(await readFile(path, 'utf8'));

async function main() {
  check(input && ['inspect', 'catalog', 'story', 'project', 'diff', 'build', 'battle-probe'].includes(command),
    'Usage: scene inspect ROM | catalog ROM [--programs] [--dialogue] | story ROM SCENE [PROJECT] [VARIANT] | project ROM | diff ROM PROJECT | build ROM PROJECT OUTPUT | battle-probe ROM OUTPUT [--victory]');
  const romInput = new Uint8Array(await readFile(input));
  if (command === 'inspect') {
    check(!args.length, 'Expected only a ROM path');
    process.stdout.write(json(await inspectRom(romInput)));
    return;
  }
  const { rom, project } = await openRom(romInput);
  if (command === 'battle-probe') {
    check(args.length === 1 || (args.length === 2 && args[1] === '--victory'), 'Expected an output ROM path and optional --victory');
    const compiler = args[1] ? buildBattleVictoryProbe : buildBattleListenerProbe;
    const { bytes, report } = compiler(rom);
    await writeFile(resolve(args[0]), bytes, { flag: 'wx' });
    process.stdout.write(json(report));
    return;
  }
  if (command === 'catalog') {
    check(args.every(arg => arg === '--programs' || arg === '--dialogue'), 'Unknown catalog option');
    process.stdout.write(json(catalog(rom, { includePrograms: args.includes('--programs'), includeDialogue: args.includes('--dialogue') })));
    return;
  }
  if (command === 'story') {
    check(args.length >= 1 && args.length <= 3, 'Expected scene ID, optional project and variant');
    const candidate = args[1] ? importProject(rom, project, await readJson(args[1])) : project;
    process.stdout.write(json(describeStory(rom, plan(rom, candidate), Number(args[0]), args[2] === undefined ? 0 : Number(args[2]))));
    return;
  }
  if (command === 'project') {
    check(!args.length, 'Expected only a ROM path');
    process.stdout.write(json(project));
    return;
  }
  check(args.length === (command === 'build' ? 2 : 1), 'Expected project and output paths');
  const candidate = importProject(rom, project, await readJson(args[0]));
  const report = command === 'build' ? build(rom, candidate) : previewBuild(rom, candidate);
  const { bytes, ...details } = report;
  if (command === 'build') {
    const output = resolve(args[1]);
    check(output !== resolve(input), 'Choose a different path for the generated ROM');
    await writeFile(output, bytes, { flag: 'wx' });
  }
  process.stdout.write(json({ format: 'ffta.scene-diff/v1', baseSha256: rom.sha256, ...details }));
}

main().catch(error => {
  process.stderr.write(error.message + '\n');
  process.exitCode = 1;
});
