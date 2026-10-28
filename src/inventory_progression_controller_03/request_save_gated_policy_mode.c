/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct PolicyState { u8 unknown; u8 flags; u8 active; u8 pending; u16 width; u16 height; u8 rest[64]; u16 initialized; };
extern struct PolicyState gPolicyState;
extern const u32 gClearMemory;
extern u8 ReadSaveByte(u16 index);
extern void CallR2Trampoline(void *destination, u32 size, u32 routine);

asm(".global gPolicyState\n.set gPolicyState,0x02015744");
void RequestSaveGatedPolicyMode(u16 value)
{
    u8 mode;
    struct PolicyState *state;
    if (!ReadSaveByte(13))
        return;
    mode = value;
    state = &gPolicyState;
    if (state->active) {
        if (state->active != mode) {
            state->flags |= 4;
            state->pending = mode;
        }
    } else {
        CallR2Trampoline(state, 144, gClearMemory);
        state->active = mode;
        state->width = 216;
        state->height = 152;
        if (mode)
            state->initialized = 1;
    }
}
