#ifndef RECOVERED_SCENE_VM_ABI_H
#define RECOVERED_SCENE_VM_ABI_H
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
#define BYTE(address) (*(volatile u8 *)(address))
#define HALF(address) (*(volatile u16 *)(address))
#define WORD(address) (*(volatile u32 *)(address))
#define STATE_POINTER (*(u8 * volatile *)0x020159cc)
#define POOL_POINTER (*(void * volatile *)0x020159c4)
#define SYSTEM_STATE ((u8 *)0x0200f390)
#define READ16(p) ((u16)((p)[0] | ((u32)(p)[1]<<8)))
#define READ32(p) ((u32)(p)[0] | ((u32)(p)[1]<<8) | ((u32)(p)[2]<<16) | ((u32)(p)[3]<<24))
extern void *Allocate_08007138(void *,u32);
extern void Free_08007170(void *,void *);
extern void (*const gClearMemory)(void *,u32);
extern void *SceneHelper_08005C14(void *,u32);
extern void SceneHelper_08005B18(void *);
extern void SceneHelper_08005C34(void *);
extern void SceneHelper_080058A4(void *,void *);
extern void *SceneHelper_08121D0C(u32);
extern void *SceneHelper_08005BFC(void *);
extern void SceneHelper_08005C04(void *,void *);
extern u32 SceneHelper_080D37F8(void);
extern u32 SceneHelper_080D37C4(void);
extern void *SceneHelper_08121DBC(void);
extern u32 SceneHelper_080D3878(void *);
extern void SceneHelper_080D3864(void *);
extern void SceneHelper_08121DA8(u32);
extern u32 SceneHelper_080C72E4(void);
extern void *SceneHelper_08121E1C(void);
extern u32 SceneHelper_080C74B4(void *);
extern void SceneHelper_080C7548(void *);
extern void SceneHelper_08124CE8(void);
extern void SceneHelper_08004C40(void);
extern void SceneHelper_081253CC(void);
extern void SceneHelper_081258AC(void);
extern void SceneHelper_081256C8(void);
extern u32 SceneHelper_0803600C(void);
extern void SceneHelper_080D241C(u32,void *);
extern void SceneHelper_080C9574(u32,u32);
extern void SceneHelper_08022E90(u32,u32);
extern u8 *SceneHelper_08009A14(u32);
extern void *SceneHelper_08121B8C(void *,u32,void *,void *);
u32 RunSceneCommandLoop_08122ABC(u8 *);
u32 AdvanceSceneTransition_08122160(u8 *);
u32 SceneTaskCallback_08121FB8(void *,u8 *,u8 *);
#endif
