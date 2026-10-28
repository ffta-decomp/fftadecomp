typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneOwner { u8 unaccessed_00[6]; u8 complete; };
struct SceneActor { u8 unaccessed_00[8]; u16 x; u16 height; u16 z; };
struct SceneStep { u16 current; u8 opaque_02[22]; };
struct SceneProgressState {
    struct SceneOwner *owner; struct SceneActor *actor;
    s16 delta_x; s16 delta_z; u16 duration; u8 mode; u8 sequence_index;
    u8 unaccessed_16[8]; struct SceneStep x_step; struct SceneStep z_step;
};
typedef char XStepOffset[(u32)&(((struct SceneProgressState *)0)->x_step)==24?1:-1];
typedef char ZStepOffset[(u32)&(((struct SceneProgressState *)0)->z_step)==48?1:-1];
extern void AdvanceSceneStep(struct SceneStep *);
extern u32 IsSceneStepComplete(struct SceneStep *);
extern u32 AdvanceSceneHeightSample(struct SceneProgressState *);
extern u8 ReadMapCellPrimaryByte(u8 column,u8 row);
extern void UpdateBattlePendingHandleFlags(struct SceneActor *,u16 clear_mask,u16 set_mask);
extern s32 QueryActorSequenceIndex(struct SceneActor *);
extern u32 SelectSceneUnitModeByDistance(struct SceneProgressState *);
extern void SetActorSequenceCursor(struct SceneActor *,u32 index);
/* The original materializes the update decision before consuming it. */
static __inline__ u32 UpdateSceneSequenceForDistance(struct SceneProgressState *state)
{
    u32 next_sequence = SelectSceneUnitModeByDistance(state);
    if (next_sequence != state->sequence_index) {
        state->sequence_index = next_sequence;
        return 1;
    }
    return 0;
}
u32 AdvanceSceneActorCoordinateAndSequence(struct SceneProgressState *state)
{
    u32 phase = 0x102;
    u32 sequence_index;
    register u32 changed __asm__("r0");
    u32 first_complete;
    u32 second_complete;
    AdvanceSceneStep(&state->x_step);
    state->actor->x = state->x_step.current;
    AdvanceSceneStep(&state->z_step);
    state->actor->z = state->z_step.current;
    if ((u8)AdvanceSceneHeightSample(state) != 0) {
        state->actor->height = (u8)ReadMapCellPrimaryByte(
            (u8)((s16)state->actor->x >> 5),
            (u8)((s16)state->actor->z >> 5)) << 4;
        UpdateBattlePendingHandleFlags(state->actor,0,0x100);
        sequence_index = QueryActorSequenceIndex(state->actor);
        state->sequence_index = sequence_index;
        if ((u8)sequence_index != 0) state->sequence_index = sequence_index - 1;
        changed = UpdateSceneSequenceForDistance(state);
        /* Native tests the materialized update result after its shared join.
           The initialized empty operand emits no instructions or memory effects. */
        asm("" : "+r"(changed));
        if (changed != 0)
            SetActorSequenceCursor(state->actor,state->sequence_index);
        phase = 0x101;
    }
    first_complete = IsSceneStepComplete(&state->x_step);
    second_complete = IsSceneStepComplete(&state->z_step);
    if (first_complete != 0 && second_complete != 0) {
        state->actor->height = (u8)ReadMapCellPrimaryByte(
            (u8)((s16)state->actor->x >> 5),
            (u8)((s16)state->actor->z >> 5)) << 4;
        UpdateBattlePendingHandleFlags(state->actor,0,0x100);
        state->owner->complete = 1;
        phase = 3;
    }
    return phase;
}
asm(".global AdvanceSceneStep\n.thumb_set AdvanceSceneStep,0x080076f5\n"
    ".global IsSceneStepComplete\n.thumb_set IsSceneStepComplete,0x08007895\n"
    ".global AdvanceSceneHeightSample\n.thumb_set AdvanceSceneHeightSample,0x08127c95\n"
    ".global ReadMapCellPrimaryByte\n.thumb_set ReadMapCellPrimaryByte,0x0801cc19\n"
    ".global UpdateBattlePendingHandleFlags\n.thumb_set UpdateBattlePendingHandleFlags,0x0809a571\n"
    ".global QueryActorSequenceIndex\n.thumb_set QueryActorSequenceIndex,0x0809a53d\n"
    ".global SelectSceneUnitModeByDistance\n.thumb_set SelectSceneUnitModeByDistance,0x08127381\n"
    ".global SetActorSequenceCursor\n.thumb_set SetActorSequenceCursor,0x0809a531\n");
