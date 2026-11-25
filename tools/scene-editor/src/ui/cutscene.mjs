import { check } from '../binary.mjs';
import { t } from '../i18n.mjs';
import { blankOpening, DIRECTIONS, OPENING_CAST, OPENING_ID, openingExample } from '../opening.mjs';
import { $, button, dialog, el, field, handle, notice, number, section, textarea } from './controls.mjs';

const castLabels = {
  marche: '马修', mewt: '缪特', ritz: '莉兹', student: '同学', instructor: '老师',
  redCap: '红帽哥布林', goblin1: '哥布林 1', goblin2: '哥布林 2', goblin3: '哥布林 3',
};
const directionLabels = {
  southwest: '西南', northwest: '西北', northeast: '东北', southeast: '东南',
};
const stepLabels = { say: '对白', walk: '移动', face: '转身' };

function pick(label, value, choices, labels) {
  const input = el('select');
  for (const key of choices) {
    const option = el('option', t(labels[key]));
    option.value = key;
    input.append(option);
  }
  if (value !== undefined) input.value = value;
  return { input, label: field(t(label), input) };
}

export function createCutscenePanel({ getProject, editCollection }) {
  function renderOpening(body) {
    const opening = getProject().openings?.[OPENING_ID];
    if (!opening) {
      body.append(section(t('第一幕过场')),
        button(t('新建空白过场'), () => editCollection('openings', OPENING_ID, blankOpening()), 'accent'),
        button(t('载入哥布林示例'), () => editCollection('openings', OPENING_ID, openingExample())));
      return;
    }
    const castCards = el('div', undefined, 'opening-cast');
    for (const actor of opening.cast) {
      const icon = el('span', '◆');
      icon.className = Object.keys(OPENING_CAST).indexOf(actor.actor) < 5 ? 'cast-ally' : 'cast-enemy';
      const name = el('span', t(castLabels[actor.actor]));
      const entry = button('', () => editOpeningActor(opening, actor));
      entry.append(icon, name, el('small', `${actor.x}, ${actor.y} · ${t(directionLabels[actor.facing])}`));
      castCards.append(entry);
    }
    body.append(section(t('登场角色'), button(t('添加角色'), () => editOpeningActor(opening))),
      castCards, section(t('事件时间线'), button(t('添加步骤'), () => editOpeningStep(opening))));
    const timeline = el('ol', undefined, 'opening-timeline');
    opening.steps.forEach((step, index) => {
      const row = el('li');
      const detail = step.type === 'say' ? step.text : step.type === 'walk'
        ? `(${step.x}, ${step.y}) · ${t(directionLabels[step.facing])}` : t(directionLabels[step.facing]);
      row.append(el('span', String(index + 1), 'opening-order'), el('strong', t(stepLabels[step.type])),
        el('span', t(castLabels[step.actor])), el('span', detail, 'opening-detail'),
        button(t('编辑'), () => editOpeningStep(opening, index)));
      timeline.append(row);
    });
    body.append(timeline, section(t('进入战斗'), button(t('编辑'), () => editOpeningBattle(opening))));
    const intro = el('div', undefined, 'opening-intro');
    intro.append(el('strong', t('红帽哥布林 × 1 · 哥布林 × 3')), el('span', t('击倒全部敌人'), 'opening-detail'));
    body.append(intro);
  }

  function editOpeningActor(opening, previous) {
    const choices = Object.keys(OPENING_CAST).filter(key => key === previous?.actor || !opening.cast.some(item => item.actor === key));
    if (!choices.length) return;
    const actor = pick('角色', previous?.actor, choices, castLabels);
    if (previous) actor.input.disabled = true;
    const x = number(t('列'), previous?.x ?? 4, 0, 11);
    const y = number(t('行'), previous?.y ?? 4, 0, 8);
    const facing = pick('朝向', previous?.facing, DIRECTIONS, directionLabels);
    const extras = [];
    if (previous) extras.push(button(t('移除角色'), handle(() => {
      check(!opening.steps.some(step => step.actor === previous.actor), t('请先移除该角色的时间线步骤。'));
      const cast = opening.cast.filter(member => member !== previous);
      editCollection('openings', OPENING_ID, { ...opening, cast });
      $('#editor').close();
    })));
    dialog(t(previous ? '编辑角色' : '添加角色'), [actor.label, x.label, y.label, facing.label, ...extras], () => {
      const member = { actor: actor.input.value, x: x.input.valueAsNumber, y: y.input.valueAsNumber, facing: facing.input.value };
      const cast = previous ? opening.cast.map(item => item === previous ? member : item) : [...opening.cast, member];
      editCollection('openings', OPENING_ID, { ...opening, cast });
    });
  }

  function editOpeningStep(opening, index) {
    if (!opening.cast.length) { notice(t('请先添加登场角色。'), true); return; }
    const previous = opening.steps[index];
    const type = pick('操作', previous?.type, Object.keys(stepLabels), stepLabels);
    const actor = pick('角色', previous?.actor, opening.cast.map(member => member.actor), castLabels);
    const text = textarea(t('对白'), previous?.text ?? '', 3);
    const x = number(t('列'), previous?.x ?? 4, 0, 11);
    const y = number(t('行'), previous?.y ?? 4, 0, 8);
    const facing = pick('朝向', previous?.facing, DIRECTIONS, directionLabels);
    const position = number(t('时间线顺序'), index === undefined ? opening.steps.length + 1 : index + 1,
      1, opening.steps.length + (previous ? 0 : 1));
    function toggleFields() {
      text.label.hidden = type.input.value !== 'say';
      facing.label.hidden = type.input.value === 'say';
      x.label.hidden = y.label.hidden = type.input.value !== 'walk';
    }
    type.input.onchange = toggleFields;
    toggleFields();
    const extras = [];
    if (previous) extras.push(button(t('删除步骤'), () => {
      editCollection('openings', OPENING_ID, { ...opening, steps: opening.steps.filter((_, i) => i !== index) });
      $('#editor').close();
    }));
    dialog(t(previous ? '编辑步骤' : '添加步骤'), [type.label, actor.label, text.label, x.label, y.label, facing.label, position.label, ...extras], () => {
      const step = { type: type.input.value, actor: actor.input.value };
      if (step.type === 'say') step.text = text.input.value;
      else step.facing = facing.input.value;
      if (step.type === 'walk') Object.assign(step, { x: x.input.valueAsNumber, y: y.input.valueAsNumber });
      const steps = opening.steps.filter((_, i) => i !== index);
      steps.splice(position.input.valueAsNumber - 1, 0, step);
      editCollection('openings', OPENING_ID, { ...opening, steps });
    });
  }

  function editOpeningBattle(opening) {
    const title = el('input');
    Object.assign(title, { value: opening.title, maxLength: 80, required: true });
    const intro = textarea(t('战斗开场对白'), opening.battleIntro, 3);
    const ending = textarea(t('战后对白'), opening.battleEnding ?? blankOpening().battleEnding, 3);
    dialog(t('编辑第一幕'), [field(t('标题'), title), intro.label, ending.label], () => {
      editCollection('openings', OPENING_ID, { ...opening, title: title.value, battleIntro: intro.input.value, battleEnding: ending.input.value });
    });
  }

  return {
    id: 'opening', label: '过场编排', preferredScene: 1, showMetadata: false,
    title: () => getProject().openings?.[OPENING_ID]?.title ?? t('第一幕过场'),
    render: renderOpening,
  };
}
