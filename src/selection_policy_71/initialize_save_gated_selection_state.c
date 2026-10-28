/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct State {u32 values[24];u8 mode;u8 unknown;u8 count;u8 gap[3];u16 saved_display_control;u16 saved_display_mode;u16 padding;u16 state;u16 depth;u16 stack[34];};
struct PolicyState {u8 unknown;u8 flags;u8 active;u8 pending;u16 width;u16 height;u8 rest[64];u16 initialized;u8 tail[70];};
struct DisplayShadow {u16 control;u8 gap[72];volatile u8 mode;};
extern struct PolicyState gPolicyState;
extern struct DisplayShadow gDisplay;
extern u8 gPaletteShadow[];
extern void (*gClearRoutine)(void *,u32);
extern void (*gCopyRoutine)(void *,const void *,u32);
extern const void *ReadPalette(u8);
extern u8 ReadSaveByte(u16);

asm(".global gPolicyState\n.set gPolicyState,0x02015744\n.global gDisplay\n.set gDisplay,0x03000940\n.global gPaletteShadow\n.set gPaletteShadow,0x03003a60\n.global gClearRoutine\n.set gClearRoutine,0x0836d4b8\n.global gCopyRoutine\n.set gCopyRoutine,0x0836d4bc\n.global ReadPalette\n.thumb_set ReadPalette,0x80cba3d\n.global ReadSaveByte\n.thumb_set ReadSaveByte,0x80c95a9\n.global _call_via_r2\n.thumb_set _call_via_r2,0x814224d\n.global _call_via_r3\n.thumb_set _call_via_r3,0x8142251\n");
static inline void PushCurrentState(struct State *state)
{
    state->stack[state->depth++] = state->state;
}
static inline void RequestPolicyMode(u16 value)
{
    u8 mode;
    struct PolicyState *policy;
    if (!ReadSaveByte(13)) return;
    mode = value;
    policy = &gPolicyState;
    if (policy->active) {
        if (policy->active != mode) {
            policy->flags |= 4;
            policy->pending = mode;
        }
    } else {
        gClearRoutine(policy,144);
        policy->active = mode;
        policy->width = 216;
        policy->height = 152;
        if (mode) policy->initialized = 1;
    }
}
void InitializeSaveGatedSelectionState(struct State *state,const u32 *values,int count,u8 option)
{
    u32 *destination;
    const u32 *source;
    int remaining;
    u8 display_mode;
    gClearRoutine(state,180);
    state->count = count;
    if (count > 0) {
        source = values;
        destination = state->values;
        remaining = count;
        do { *destination++ = *source++; } while (--remaining);
    }
    state->state = 15;
    if (option) {
        state->mode = 0;
        PushCurrentState(state);
        state->state = 11;
        PushCurrentState(state);
        state->state = 9;
        PushCurrentState(state);
        state->state = 8;
        PushCurrentState(state);
        state->state = 5;
    } else {
        state->mode = 1;
        PushCurrentState(state);
        state->state = 11;
        PushCurrentState(state);
        state->state = 9;
        PushCurrentState(state);
        state->state = 12;
    }
    PushCurrentState(state);
    state->state = 7;
    PushCurrentState(state);
    state->state = 14;
    gCopyRoutine(gPaletteShadow,ReadPalette(0),32);
    RequestPolicyMode(1);
    state->saved_display_control = gDisplay.control;
    state->saved_display_mode = gDisplay.mode;
    gDisplay.control |= 0x1000;
    display_mode = gDisplay.mode & 0xef;
    gDisplay.mode = display_mode;
}
