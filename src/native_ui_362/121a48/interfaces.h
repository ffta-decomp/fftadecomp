#ifndef CORE_REGION_00121A48_INTERFACES_H
#define CORE_REGION_00121A48_INTERFACES_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern void SetGameFlag(u32, u32);
extern void WriteSceneControl(u32, u32);
extern void EnterSceneMode(void);
extern void BeginSceneAction(u32);
extern u32 ReadBattleContext(void);
extern u32 ConfigureSceneAction(u32, u32);
extern void ContinueSceneMode(u32);
extern void PrepareEffect(void);
extern void NotifySceneCode(u32);
extern void CompleteSceneTransition(void);
__asm__(".global SetGameFlag\n.thumb_set SetGameFlag,0x080c9575");
__asm__(".global WriteSceneControl\n.thumb_set WriteSceneControl,0x080c95c1");
__asm__(".global EnterSceneMode\n.thumb_set EnterSceneMode,0x08125561");
__asm__(".global BeginSceneAction\n.thumb_set BeginSceneAction,0x0802b5a9");
__asm__(".global ReadBattleContext\n.thumb_set ReadBattleContext,0x08096d7d");
__asm__(".global ConfigureSceneAction\n.thumb_set ConfigureSceneAction,0x0809a261");
__asm__(".global ContinueSceneMode\n.thumb_set ContinueSceneMode,0x081256bd");
__asm__(".global PrepareEffect\n.thumb_set PrepareEffect,0x08022a9d");
__asm__(".global NotifySceneCode\n.thumb_set NotifySceneCode,0x08009afd");
__asm__(".global CompleteSceneTransition\n.thumb_set CompleteSceneTransition,0x08009fd1");
#endif
