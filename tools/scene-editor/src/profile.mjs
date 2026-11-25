export const PROFILE = Object.freeze({
  id: 'ffta-us-retail',
  sha256: '43fc8204c6dceee58828aebc7af0c72eb807e99f35ad641c8bb0a4fa8b6edc19',
  compatibleId: 'ffta-us-layout',
  gameCode: 'AFXE',
  size: 0x1000000,
  maximumSize: 0x2000000,
  bus: 0x08000000,
  index: { pointer: 0x9a20, start: 0xa19970, count: 234, expandableThrough: 239 },
  scripts: { pointer: 0x1223c0, start: 0x9a5d54, end: 0x9c1484, groups: 62, descriptors: 0x3a7ee4 },
  dialogue: { pointer: 0x9a88, start: 0x9c1484, end: 0xa19970, pages: 63, nested: 61, variants: 26 },
});

// Executable and descriptor signatures for same-layout data mods.
export const US_LAYOUT_SIGNATURES = [
  [0xc0, 0x36d4bc, '83ac45e86a90be5f4d9157cdfb9065a8b18ce12239eda72ae28cf530664fb7f1'],
  [PROFILE.scripts.descriptors, PROFILE.scripts.descriptors + 0x72 * 6,
    '8a48d25ccfc6f9be94e2b3032628798e8e461aba5c8a4c6bcd46d11455bfd659'],
];

// Names describe observed operations. Operand meanings are exposed only where verified.
const byte = key => ({ key, size: 1 });
const word = key => ({ key, size: 2 });

export const OPERATIONS = {
  0x06: ['fadeSceneBrightness', '场景亮度淡变', [byte('mode'), byte('frames'), byte('level')]],
  0x04: ['waitForActors', '等待角色动作完成', []],
  0x0c: ['loadSceneMap', '加载场景地图', [byte('map')]],
  0x12: ['applySceneMode', '应用场景模式', [byte('mode')]],
  0x1a: ['setStoryFlag', '设置剧情标志', [word('flag'), byte('value')]],
  0x1c: ['queueScene', '安排后续场景', [word('scene')]],
  0x20: ['placeSceneActor', '摆放角色', [byte('actor'), byte('tile'), byte('facing'), byte('visibility')]],
  0x27: ['playActorAction', '播放角色动作', [byte('actor'), word('action'), byte('mode')]],
  0x28: ['refreshActorFacing', '更新角色朝向', [byte('actor')]],
  0x29: ['setActorFacing', '设置角色朝向', [byte('actor'), byte('facing')]],
  0x2f: ['setActorTile', '更新角色格子', [byte('actor'), byte('x'), byte('y')]],
  0x3e: ['moveActorOnGrid', '移动角色', [byte('actor'), byte('x'), byte('y'), byte('facing'), byte('mode'), word('speed')]],
  0x47: ['moveSceneCamera', '移动镜头', [word('x'), word('y'), byte('mode'), byte('duration')]],
  0x48: ['prepareMapView', '准备地图视图', [byte('mode')]],
  0x4b: ['selectScenePresentation', '选择场景演出', [byte('preset')]],
  0x4d: ['fadeSceneAudio', '场景音量淡变', [byte('level'), word('frames'), byte('channels')]],
  0x4e: ['loadEncounterUnits', '载入场景单位', []],
  0x53: ['selectSceneEncounter', '选择剧情场景配置', [word('encounter')]],
  0x02: ['finishSceneTask', '结束场景任务', []],
  0x03: ['selectSceneHandle', '选择场景句柄', [{ key: 'handle', size: 1 }]],
  0x0d: ['setSceneRuntimeState12', '设置场景运行状态 12', []],
  0x0f: ['say', '显示对白', [{ key: 'textSelector', size: 1 }, { key: 'speakerHandle', size: 1 }, { key: 'presentationFlags', size: 1 }]],
  0x15: ['setContextValue', '设置场景上下文值', [{ key: 'value', size: 1 }]],
  0x17: ['setSceneRuntimeMode', '设置场景运行模式', [{ key: 'mode', size: 1 }]],
  0x19: ['adjustScriptOffset', '调整脚本偏移', [{ key: 'delta', size: 2, signed: true }]],
  0x26: ['createActionFromHandles', '根据句柄创建场景动作', [{ key: 'firstHandle', size: 1 }, { key: 'secondHandle', size: 1 }]],
  0x57: ['initializeSceneTaskContext', '初始化场景任务上下文', []],
  0x58: ['clearSceneTaskContext', '清理场景任务上下文', []],
  0x59: ['selectCurrentSceneEntity', '设置当前场景实体', [{ key: 'handle', size: 1 }]],
  0x5b: ['waitForSceneTask', '等待场景任务完成', []],
  0x66: ['addOffsetWhenTargetFlagSet', '目标标志满足时调整偏移', [{ key: 'handle', size: 1 }, { key: 'bit', size: 1 }, { key: 'delta', size: 2, signed: true }]],
};
