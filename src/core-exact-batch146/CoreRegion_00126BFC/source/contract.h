#include "../../../../src/task_tree_core.h"
typedef signed char s8;
typedef signed int s32;
struct SceneOwner { u8 unaccessed_00[6]; u8 complete; };
struct SceneUnit { u8 unaccessed_00[248]; u8 direction; };
struct SceneActor { struct SceneUnit *unit; u8 unaccessed_04[44]; u32 flags; };
struct DirectionEvent { u16 phase; u16 unaccessed_02; struct SceneOwner *owner; u8 unaccessed_08[12]; u16 unit_selector; u16 target; u16 mode; u16 unaccessed_26; };
struct DirectionState { struct SceneOwner *owner; struct SceneActor *actor; u8 current; u8 target; u8 counter; u8 mode; };
typedef char EventExtent[sizeof(struct DirectionEvent)==28?1:-1];
typedef char StateExtent[sizeof(struct DirectionState)==12?1:-1];
typedef char UnitDirectionOffset[(u32)&(((struct SceneUnit *)0)->direction)==248?1:-1];
typedef char ActorFlagsOffset[(u32)&(((struct SceneActor *)0)->flags)==48?1:-1];
extern struct SceneUnit *ResolveSceneUnit(u8);
extern void *GetBattleActionRegistry(void);
extern struct SceneActor *FindPrimaryActor(void *,struct SceneUnit *);
extern u32 ApplyBattleActorState(struct SceneActor *,u16,s8,u16);
extern void ReapplySceneActorDirection(struct SceneActor *,u8,u8);
