import { check, hex } from './binary.mjs';
import { PROFILE } from './profile.mjs';
import { catalog, lineKey, pageKey, programKey } from './rom.mjs';
import { BATTLE_SCENE } from './battle.mjs';
import { buildBattleListenerProbe } from './battle-probes.mjs';
import { build, importProject, inspectRom, openRom, plan, previewBuild } from './project.mjs';
import { localizeShell, t, tr } from './i18n.mjs';
import { describeStory } from './story.mjs';
import { $, button, dialog, download, downloadJson, el, field, handle, notice, number, section,
  serialize, table, textarea } from './ui/controls.mjs';
import { createBattleEventPanel } from './ui/battle-event.mjs';
import { createCutscenePanel } from './ui/cutscene.mjs';
import { createPanelRegistry } from './ui/panels.mjs';

const localize = localizeShell(document.body);
const state = { rom: null, name: '', project: null, plan: null, scenes: [], selected: 1, tab: 'story', page: null,
  query: '', filter: 'all', undo: [], redo: [], saved: '' };
const statusKeys = { added: '新增', unresolved: '待补全', changed: '已修改', retail: '原版' };
const keySort = (a, b) => a.localeCompare(b, 'en', { numeric: true });

function update(project) {
  state.plan = plan(state.rom, project);
  state.project = project;
  const ids = new Set([...state.rom.scenes.map(scene => scene.id), ...state.plan.scenes.keys()]);
  state.scenes = Array.from(ids, id => state.plan.scenes.get(id) ?? state.rom.scenes[id])
    .filter(scene => scene.id !== 0);
  if (!state.scenes.some(scene => scene.id === state.selected)) {
    state.selected = state.scenes[0].id;
    state.page = null;
  }
  render();
}

function commit(project) {
  plan(state.rom, project);
  if (serialize(project) === serialize(state.project)) return;
  state.undo.push(state.project);
  state.redo = [];
  update(project);
}

function editCollection(collection, key, entry) {
  const project = structuredClone(state.project);
  project[collection][key] = entry;
  commit(project);
}

function restore(collection, key) {
  const project = structuredClone(state.project);
  delete project[collection][key];
  commit(project);
}

async function load(bytes, name) {
  const { rom, project } = await openRom(bytes);
  Object.assign(state, { rom, name, selected: 1, tab: 'story', page: null, query: '', filter: 'all',
    undo: [], redo: [], saved: serialize(project) });
  $('#search').value = '';
  $('#filter').value = 'all';
  update(project);
  notice(t('ROM 就绪'));
}

function currentScene() {
  return state.scenes.find(scene => scene.id === state.selected);
}

function activePage(scene) {
  return pageKey(scene.dialoguePage, scene.dialoguePage === PROFILE.dialogue.nested ? 0 : null);
}

function pageRecords(key) {
  const page = state.plan.pages.get(key) ?? state.rom.pages.get(key);
  if (!page) return [];
  const records = page.records.slice();
  for (const change of state.plan.diffs) {
    if (change.kind !== 'dialogue') continue;
    const [address, index] = change.target.split(':');
    if (address === key) records[Number(index)] = { ...change.after, index: Number(index), preview: change.after.text, edited: true };
  }
  return records;
}

function programFor(scene) {
  const key = programKey(scene.script.group, scene.script.program);
  const changed = state.plan.programs.get(key);
  if (changed) return { commands: changed.commands, insertions: changed.insertions };
  return state.rom.programs.get(key);
}

function sceneStatus(scene) {
  if (scene.id >= PROFILE.index.count) return ['added', false];
  if (scene.id === BATTLE_SCENE && state.plan.battles.size) return ['changed', false];
  if (!programFor(scene)?.commands.length) return ['unresolved', true];
  if (state.plan.scenes.has(scene.id) || state.plan.programs.has(programKey(scene.script.group, scene.script.program)) ||
    state.plan.dialogue.has(activePage(scene))) return ['changed', false];
  return ['retail', false];
}

function renderList() {
  if (!state.rom) return;
  const nav = $('#scene-list');
  const scroll = nav.scrollTop;
  const fragment = document.createDocumentFragment();
  let count = 0;
  for (const scene of state.scenes) {
    const [status, warning] = sceneStatus(scene);
    const firstLine = programFor(scene)?.commands.find(command => command.operation === 'say' && command.operands.textSelector <= 239);
    const text = (readableDialogue(pageRecords(activePage(scene))[firstLine?.operands.textSelector]?.preview) ?? '').replace(/\s+/g, ' ');
    if (state.filter === 'changed' && !['changed', 'added'].includes(status)) continue;
    if (state.filter === 'unresolved' && !warning) continue;
    const query = state.query.trim().toLowerCase();
    if (query && ![String(scene.id), hex(scene.id), text.toLowerCase()].some(value => value.includes(query))) continue;
    const row = button('', () => {
      state.selected = scene.id;
      const { preferredScene } = panels.get(state.tab);
      if (preferredScene !== undefined && scene.id !== preferredScene) state.tab = 'story';
      state.page = null;
      render();
    }, 'scene-link');
    row.dataset.scene = scene.id;
    if (scene.id === state.selected) row.setAttribute('aria-current', 'true');
    row.append(el('span', String(scene.id).padStart(3, '0'), 'id'), el('span', text || t(statusKeys[status]), 'excerpt'));
    if (status !== 'retail') row.append(el('span', warning ? '◇' : '●', 'dot'));
    fragment.append(row);
    count++;
  }
  if (!count) fragment.append(el('p', t('没有匹配的场景。'), 'note'));
  nav.replaceChildren(fragment);
  nav.scrollTop = scroll;
  $('#scene-count').hidden = !state.query.trim() && state.filter === 'all';
  $('#scene-count').textContent = tr`${count} / ${state.scenes.length} 个可浏览条目`;
}

function render() {
  const ready = Boolean(state.rom);
  $('#welcome').hidden = ready;
  if (!ready) $('#rom-name').textContent = t('未载入 ROM');
  $('#workspace').hidden = !ready;
  document.querySelectorAll('[data-needs-rom]').forEach(node => { node.disabled = !ready; });
  if (!ready) return;
  $('#rom-name').textContent = state.name;
  renderList();
  const scene = currentScene();
  const [status, warning] = sceneStatus(scene);
  $('#crumb-scene').textContent = String(scene.id);
  const panel = panels.get(state.tab);
  $('#scene-title').textContent = panel.title?.(scene) ?? tr`场景 ${String(scene.id).padStart(3, '0')}`;
  $('#scene-status').textContent = t(statusKeys[status]);
  $('#scene-status').classList.toggle('warn', warning);
  $('#scene-meta').hidden = panel.showMetadata === false;
  $('#scene-meta').textContent = tr`脚本 ${programKey(scene.script.group, scene.script.program)} · 对白页 ${scene.dialoguePage}`;
  $('#undo').disabled = !state.undo.length;
  $('#redo').disabled = !state.redo.length;
  $('#footer-status').textContent = serialize(state.project) === state.saved ? t('项目已保存或无改动') : t('项目有未保存的编辑');
  for (const { panel, element } of tabs) {
    const count = panel.id === 'diff' && state.plan.diffs.length;
    element.textContent = t(panel.label) + (count ? ` ${count}` : '');
    element.hidden = panel.retailOnly === true && state.rom.profile !== PROFILE.id;
    element.setAttribute('aria-selected', String(panel.id === state.tab));
  }
  const body = $('#detail-body');
  body.replaceChildren();
  panel.render(body, scene);
}

function readableDialogue(text) {
  return text?.replace(/〈0x[0-9a-f]+:\d+〉/gi, '〈…〉').replace(/⟨0x[0-9a-f]+⟩/gi, '□');
}

function renderStory(body, scene) {
  const selectedVariant = state.page?.startsWith(`${PROFILE.dialogue.nested}/`) ? Number(state.page.split('/')[1]) : 0;
  const story = describeStory(state.rom, state.plan, scene.id, selectedVariant);
  const program = programFor(scene);
  body.append(section(t('剧情流程'), button(t('编辑索引'), () => editIndex(scene)),
    button(t('复制为新场景'), () => createScene(scene))));

  if (scene.dialoguePage === PROFILE.dialogue.nested) {
    const variants = el('select');
    variants.setAttribute('aria-label', t('对白变体'));
    for (let i = 0; i < PROFILE.dialogue.variants; i++) {
      const option = el('option', tr`对白变体 ${i}`);
      option.value = pageKey(scene.dialoguePage, i);
      variants.append(option);
    }
    variants.value = story.page;
    variants.onchange = () => { state.page = variants.value; render(); };
    body.append(variants);
  }
  if (!story.steps.length) {
    body.append(el('p', t('当前索引没有可执行的脚本。可以在索引页重新关联，或在此补全有效的程序。'), 'note'),
      button(t('编辑结构化脚本'), () => editScript(scene), 'accent'));
    return;
  }
  const flow = el('ol', undefined, 'story-flow');
  const key = programKey(scene.script.group, scene.script.program);
  const hasDialogue = story.steps.some(step => step.kind === 'dialogue');
  let interlude;
  let lineNumber = 0;
  for (const step of story.steps) {
    const item = el('li', undefined, `step ${step.kind}`);
    item.id = step.insertionIndex === undefined ? `step-${step.offset}` : `insertion-${step.insertionIndex}`;
    const heading = el('div', undefined, 'step-head');
    const type = { dialogue: '对白', native: '原生步骤', branch: '分支', action: '动作', end: '结束' };
    heading.append(el('strong', step.kind === 'dialogue'
      ? tr`对白 ${++lineNumber}`
      : t(type[step.kind])));
    item.append(heading);
    if (step.kind === 'dialogue') {
      const actions = el('div', undefined, 'buttons');
      if (step.dialogue) {
        item.append(el('p', readableDialogue(step.dialogue.text) ?? t('此页缺少该对白。'), 'dialogue-preview'));
        const records = pageRecords(story.page);
        if (step.textSelector <= records.length) {
          actions.append(button(step.dialogue.text === null ? t('补全对白') : t('编辑对白'),
            () => editDialogue(story.page, step.textSelector), 'accent'));
        }
        if (records.length <= 239 && scene.dialoguePage !== PROFILE.dialogue.nested && step.insertionIndex === undefined) {
          actions.append(button(t('改用新对白'), () => writeStoryLine(story, program.commands, step, 'replace')),
            button(t('在前面插入对白'), () => writeStoryLine(story, program.commands, step, 'insert')));
        }
      } else {
        item.append(el('p', t('引用原版备用对白'), 'note'));
      }
      if (!step.dialogue) actions.append(button(t('参数'), () => editInstruction(key, program.commands, step.index)));
      item.append(actions);
    } else if (step.kind === 'native') {
      item.append(button(t('在脚本中查看'), () => { state.tab = 'script'; render(); }));
    } else {
      const spec = [...state.rom.specs.values()].find(value => value.operation === step.operation);
      item.append(el('p', t(spec.label), 'step-label'));
      if (step.kind === 'branch') {
        const target = story.steps.find(other => other.offset === step.target);
        const label = target ? tr`查看跳转目标 · 步骤 ${target.index + 1}` : t('目标待核对');
        if (target) item.append(button(label, () => {
          const element = document.getElementById(target.insertionIndex === undefined ? `step-${target.offset}` : `insertion-${target.insertionIndex}`);
          const group = element.closest('details.interlude');
          if (group) group.open = true;
          element.scrollIntoView({ block: 'center' });
        }));
        else item.append(el('small', label));
      }
      if (spec.operands.length) item.append(button(t('参数'), () => editInstruction(key, program.commands, step.index)));
    }
    if (step.kind === 'dialogue' || !hasDialogue) {
      flow.append(item);
      interlude = null;
      continue;
    }
    if (!interlude) {
      const block = el('li', undefined, 'step interlude-block');
      const details = el('details', undefined, 'interlude');
      const summary = el('summary');
      const items = el('ol', undefined, 'story-substeps');
      details.append(summary, items);
      block.append(details);
      flow.append(block);
      interlude = { summary, items, hasBranch: false };
    }
    if (step.kind === 'branch') interlude.hasBranch = true;
    interlude.summary.textContent = interlude.hasBranch ? t('动作与分支') : t('动作');
    interlude.items.append(item);
  }
  body.append(flow);
}

function writeStoryLine(story, commands, step, mode) {
  const text = textarea(t('新对白'), '', 4);
  const line = pageRecords(story.page).length;
  const key = programKey(story.script.group, story.script.program);
  const sharedPage = state.scenes.some(scene => scene.id !== story.scene && scene.dialoguePage === Number(story.page));
  const sharedProgram = state.scenes.some(scene => scene.id !== story.scene && programKey(scene.script.group, scene.script.program) === key);
  const destination = sharedPage ? nextPage() : Number(story.page);
  const speaker = el('select');
  const sameSpeaker = el('option', t('当前说话者'));
  sameSpeaker.value = '';
  speaker.append(sameSpeaker);
  const seen = new Set([step.speakerHandle]);
  let dialogueNumber = 0;
  for (const event of describeStory(state.rom, state.plan, story.scene).steps) {
    if (event.kind !== 'dialogue') continue;
    dialogueNumber++;
    if (seen.has(event.speakerHandle)) continue;
    seen.add(event.speakerHandle);
    const option = el('option', tr`对白 ${dialogueNumber} 的说话者`);
    option.value = String(event.speakerHandle);
    option.dataset.presentationFlags = String(event.presentationFlags);
    speaker.append(option);
  }
  dialog(t(mode === 'insert' ? '在前面插入对白' : '改用新对白'),
    mode === 'insert' ? [text.label, field(t('说话者'), speaker)] : [text.label],
    () => {
      const project = structuredClone(state.project);
      const entry = pageRecords(story.page)[step.textSelector];
      if (sharedPage) copyPage(project, story.page, destination);
      project.dialogue[lineKey(destination, line)] = { text: text.input.value, flags: entry?.flags ?? 16 };
      const existingEdit = project.programs[key];
      const instructions = mode === 'insert' ? existingEdit?.instructions : commandData(commands);
      const selected = speaker.selectedOptions[0];
      const cast = selected.value ? {
        speakerHandle: Number(selected.value),
        presentationFlags: Number(selected.dataset.presentationFlags),
      } : {};
      const inserted = mode === 'insert' ? { anchorOffset: step.offset, textSelector: line, ...cast } : null;
      if (!inserted) instructions[step.index].operands.textSelector = line;
      const script = { ...story.script };
      if (sharedProgram) {
        script.program = state.rom.directories[script.group].slotCount;
        while (project.programs[programKey(script.group, script.program)]) script.program++;
      }
      const cloneFrom = existingEdit?.cloneFrom ?? (sharedProgram && state.rom.programs.has(key) ? key : undefined);
      const insertions = [...(existingEdit?.insertDialogue ?? []), ...(inserted ? [inserted] : [])];
      project.programs[programKey(script.group, script.program)] = {
        ...(cloneFrom ? { cloneFrom } : {}), ...(instructions ? { instructions } : {}),
        ...(insertions.length ? { insertDialogue: insertions } : {}),
      };
      if (sharedProgram || sharedPage) project.scenes[story.scene] = { script, dialoguePage: destination };
      commit(project);
    });
}

function renderIndex(body, scene) {
  const actions = [button(t('编辑索引'), () => editIndex(scene), 'accent'), button(t('复制为新场景'), () => createScene(scene))];
  if (state.project.scenes[scene.id]) actions.push(button(t('还原索引'), handle(() => restore('scenes', scene.id))));
  body.append(section(t('场景关联'), ...actions));
  const program = programFor(scene);
  const grid = el('div', undefined, 'info-grid');
  for (const [label, value] of [
    [t('场景 ID'), String(scene.id)], [t('脚本组 / 程序'), programKey(scene.script.group, scene.script.program)],
    [t('对白页'), String(scene.dialoguePage)], [t('指令数'), String(program?.commands.length ?? 0)],
  ]) {
    const box = el('div');
    box.append(el('small', label), el('strong', value, 'code'));
    grid.append(box);
  }
  body.append(grid);
  if (!program?.commands.length) body.append(el('p', t('这个索引指向空程序或未解出的程序。可以重新关联到已有脚本后保存。'), 'note'));
  if (scene.id >= PROFILE.index.count) body.append(el('p', t('新索引已经分配。要在游戏中播放它，还需要让现有剧情触发入口引用这个 ID。'), 'note'));
}

function renderDialogue(body, scene) {
  const address = state.page ?? activePage(scene);
  const selector = el('select');
  selector.setAttribute('aria-label', t('对白页'));
  for (const key of [...state.rom.pages.keys(), ...state.plan.pages.keys()].sort(keySort)) {
    const option = el('option', tr`对白页 ${key.replace('/', t(' · 变体 '))}`);
    option.value = key;
    selector.append(option);
  }
  selector.value = address;
  selector.addEventListener('change', () => { state.page = selector.value; render(); });
  const records = pageRecords(address);
  body.append(section(t('对白内容'), selector,
    button(t('导入对白 JSON'), () => dialogueImport(address)),
    button(t('＋ 新增对白'), () => editDialogue(address, records.length), 'accent')));
  const sharing = state.scenes.filter(row => row.dialoguePage === Number(address.split('/')[0])).length;
  if (sharing > 1) body.append(el('p', tr`这个对白页被 ${sharing} 个场景索引引用。若只改当前场景，可先复制它的对白页再重新关联。`, 'note'));
  const copy = button(t('复制对白页并关联到当前场景'), () => clonePage(scene, address));
  body.append(copy, el('p', t('展开一行的结构化编辑可以查看和保留控制码、字形编号与编码。'), 'note'));
  body.append(table([t('行号'), t('对白'), t('编码'), ''], records.map((record, line) => [
    el('span', String(line).padStart(3, '0'), 'code'),
    record.preview || t('（空）'),
    record.edited ? t('已修改') : record.encoding === 'alternate' ? t('半宽') : t('标准'),
    button(tr`编辑 ${line}`, () => editDialogue(address, line)),
  ])));
}

function renderScript(body, scene) {
  const program = programFor(scene);
  const address = programKey(scene.script.group, scene.script.program);
  body.append(section(t('场景指令'), button(t('编辑结构化脚本'), () => editScript(scene), 'accent')));
  if (!program?.commands.length) {
    body.append(el('p', t('当前索引没有可执行的脚本。可以在索引页重新关联，或在此补全有效的程序。'), 'note'));
    return;
  }
  body.append(table([t('位置'), t('操作'), t('操作数'), ''], program.commands.map((command, i) => {
    const spec = command.operation === 'native' ? state.rom.specs.get(command.opcode) :
      [...state.rom.specs.values()].find(item => item.operation === command.operation);
    return [el('span', hex(command.offset, 4), 'code'), `${t(spec.label)} · ${hex(spec.opcode)}`,
      el('span', command.operation === 'native' ? command.operands.map(value => hex(value)).join(' ') :
        Object.entries(command.operands).map(([key, value]) => `${key}=${value}`).join(' · '), 'code'),
      command.operation === 'native' ? '' : button(tr`编辑 ${i + 1}`, () => editInstruction(address, program.commands, i))];
  })));
}

function renderDiff(body) {
  body.append(section(t('待导出的改动'), button(t('导出差异 JSON'), handle(exportDiff))));
  if (!state.plan.diffs.length) {
    body.append(el('p', t('当前项目没有实际改动。'), 'note'));
    return;
  }
  const kinds = { opening: '过场编排', battle: '战斗事件', scene: '索引', program: '脚本', page: '对白页', dialogue: '对白' };
  for (const change of state.plan.diffs) {
    const item = el('details', undefined, 'change');
    item.append(el('summary', `${t(change.action === 'add' ? '新增' : '修改')} · ${t(kinds[change.kind])} ${change.target}`));
    const panes = el('div', undefined, 'panes');
    for (const [title, value] of [[t('修改前'), change.before], [t('修改后'), change.after]]) {
      const pane = el('div', undefined, 'pane');
      pane.append(el('strong', title));
      if (change.kind === 'dialogue' && value) {
        pane.append(el('p', value.text || t('（空对白）'), 'dialogue-preview'));
        const source = el('details');
        source.append(el('summary', t('结构化数据')), el('pre', serialize(value)));
        pane.append(source);
      } else {
        pane.append(el('pre', value === null ? t('无') : serialize(value)));
      }
      panes.append(pane);
    }
    item.append(panes);
    body.append(item);
  }
  if (state.plan.battles.size) {
    body.append(el('p', t('战斗事件还需运行时接入，完整 ROM 暂不可导出。'), 'note'));
    return;
  }
  body.append(button(t('查看 ROM 写入位置'), handle(() => {
    const report = build(state.rom, state.project);
    dialog(t('ROM 写入位置'), [table([t('资源'), t('位置'), t('写入')], [
      ...report.pointers.map(item => [item.kind, hex(item.offset, 8), `${hex(item.before, 8)} → ${hex(item.after, 8)}`]),
      ...report.allocations.map(item => [item.target, hex(item.offset, 8), tr`${item.length} 字节`]),
    ])]);
  })));
}

function editIndex(scene) {
  const group = number(t('脚本组（从 0 起）'), scene.script.group, 0, 61);
  const program = number(t('程序编号（从 0 起）'), scene.script.program, 0, 255);
  const page = number(t('对白页编号'), scene.dialoguePage, 0, 255);
  dialog(tr`编辑场景 ${scene.id} 的索引`, [group.label, program.label, page.label], () => {
    editCollection('scenes', scene.id, { script: { group: group.input.valueAsNumber, program: program.input.valueAsNumber },
      dialoguePage: page.input.valueAsNumber });
    state.page = null;
    render();
  });
}

function createScene(scene = currentScene()) {
  const free = Array.from({ length: 6 }, (_, i) => PROFILE.index.count + i).find(id => !state.plan.scenes.has(id));
  if (free === undefined) { notice(t('新增场景 ID 234–239 已用完。'), true); return; }
  const id = number(t('新增场景 ID'), free, PROFILE.index.count, PROFILE.index.expandableThrough);
  const group = number(t('引用脚本组'), scene.script.group, 0, 61);
  const program = number(t('引用程序编号'), scene.script.program, 0, 255);
  const page = number(t('引用对白页'), scene.dialoguePage, 0, 255);
  const clone = el('input');
  clone.type = 'checkbox';
  clone.checked = scene.dialoguePage !== PROFILE.dialogue.nested;
  dialog(t('新增场景索引'), [id.label, group.label, program.label, page.label,
    field(t('复制脚本与对白页，供新场景独立编辑'), clone),
    el('p', t('使用已有的游戏触发入口时，仍需让该入口引用新场景 ID。'), 'note')], () => {
    const project = structuredClone(state.project);
    const target = id.input.valueAsNumber;
    check(!project.scenes[target], t('该场景 ID 已分配'));
    const script = { group: group.input.valueAsNumber, program: program.input.valueAsNumber };
    let dialoguePage = page.input.valueAsNumber;
    if (clone.checked) {
      const source = programKey(script.group, script.program);
      const directory = state.rom.directories[script.group];
      let slot = directory.slotCount;
      while (project.programs[programKey(script.group, slot)]) slot++;
      const effective = state.plan.programs.get(source);
      const existingEdit = project.programs[source];
      check(existingEdit || state.rom.programs.get(source)?.commands.length, t('请选择有效脚本作为复制来源'));
      project.programs[programKey(script.group, slot)] = existingEdit ?
        { ...existingEdit, cloneFrom: existingEdit.cloneFrom ?? (state.rom.programs.has(source) ? source : undefined) } : { cloneFrom: source };
      if (effective && !existingEdit) throw new Error(t('找不到脚本的原始结构化记录'));
      script.program = slot;
      check(dialoguePage !== PROFILE.dialogue.nested, t('请在对白页选择具体变体并复制'));
      const destination = nextPage();
      copyPage(project, String(dialoguePage), destination);
      dialoguePage = destination;
    }
    project.scenes[target] = { script, dialoguePage };
    commit(project);
    state.selected = target;
    state.tab = 'story';
    state.page = null;
    render();
  }, t('新增'));
}

function nextPage() {
  return PROFILE.dialogue.pages + Object.keys(state.project.pages).length;
}

function copyPage(project, address, destination) {
  const current = project.pages[address];
  project.pages[destination] = current ? { ...current } : { cloneFrom: address };
  for (const [key, data] of Object.entries(state.project.dialogue)) {
    const [page, line] = key.split(':');
    if (page === address) project.dialogue[lineKey(destination, line)] = structuredClone(data);
  }
}

function clonePage(scene, address) {
  const page = nextPage();
  dialog(t('复制对白页'), [el('p', tr`将对白页 ${address} 复制为 ${page}，并把场景 ${scene.id} 关联到新页。`, 'note')], () => {
    const project = structuredClone(state.project);
    copyPage(project, address, page);
    project.scenes[scene.id] = { script: scene.script, dialoguePage: page };
    commit(project);
    state.page = String(page);
    render();
  });
}

function editDialogue(address, index) {
  const record = pageRecords(address)[index];
  const key = lineKey(address, index);
  const mode = el('select');
  for (const [value, label] of [['text', t('纯文本')], ['tokens', t('结构化 token')]]) {
    const option = el('option', label);
    option.value = value;
    mode.append(option);
  }
  mode.value = record ? 'tokens' : 'text';
  const content = textarea(t('纯文本'), record?.preview ?? '', 4);
  const tokens = textarea(t('结构化 token JSON'), serialize(record?.tokens ?? []));
  const encoding = el('select');
  for (const [value, label] of [['alternate', t('半宽')], ['standard', t('标准')]]) {
    const option = el('option', label);
    option.value = value;
    encoding.append(option);
  }
  encoding.value = record?.encoding ?? 'standard';
  const choice = field(t('编码'), encoding);
  const flags = number(t('样式标志'), record?.flags ?? 16, 0, 65535);
  const controls = record ? el('p', record.tokens.filter(token => token.kind === 'control').map(token => ({ 0x52: t('空格'), 0x4d: t('换行'), 0x32: t('双字符串') })[token.code] ?? tr`控制码 ${hex(token.code)}`).join(' · '), 'note') : el('span');
  const refresh = () => {
    content.label.hidden = mode.value !== 'text';
    tokens.label.hidden = mode.value !== 'tokens';
  };
  mode.addEventListener('change', refresh);
  refresh();
  const reset = state.project.dialogue[key] ? [button(t('还原这一行'), handle(() => {
    restore('dialogue', key);
    $('#editor').close();
  }))] : [];
  dialog(tr`对白 ${key}`, [field(t('编辑方式'), mode), controls, content.label, tokens.label, choice, flags.label, ...reset], () => {
    const data = mode.value === 'tokens' ? { tokens: JSON.parse(tokens.input.value) } : { text: content.input.value };
    editCollection('dialogue', key, { ...data, encoding: encoding.value, flags: flags.input.valueAsNumber });
  });
}

function dialogueImport(address) {
  const input = textarea(t('对白 JSON'), '[\n  { "text": "A new line." }\n]');
  const start = number(t('起始行号'), pageRecords(address).length, 0, 4094);
  dialog(tr`批量导入到对白页 ${address}`, [start.label, input.label,
    el('p', t('每项可填 text 或 tokens，并可指定 encoding 和 flags。默认追加。'), 'note')], () => {
    const rows = JSON.parse(input.input.value);
    check(Array.isArray(rows) && rows.length, t('请输入至少一条对白'));
    const project = structuredClone(state.project);
    rows.forEach((entry, i) => { project.dialogue[lineKey(address, start.input.valueAsNumber + i)] = entry; });
    commit(project);
  }, t('校验并导入'));
}

function commandData(commands) {
  return commands.map(({ offset, ...command }) => structuredClone(command));
}

function editScript(scene) {
  const key = programKey(scene.script.group, scene.script.program);
  const commands = commandData(programFor(scene)?.commands ?? [{ operation: 'finishSceneTask', operands: {} }]);
  const input = textarea(t('指令列表 JSON'), serialize(commands), 15);
  const label = textarea(t('复制源（可选，组/程序）'), state.project.programs[key]?.cloneFrom ?? '', 1);
  dialog(tr`编辑程序 ${key}`, [label.label, input.label,
    el('p', t('待考证的原生指令保留原始操作数。具备这些指令的程序保留原有布局。'), 'note')], () => {
    const cloneFrom = label.input.value.trim();
    const prior = state.project.programs[key] ?? {};
    editCollection('programs', key, { ...(prior.insertDialogue ? { insertDialogue: prior.insertDialogue } : {}),
      ...(cloneFrom ? { cloneFrom } : {}), instructions: JSON.parse(input.input.value) });
  });
}

function editInstruction(key, commands, index) {
  const draft = commandData(commands);
  const command = draft[index];
  const spec = [...state.rom.specs.values()].find(item => item.operation === command.operation);
  const inputs = spec.operands.map(arg => number(arg.key, command.operands[arg.key],
    arg.signed ? -32768 : 0, arg.key === 'bit' ? 15 : arg.size === 1 ? 255 : arg.signed ? 32767 : 65535));
  dialog(t(spec.label), inputs.length ? inputs.map(input => input.label) : [el('p', t('该指令没有操作数。'), 'note')], () => {
    command.operands = Object.fromEntries(spec.operands.map((arg, i) => [arg.key, inputs[i].input.valueAsNumber]));
    editCollection('programs', key, { ...state.project.programs[key], instructions: draft });
  });
}

function exportDiff() {
  const report = previewBuild(state.rom, state.project);
  downloadJson('ffta.diff.json', { format: 'ffta.scene-diff/v1', baseSha256: state.rom.sha256, ...report });
}

function importDialog(incoming) {
  const project = importProject(state.rom, state.project, incoming);
  const changes = plan(state.rom, project).diffs;
  dialog(t('预览项目导入'), [
    el('p', tr`合并后共有 ${changes.length} 项有效改动。同一资源以导入内容为准。`, 'note'),
    table([t('操作'), t('目标')], changes.map(change => [change.kind, change.target])),
  ], () => commit(project), t('确认合并'));
}

$('#open-rom').onclick = $('#welcome-open').onclick = () => $('#rom-file').click();
$('#import-project').onclick = () => $('#project-file').click();
$('#rom-file').onchange = handle(async event => {
  const file = event.target.files[0];
  event.target.value = '';
  if (!file) return;
  if (state.rom && state.saved !== serialize(state.project) && !confirm(t('导入新 ROM 会丢弃当前未保存的编辑。继续吗？'))) return;
  await load(new Uint8Array(await file.arrayBuffer()), file.name);
});
$('#project-file').onchange = handle(async event => {
  const file = event.target.files[0];
  event.target.value = '';
  if (file) importDialog(JSON.parse(await file.text()));
});
$('#search').oninput = event => { state.query = event.target.value; renderList(); };
$('#filter').onchange = event => { state.filter = event.target.value; renderList(); };
$('#new-scene').onclick = () => createScene();
$('#close-dialog').onclick = $('#cancel-dialog').onclick = () => $('#editor').close();
$('#save-project').onclick = () => {
  downloadJson('ffta.scene.project.json', state.project);
  state.saved = serialize(state.project);
  render();
  notice(t('已生成项目 JSON'));
};
$('#export-rom').onclick = handle(() => {
  check(!state.plan.battles.size, t('战斗事件还需运行时接入，完整 ROM 暂不可导出。'));
  const { bytes, changes } = build(state.rom, state.project);
  download('FFTA_US_Scene_Edit.gba', bytes, 'application/octet-stream');
  notice(tr`ROM 已导出 · ${changes.length} 项改动`);
});
$('#undo').onclick = () => {
  state.redo.push(state.project);
  update(state.undo.pop());
};
$('#redo').onclick = () => {
  state.undo.push(state.project);
  update(state.redo.pop());
};
const panels = createPanelRegistry([
  { id: 'story', label: '剧情', showMetadata: false, render: renderStory },
  { ...createCutscenePanel({ getProject: () => state.project, editCollection }), retailOnly: true },
  { id: 'index', label: '索引', render: renderIndex },
  { id: 'dialogue', label: '对白', render: renderDialogue },
  { ...createBattleEventPanel({
    getPlan: () => state.plan, getRom: () => state.rom, editCollection, restore,
  }), retailOnly: true },
  { id: 'script', label: '脚本', render: renderScript },
  { id: 'diff', label: '改动', render: renderDiff },
]);
const tabs = panels.list.map(panel => {
  const element = button('', () => {
    state.tab = panel.id;
    if (panel.preferredScene !== undefined) {
      state.selected = panel.preferredScene;
      state.page = null;
    }
    render();
  });
  element.dataset.tab = panel.id;
  $('#workspace-tabs').append(element);
  return { panel, element };
});
$('#agent').onclick = () => dialog(t('Agent 数据交换'), [
  el('p', t('场景目录供检索和定位。项目 JSON 记录改动，差异报告包含 ROM 写入范围。'), 'note'),
  button(t('导出场景目录'), () => downloadJson('ffta.scene.catalog.json', catalog(state.rom))),
  button(t('导出目录、脚本和对白'), () => downloadJson('ffta.full.catalog.json', catalog(state.rom, { includePrograms: true, includeDialogue: true }))),
  button(t('导出差异 JSON'), handle(exportDiff)),
]);
window.addEventListener('beforeunload', event => {
  if (state.rom && state.saved !== serialize(state.project)) event.preventDefault();
});
function applyLanguage(value) {
  localize(value);
  $('#language').value = document.documentElement.lang;
  try { localStorage.setItem('ffta.scene.locale', document.documentElement.lang); }
  catch { /* Language remains available for this tab when storage is disabled. */ }
  $('#notice').hidden = true;
  render();
}
let storedLanguage;
try { storedLanguage = localStorage.getItem('ffta.scene.locale'); }
catch { /* Use the default language. */ }
$('#language').onchange = event => applyLanguage(event.target.value);
applyLanguage(storedLanguage ?? 'zh-CN');

// No background access or transport. The caller explicitly supplies local file bytes.
window.fftaSceneEditor = Object.freeze({
  async open(bytes, name = 'FFTA_US.gba') { await load(new Uint8Array(bytes), name); },
  async inspectRom(bytes) { return inspectRom(new Uint8Array(bytes)); },
  getCatalog(options) { check(state.rom, 'Open a ROM first'); return structuredClone(catalog(state.rom, options)); },
  getStory(id, variant = 0) {
    check(state.rom, 'Open a ROM first');
    return structuredClone(describeStory(state.rom, state.plan, id, variant));
  },
  getProject() { check(state.rom, 'Open a ROM first'); return structuredClone(state.project); },
  preview(incoming, mode = 'merge') {
    check(state.rom, 'Open a ROM first');
    const candidate = importProject(state.rom, state.project, incoming, mode);
    return previewBuild(state.rom, candidate);
  },
  apply(incoming, mode = 'merge') {
    check(state.rom, 'Open a ROM first');
    commit(importProject(state.rom, state.project, incoming, mode));
  },
  exportRom() { check(state.rom, 'Open a ROM first'); return build(state.rom, state.project).bytes; },
  exportBattleListenerProbe() {
    check(state.rom, 'Open a ROM first');
    return buildBattleListenerProbe(state.rom);
  },
});
