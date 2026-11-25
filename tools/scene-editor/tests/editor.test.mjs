import assert from 'node:assert/strict';
import { readFile } from 'node:fs/promises';
import test from 'node:test';
import { eq, u16, u32 } from '../src/binary.mjs';
import { battleEventStep, DEMO_ID, snowballDemo, validateBattleEvent } from '../src/battle.mjs';
import { blankOpening, OPENING_BANNER, OPENING_ID, OPENING_OUTCOME, OPENING_ROSTER, openingExample } from '../src/opening.mjs';
import { buildBattleListenerProbe, buildBattleVictoryProbe } from '../src/battle-probes.mjs';
import { PROFILE } from '../src/profile.mjs';
import { build, importProject, inspectRom, newProject, openRom, plan, previewBuild } from '../src/project.mjs';
import { createPanelRegistry } from '../src/ui/panels.mjs';
import { catalog } from '../src/rom.mjs';
import { describeStory } from '../src/story.mjs';
import { setLanguage, t, tr } from '../src/i18n.mjs';
import { encodeLine, makePage, plainTokens, readLine } from '../src/text.mjs';

test('plain scene dialogue round-trips text, line breaks and its native continuation controls', () => {
  const text = 'A new story!\nSee you soon.';
  const tokens = plainTokens(text);
  const record = encodeLine(tokens, 'standard', 0x32);
  const recovered = readLine(record, 0, record.length);
  assert.equal(recovered.preview, text);
  assert.equal(recovered.flags, 0x30);
  assert.deepEqual(recovered.tokens, tokens);
  assert.deepEqual(tokens.slice(-2).map(token => token.code), [0x40, 0x42]);
  assert.throws(() => plainTokens('新对白'), /Glyph unavailable/);
  assert.throws(() => makePage([new Uint8Array(65535)]), /16-bit/);
});

test('i18n renders labels and interpolated messages without changing project data', () => {
  const project = newProject();
  const before = JSON.stringify(project);
  setLanguage('en');
  assert.equal(t('剧情流程'), 'Story flow');
  assert.equal(tr`查看跳转目标 · 步骤 ${182}`, 'View destination · Step 182');
  setLanguage('zh-CN');
  assert.equal(t('剧情流程'), '剧情流程');
  assert.equal(JSON.stringify(project), before);
});

const source = process.env.FFTA_US_ROM;
test('retail catalog and copy-on-write edits resolve through native pointers', { skip: !source }, async () => {
  const input = new Uint8Array(await readFile(source));
  const { rom, project } = await openRom(input);
  const index = catalog(rom);
  assert.equal(index.scenes.length, 234);
  assert.equal(rom.programs.size, 228);
  assert.equal([...rom.programs.values()].reduce((sum, value) => sum + value.commands.length, 0), 34395);
  assert.equal([...rom.pages.values()].reduce((sum, value) => sum + value.records.length, 0), 9208);
  assert.ok(eq(build(rom, project).bytes, input));

  project.pages[63] = { cloneFrom: '1' };
  project.dialogue['63:0'] = { text: 'A new story begins!' };
  project.dialogue['63:182'] = { text: 'One more line.' };
  project.dialogue['61/0:0'] = { text: 'An independent branch.' };
  const originalStory = describeStory(rom, plan(rom, newProject()), 1);
  const firstSay = originalStory.steps.find(step => step.kind === 'dialogue');
  assert.equal(firstSay.dialogue.line, 0);
  assert.equal(firstSay.speakerHandle, 0x18);
  const instructions = rom.programs.get('0/0').commands.map(({ offset, ...instruction }) => structuredClone(instruction));
  instructions[firstSay.index].operands.textSelector = 182;
  project.programs['0/12'] = { cloneFrom: '0/0', instructions };
  project.scenes[1] = { script: { group: 0, program: 12 }, dialoguePage: 63 };
  project.scenes[234] = { script: { group: 0, program: 12 }, dialoguePage: 63 };
  const out = build(rom, project);
  assert.equal(out.bytes.length, PROFILE.maximumSize);
  assert.ok(out.allocations.every(item => item.offset >= PROFILE.size));
  assert.equal(out.changes.length, 7);

  const originalPrefix = out.bytes.slice(0, PROFILE.size);
  for (const pointer of out.pointers) originalPrefix.set(input.subarray(pointer.offset, pointer.offset + 4), pointer.offset);
  assert.ok(eq(originalPrefix, input), 'Only the native pointer words may change in the retail prefix');

  const { bytes } = out;
  const onBus = site => u32(bytes, site) - PROFILE.bus;
  const relative = (base, at) => (base + u32(bytes, at)) >>> 0;
  const indexStart = onBus(PROFILE.index.pointer);
  const scene = id => [...bytes.subarray(indexStart + id * 4, indexStart + id * 4 + 4)];
  assert.deepEqual(scene(1), [1, 12, 63, 0]);
  assert.deepEqual(scene(234), scene(1));
  const book = onBus(PROFILE.scripts.pointer);
  const group = relative(book, book);
  const command = relative(group, group + 12 * 4);
  const original = rom.programs.get('0/0');
  assert.equal(bytes[command + firstSay.offset + 1], 182);
  const linkedProgram = bytes.slice(command, command + original.end - original.offset);
  linkedProgram[firstSay.offset + 1] = 0;
  assert.ok(eq(linkedProgram, input.subarray(original.offset, original.end)), 'Only the say operand changes in the compiled script clone');
  const editedStory = describeStory(rom, plan(rom, project), 1);
  const editedSay = editedStory.steps.find(step => step.kind === 'dialogue');
  assert.deepEqual(editedSay.dialogue, { page: '63', line: 182, text: 'One more line.' });

  const dialogue = onBus(PROFILE.dialogue.pointer);
  const page = number => relative(dialogue, dialogue + number * 4);
  assert.equal(page(1), rom.pages.get('1').offset, 'Unedited aliased page stays at its retail location');
  assert.equal(page(2), rom.pages.get('2').offset, 'Unrelated page stays at its retail location');
  const line = (pageOffset, number) => {
    const position = pageOffset + u16(bytes, pageOffset + number * 2);
    return readLine(bytes, position, bytes.length);
  };
  assert.equal(line(page(63), 0).preview, 'A new story begins!');
  assert.equal(line(page(63), 182).preview, 'One more line.');
  assert.equal(line(relative(dialogue, page(61)), 0).preview, 'An independent branch.');
  assert.equal(relative(dialogue, page(61) + 4), rom.pages.get('61/1').offset);

  const reopened = await openRom(out.bytes);
  assert.deepEqual(reopened.project, project);
  assert.ok(eq(build(reopened.rom, reopened.project).bytes, out.bytes));
  out.bytes[PROFILE.size + 21] ^= 1;
  await assert.rejects(openRom(out.bytes), /embedded project/);
});

test('bad drafts fail before application and unresolved retail slots can be repaired', { skip: !source }, async () => {
  const { rom, project } = await openRom(await readFile(source));
  const before = structuredClone(project);
  assert.throws(() => importProject(rom, project, { ...newProject(), dialogue: { '1:183': { text: 'Hole' } } }), /hole/);
  assert.throws(() => importProject(rom, project, { ...newProject(), scenes: { 240: { dialoguePage: 1 } } }), /Scene ID/);
  assert.throws(() => importProject(rom, project, { ...newProject(), scenes: { 234: { script: { group: 0, program: 2 }, dialoguePage: 1 } } }), /executable/);
  assert.deepEqual(project, before);
  const repaired = importProject(rom, project, { ...newProject(), scenes: { 108: { script: { group: 0, program: 0 } } } });
  assert.equal(plan(rom, repaired).diffs[0].action, 'replace');
  assert.deepEqual(plan(rom, repaired).diffs[0].after.script, { group: 0, program: 0 });
  const invalid = { ...newProject(), programs: { '0/12': { instructions: [
    { operation: 'adjustScriptOffset', operands: { delta: 5 } },
    { operation: 'finishSceneTask', operands: {} },
  ] } } };
  assert.throws(() => plan(rom, invalid), /instruction boundary/);
});


test('dialogue insertion preserves the native anchor and links to a new text line', { skip: !source }, async () => {
  const { rom, project } = await openRom(await readFile(source));
  const { steps } = describeStory(rom, plan(rom, project), 1);
  const first = steps.find(step => step.kind === 'dialogue');
  project.scenes[1] = { dialoguePage: 63 };
  project.pages[63] = { cloneFrom: '1' };
  project.programs['0/0'] = { insertDialogue: [{ anchorOffset: first.offset, textSelector: 182 }] };
  assert.throws(() => plan(rom, project), /absent line/);
  project.dialogue['63:182'] = { text: 'An inserted line.' };
  const change = plan(rom, project);
  const list = describeStory(rom, change, 1).steps.filter(step => step.kind === 'dialogue');
  assert.deepEqual(list.slice(0, 2).map(step => step.dialogue.line), [182, 0]);
  assert.equal(list[0].speakerHandle, first.speakerHandle);
  const body = change.programs.get('0/0').bytes;
  const base = rom.programs.get('0/0');
  const anchor = first.offset;
  const block = anchor + 3 + u16(body, anchor + 1);
  assert.equal(body[anchor], 0x19);
  assert.deepEqual([...body.slice(block, block + 4)], [0x0f, 182, first.speakerHandle, first.presentationFlags]);
  assert.ok(eq(body.slice(block + 4, block + 8), rom.bytes.slice(base.offset + anchor, base.offset + anchor + 4)));
  const back = u16(body, block + 9) - 0x10000;
  assert.equal(block + 11 + back, anchor + 4);
  assert.ok(eq(body.slice(0, anchor), rom.bytes.slice(base.offset, base.offset + anchor)));
  assert.ok(eq(body.slice(anchor + 4, base.end - base.offset), rom.bytes.slice(base.offset + anchor + 4, base.end)));
});


test('snowball rule fires once, resumes after dialogue, and wins on the spawned unit', () => {
  const rule = validateBattleEvent(DEMO_ID, snowballDemo());
  const step = (phase, kind, target, damage) => battleEventStep(rule, phase, { kind, target, damage });
  assert.equal(step('waiting', 'damageResolved', 'mewt', 0).phase, 'waiting');
  assert.equal(step('waiting', 'damageResolved', 'other', 1).phase, 'waiting');
  assert.equal(step('waiting', 'unitDefeated', 'goblin').phase, 'waiting');
  const hit = step('waiting', 'damageResolved', 'mewt', 1);
  assert.equal(hit.phase, 'speaking');
  assert.deepEqual(hit.outputs.map(item => item.kind), ['spawnBattleUnit', 'speakAsBattleUnit']);
  assert.equal(hit.outputs[0].hp, 3);
  assert.equal(hit.outputs[0].attack, 1);
  assert.equal(step('speaking', 'unitDefeated', 'goblin').phase, 'speaking');
  assert.equal(step('speaking', 'dialogueClosed').phase, 'fighting');
  assert.equal(step('fighting', 'damageResolved', 'mewt', 1).outputs.length, 0);
  assert.equal(step('fighting', 'unitDefeated', 'other').phase, 'fighting');
  assert.equal(step('fighting', 'unitDefeated', 'goblin').phase, 'won');
});

test('battle draft is saved and reviewed without leaking a partial game build', { skip: !source }, async () => {
  const { rom, project } = await openRom(await readFile(source));
  const after = importProject(rom, project, { ...newProject(), battleEvents: { [DEMO_ID]: snowballDemo() } });
  const report = previewBuild(rom, after);
  assert.equal(report.buildable, false);
  assert.equal(report.changes[0].kind, 'battle');
  assert.equal(report.changes[0].after.spawn.hp, 3);
  assert.equal(report.battleCapabilities[0].state, 'rom-probe');
  assert.throws(() => build(rom, after), /battle event is a draft/);
  const probe = buildBattleListenerProbe(rom);
  assert.equal(probe.bytes.length, PROFILE.maximumSize);
  assert.equal(probe.report.markerAddress, 0x0900002c);
  assert.equal(u32(probe.bytes, probe.report.hookOffset + 4), 0x09000001);
  const prefix = probe.bytes.slice(0, PROFILE.size);
  prefix.set(rom.bytes.subarray(probe.report.hookOffset, probe.report.hookOffset + 8), probe.report.hookOffset);
  assert.ok(eq(prefix, rom.bytes));
  const goal = buildBattleVictoryProbe(rom);
  assert.equal(goal.report.targetSelector, 76);
  assert.equal(u32(goal.bytes, 0xa148), 0x09000000);
  const victoryByte = PROFILE.size + 0xa1b318 - 0xa1a908;
  assert.equal(goal.bytes[victoryByte], 76);
  const archive = goal.bytes.slice(PROFILE.size, PROFILE.size + (0xa1b90c - 0xa1a908));
  archive[victoryByte - PROFILE.size] = 16;
  assert.ok(eq(archive, rom.bytes.subarray(0xa1a908, 0xa1b90c)));
});

test('authored opening exports a relocated roster and reconstructs its declarative project', { skip: !source }, async () => {
  const input = new Uint8Array(await readFile(source));
  const { rom, project } = await openRom(input);
  project.openings[OPENING_ID] = blankOpening();
  project.openings[OPENING_ID].battleIntro = '';
  project.openings[OPENING_ID].battleEnding = '';
  assert.equal(build(rom, project).bytes.length, PROFILE.maximumSize);

  project.openings[OPENING_ID] = openingExample();
  const changes = plan(rom, project);
  assert.equal(changes.scenes.get(1).dialoguePage, changes.scenes.get(6).dialoguePage);
  const start = changes.programs.get('0/0').commands;
  assert.ok(start.some(command => command.operation === 'moveActorOnGrid'));
  assert.deepEqual(start.filter(command => command.operation === 'say').map(command => command.operands.speakerHandle), [15, 128]);
  assert.ok(!changes.programs.get('0/5').commands.some(command => command.operation === 'applySceneMode'));
  const output = build(rom, project);
  const roster = output.allocations.find(item => item.kind === 'encounterRoster');
  assert.ok(roster.offset >= PROFILE.size);
  assert.equal(u32(output.bytes, OPENING_ROSTER.pointer), PROFILE.bus + roster.offset);
  assert.deepEqual([0, 1, 2, 3].map(slot => output.bytes[roster.offset + slot * 48 + 1]), [45, 44, 44, 44]);
  const banner = output.allocations.find(item => item.kind === 'battleBanner');
  assert.equal(u32(output.bytes, OPENING_BANNER.pointer), PROFILE.bus + banner.offset);
  const bannerTable = output.bytes.slice(banner.offset, banner.offset + banner.length);
  assert.equal(bannerTable[OPENING_BANNER.categoryOffset], 1);
  bannerTable[OPENING_BANNER.categoryOffset] = 5;
  assert.ok(eq(bannerTable, input.subarray(OPENING_BANNER.start, OPENING_BANNER.end)));
  const outcome = output.allocations.find(item => item.kind === 'battleOutcome');
  assert.equal(u32(output.bytes, OPENING_OUTCOME.pointer), PROFILE.bus + outcome.offset);
  const group = outcome.offset + OPENING_OUTCOME.group - OPENING_OUTCOME.start;
  assert.equal(group + u16(output.bytes, group + 2), outcome.offset + OPENING_OUTCOME.end - OPENING_OUTCOME.start);
  assert.equal(changes.programs.get('0/1').commands.find(command => command.operation === 'queueScene').operands.scene, 4);
  const prefix = output.bytes.slice(0, PROFILE.size);
  for (const pointer of output.pointers) prefix.set(input.subarray(pointer.offset, pointer.offset + 4), pointer.offset);
  assert.ok(eq(prefix, input));
  assert.deepEqual((await openRom(output.bytes)).project, project);

  project.openings[OPENING_ID].cast = [];
  assert.throws(() => plan(rom, project), /actor from the cast/);
});


test('workspace modules register in order with unique, stable IDs', () => {
  const render = () => {};
  const story = { id: 'story', label: 'Story', render };
  const jobs = { id: 'jobs', label: 'Jobs', render };
  const registry = createPanelRegistry([story, jobs]);
  assert.deepEqual(registry.list.map(panel => panel.id), ['story', 'jobs']);
  assert.equal(registry.get('jobs').render, render);
  assert.throws(() => createPanelRegistry([story, story]), /Duplicate workspace panel/);
});

test('an unidentified expanded cartridge is reported without enabling edits', async () => {
  const input = new Uint8Array(PROFILE.maximumSize);
  input.set([65, 70, 88, 69], 0xac);
  const result = await inspectRom(input);
  assert.equal(result.gameCode, 'AFXE');
  assert.equal(result.editable, false);
  assert.match(result.reason, /expanded ROM/);
});

test('same-layout mods keep their own identity and untouched data', { skip: !source }, async () => {
  const input = Uint8Array.from(await readFile(source));
  const unrelatedData = 0x400000;
  input[unrelatedData] ^= 1;
  const { rom, project } = await openRom(input);
  assert.equal(project.profile, PROFILE.compatibleId);
  assert.equal(project.baseSha256, rom.sha256);
  assert.notEqual(rom.sha256, PROFILE.sha256);
  assert.deepEqual(build(rom, project).bytes, input);

  project.dialogue['1:0'] = { text: 'A new line.' };
  const output = build(rom, project).bytes;
  assert.equal(output[unrelatedData], input[unrelatedData]);
  const reopened = await openRom(output);
  assert.deepEqual(reopened.project, project);
  assert.deepEqual(reopened.rom.bytes, input);
  assert.throws(() => importProject(rom, project, newProject()), /profile mismatch/);
  project.openings[OPENING_ID] = openingExample();
  assert.throws(() => plan(rom, project), /verified retail profile/);

  input[0x1000] ^= 1;
  await assert.rejects(openRom(input), /changes the US engine/);
});
