/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct ActionState { u8 prefix[12]; u16 first_id; u16 second_id; u8 gap[16]; u16 preserved_first; u16 preserved_second; u16 gap2; u16 flags; u8 counter; u8 gap3[3]; const u8 *data; const u32 *handler; };
extern const u32 gClearMemory;
extern const u32 gActionHandlers[];
extern void CallR2Trampoline(void *destination, u32 size, u32 routine);
extern const u8 *ReadActionData(u16 id, u32 selector);

asm(".global gActionHandlers\n.set gActionHandlers,0x08553e70\n.global ReadActionData\n.thumb_set ReadActionData,0x080ccd51");
void InitializePreservedActionState(struct ActionState *state, u16 first_id, u16 second_id, u8 mode)
{
    u16 saved[2];
    u32 offset;
    saved[0] = state->preserved_first;
    saved[1] = state->preserved_second;
    CallR2Trampoline(state, 52, gClearMemory);
    state->preserved_first = saved[0];
    state->preserved_second = saved[1];
    state->flags = mode ? 0 : 128;
    state->data = ReadActionData(first_id, 9);
    state->first_id = first_id;
    state->second_id = second_id;
    state->counter = 0;
    offset = state->data[0] * sizeof(u32);
    state->handler = (const u32 *)((const u8 *)gActionHandlers + offset);
}
