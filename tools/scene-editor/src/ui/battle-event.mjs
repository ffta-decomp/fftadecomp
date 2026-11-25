import { battleEventStep, BATTLE_SCENE, DEMO_ID, snowballDemo } from '../battle.mjs';
import { buildBattleListenerProbe } from '../battle-probes.mjs';
import { t, tr } from '../i18n.mjs';
import { button, dialog, download, el, handle, notice, number, section, table, textarea } from './controls.mjs';

export function createBattleEventPanel({ getPlan, getRom, editCollection, restore }) {
  function renderBattle(body) {
    const current = getPlan().battles.get(DEMO_ID);
    const actions = [button(current ? t('编辑事件') : t('新增战斗事件'), () => editBattle(current), 'accent')];
    if (current) actions.push(button(t('移除事件'), handle(() => restore('battleEvents', DEMO_ID))));
    body.append(section(t('战斗规则'), ...actions));
    if (!current) {
      body.append(el('p', t('添加「缪特受伤后，哥布林登场」的事件草稿。'), 'note'));
      return;
    }
    body.append(table([t('步骤'), t('规则')], [
      [t('触发'), t('缪特首次受到攻击伤害')],
      [t('登场'), tr`哥布林 · 生命 ${current.spawn.hp} · 攻击 ${current.spawn.attack}`],
      [t('对白'), current.dialogue.text],
      [t('胜利'), t('击倒这只哥布林')],
    ]), el('p', t('监听探针可导出。完整事件还需接入登场、对白和胜利目标。'), 'note'),
    button(t('预演规则'), () => previewBattle(current)),
    button(t('导出监听探针'), handle(() => {
      const { bytes } = buildBattleListenerProbe(getRom());
      download('FFTA_US_Snowball_Listener_Probe.gba', bytes, 'application/octet-stream');
      notice(t('已导出监听探针'));
    })));
  }

  function editBattle(existing) {
    const rule = structuredClone(existing ?? snowballDemo());
    const hp = number(t('生命值'), rule.spawn.hp, 1, 255);
    const attack = number(t('攻击力'), rule.spawn.attack, 0, 255);
    const line = textarea(t('哥布林对白'), rule.dialogue.text, 3);
    dialog(t('哥布林登场'), [hp.label, attack.label, line.label], () => {
      rule.spawn.hp = hp.input.valueAsNumber;
      rule.spawn.attack = attack.input.valueAsNumber;
      rule.dialogue.text = line.input.value;
      editCollection('battleEvents', DEMO_ID, rule);
    });
  }

  function previewBattle(rule) {
    const sequence = [
      [t('缪特未受伤'), { kind: 'damageResolved', target: 'mewt', damage: 0 }],
      [t('命中其他单位'), { kind: 'damageResolved', target: 'other', damage: 1 }],
      [t('击倒其他单位'), { kind: 'unitDefeated', target: 'other' }],
      [t('缪特受到伤害'), { kind: 'damageResolved', target: 'mewt', damage: 1 }],
      [t('关闭对白'), { kind: 'dialogueClosed' }],
      [t('再次伤到缪特'), { kind: 'damageResolved', target: 'mewt', damage: 1 }],
      [t('击倒哥布林'), { kind: 'unitDefeated', target: 'goblin' }],
    ];
    const labels = { spawnBattleUnit: '哥布林登场', speakAsBattleUnit: '播放对白', resumeBattle: '继续战斗', battleVictory: '战斗胜利' };
    let phase = 'waiting';
    const rows = sequence.map(([label, input]) => {
      const next = battleEventStep(rule, phase, input);
      phase = next.phase;
      return [label, next.outputs.map(output => t(labels[output.kind])).join(' · ') || t('继续原流程')];
    });
    dialog(t('规则预演'), [table([t('输入'), t('事件结果')], rows)]);
  }

  return {
    id: 'battle', label: '战斗事件', preferredScene: BATTLE_SCENE, showMetadata: false,
    title: () => t('雪球战'),
    render: renderBattle,
  };
}
