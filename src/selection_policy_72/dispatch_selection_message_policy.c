/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
union ControllerState {
 struct {u16 current;u16 depth;u16 stack[1];} navigation;
 struct {u8 unknown00[78];u16 message;u8 mode;u8 pending;u8 unknown52[2];u32 flags;s32 selection;u32 unknown5c[2];u16 signature;u16 value;u8 unknown68[233-104];u8 option;} dispatch;
};
extern union ControllerState *controller;
extern u8 context_flags;
extern void PrepareSaveSnapshot(void);
extern void ClearSelectionSlot(u8 slot);
typedef char ControllerLayout[sizeof(union ControllerState)==236?1:-1];
asm(".global controller\n.set controller,0x0200f450");
asm(".global context_flags\n.set context_flags,0x030028a0");
asm(".global PrepareSaveSnapshot\n.thumb_set PrepareSaveSnapshot,0x08064e7d");
asm(".global ClearSelectionSlot\n.thumb_set ClearSelectionSlot,0x08066121");

void DispatchSelectionMessagePolicy(void)
{
    union ControllerState *selected_state;
    controller->dispatch.flags &= ~64;
    PrepareSaveSnapshot();
    if (context_flags & 8) {
        selected_state = controller;
        switch (selected_state->dispatch.selection) {
        case 1: {
            union ControllerState *state;
            selected_state->dispatch.message = (selected_state->dispatch.option & 1) ? 168 : 169;
            selected_state->dispatch.mode = 7;
            state = controller;
        state->navigation.current = 8;
        state->navigation.stack[state->navigation.depth++] = 8;
        state->navigation.current = 56;
        state->navigation.stack[state->navigation.depth++] = 56;
        state->navigation.current = 52;
        state->navigation.stack[state->navigation.depth++] = 52;
        state->navigation.current = 53;
            break;
        }
        case 2:
{
            union ControllerState *state;
            selected_state->dispatch.message = (selected_state->dispatch.option & 1) ? 182 : 183;
            selected_state->dispatch.flags &= ~4;
            ClearSelectionSlot(4);
            state = controller;
        state->navigation.current = 19;
        state->navigation.stack[state->navigation.depth++] = 19;
        state->navigation.current = 52;
        state->navigation.stack[state->navigation.depth++] = 52;
        state->navigation.current = 53;
            break;
        }
        case 3:
            selected_state->dispatch.message = (selected_state->dispatch.option & 1) ? 190 : 191;
            selected_state->dispatch.flags &= ~4;
        selected_state->navigation.current = 31;
        selected_state->navigation.stack[selected_state->navigation.depth++] = 31;
        selected_state->navigation.current = 52;
        selected_state->navigation.stack[selected_state->navigation.depth++] = 52;
        selected_state->navigation.current = 53;
            break;
        }
    } else {
        selected_state = controller;
        switch (selected_state->dispatch.selection) {
        case 1: {
            union ControllerState *state;
            selected_state->dispatch.message = (selected_state->dispatch.option & 1) ? 170 : 171;
            selected_state->dispatch.signature = 0x9001;
            selected_state->dispatch.value = 0x1234;
            selected_state->dispatch.mode = 8;
            state = controller;
        state->navigation.current = 14;
        state->navigation.stack[state->navigation.depth++] = 14;
        state->navigation.current = 42;
        state->navigation.stack[state->navigation.depth++] = 42;
        state->navigation.current = 40;
        state->navigation.stack[state->navigation.depth++] = 40;
        state->navigation.current = 57;
        state->navigation.stack[state->navigation.depth++] = 57;
        state->navigation.current = 56;
        state->navigation.stack[state->navigation.depth++] = 56;
        state->navigation.current = 52;
        state->navigation.stack[state->navigation.depth++] = 52;
        state->navigation.current = 53;
            break;
        }
        case 2:
{
            union ControllerState *state;
            selected_state->dispatch.message = (selected_state->dispatch.option & 1) ? 182 : 183;
            selected_state->dispatch.flags &= ~4;
            ClearSelectionSlot(4);
            state = controller;
        state->navigation.current = 19;
        state->navigation.stack[state->navigation.depth++] = 19;
        state->navigation.current = 52;
        state->navigation.stack[state->navigation.depth++] = 52;
        state->navigation.current = 53;
            break;
        }
        case 3:
            selected_state->dispatch.message = (selected_state->dispatch.option & 1) ? 190 : 191;
            selected_state->dispatch.flags &= ~4;
        selected_state->navigation.current = 31;
        selected_state->navigation.stack[selected_state->navigation.depth++] = 31;
        selected_state->navigation.current = 52;
        selected_state->navigation.stack[selected_state->navigation.depth++] = 52;
        selected_state->navigation.current = 53;
            break;
        }
    }
}
