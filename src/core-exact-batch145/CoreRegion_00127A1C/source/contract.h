#include "../../../../src/task_tree_core.h"
typedef signed short s16;
typedef signed int s32;
struct SceneOwner { u8 unaccessed_00[6]; u8 complete; u8 unaccessed_07; TaskNode *parent; };
struct SceneCoordinateTemplate {
    u16 phase; u16 unassigned_02; struct SceneOwner *owner;
    s32 delta_x; s32 delta_y; u32 unassigned_16;
    u16 unit_selector; u16 mode; u16 duration; u16 unassigned_26;
};
struct MovingSceneActor { u8 unaccessed_00[10]; s16 height; };
struct SceneStep { u16 current; u8 opaque_02[22]; };
struct SceneCoordinateState {
    struct SceneOwner *owner; struct MovingSceneActor *actor;
    s16 delta_x; s16 delta_y; u16 duration; u8 mode;
    u8 unaccessed_15[9]; struct SceneStep x_step; struct SceneStep y_step;
};
typedef char StepSize[sizeof(struct SceneStep)==24?1:-1];
typedef char XStepOffset[(u32)&(((struct SceneCoordinateState *)0)->x_step)==24?1:-1];
typedef char YStepOffset[(u32)&(((struct SceneCoordinateState *)0)->y_step)==48?1:-1];
struct BattleActionRegistry;
extern void *ResolveSceneUnit(u8 selector);
extern struct BattleActionRegistry *GetBattleActionRegistry(void);
extern struct MovingSceneActor *FindPrimaryActor(struct BattleActionRegistry *, void *unit);
extern u32 SquareRootWord(u32 value);
extern s32 DivideSignedWord(s32 dividend,s32 divisor);
extern void InitializeSceneStep(struct SceneStep *,s16 start,u16 zero,s16 end,s16 duration);
extern void AdvanceSceneStep(struct SceneStep *);
extern u32 IsSceneStepComplete(struct SceneStep *);
