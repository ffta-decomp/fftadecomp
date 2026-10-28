/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct SaveImage {u8 unknown00[0x20d0];u32 transaction;u8 unknown20d4[0x219e - 0x20d4];u16 selected_id;};
union ControllerState {
 struct {u16 current;u16 depth;u16 stack[1];} navigation;
 struct {u8 unknown00[78];u16 message;u8 mode;u8 pending;u8 unknown52[2];u32 flags;u32 selected88;u32 selected92;u32 unknown60;u16 signature;u16 value;} dispatch;
 struct {u8 unknown00[0x888];u32 value888;} saved;
};
extern struct SaveImage live_save;
extern union ControllerState *controller;
extern u32 PollDisplayCompletion(void);
extern s8 GetConfirmation(void);
extern void ClearConfirmation(void);
typedef char ControllerLayout[sizeof(union ControllerState)==0x88c?1:-1];
typedef char SaveLayout[sizeof(struct SaveImage)==0x21a0?1:-1];
asm(".global live_save\n.set live_save,0x02000000");
asm(".global controller\n.set controller,0x0200f450");
asm(".global PollDisplayCompletion\n.thumb_set PollDisplayCompletion,0x08011861");
asm(".global GetConfirmation\n.thumb_set GetConfirmation,0x08013381");
asm(".global ClearConfirmation\n.thumb_set ClearConfirmation,0x08013365");
struct SelectedRecord {u16 id:10;u16 unknown10:6;} __attribute__((packed));
typedef char SelectedRecordLayout[sizeof(struct SelectedRecord)==2?1:-1];
extern const struct SelectedRecord *GetStoredSelectedRecord(void);
asm(".global GetStoredSelectedRecord\n.thumb_set GetStoredSelectedRecord,0x08066115");

void AdvanceSelectionOptionPolicy(void)
{
    s32 confirmation;
    if (!(u16)PollDisplayCompletion()) return;
    confirmation = GetConfirmation();
    if (confirmation < 0) {
        union ControllerState *state;
        ClearConfirmation();
        state = controller;
        state->navigation.current = 8;
        state->navigation.stack[state->navigation.depth++] = 8;
        state->navigation.current = 52;
    } else if (confirmation > 0) {
        union ControllerState *initial = controller;
        union ControllerState *message_state;
        union ControllerState *state;
        initial->dispatch.flags |= 2;
        initial->dispatch.selected92 = -1;
        initial->dispatch.message = 173;
        initial->dispatch.mode = 3;
        message_state = controller;
        message_state->dispatch.signature = 0x9001;
        message_state->dispatch.value = 0x1234;
        ClearConfirmation();
        state = controller;
        state->navigation.current = 48;
        state->navigation.stack[state->navigation.depth++] = 48;
        state->navigation.current = 57;
        state->navigation.stack[state->navigation.depth++] = 57;
        state->navigation.current = 59;
        state->navigation.stack[state->navigation.depth++] = 59;
        state->navigation.current = 52;
        state->navigation.stack[state->navigation.depth++] = 52;
        state->navigation.current = 51;
        state->navigation.stack[state->navigation.depth++] = 51;
        state->navigation.current = 41;
        state->navigation.stack[state->navigation.depth++] = 41;
        state->navigation.current = 40;
        state->navigation.stack[state->navigation.depth++] = 40;
        state->navigation.current = 57;
        state->navigation.stack[state->navigation.depth++] = 57;
        state->navigation.current = 52;
    } else {
        const struct SelectedRecord *record;
        union ControllerState *selected_state;
        union ControllerState *state;
        controller->dispatch.flags |= 2;
        record = GetStoredSelectedRecord();
        selected_state = controller;
        selected_state->dispatch.selected92 = record->id;
        selected_state->dispatch.message = 198;
        selected_state->dispatch.mode = 8;
        state = controller;
        state->dispatch.signature = 0x9001;
        state->dispatch.value = 0x1234;
        live_save.selected_id = state->dispatch.selected92;
        live_save.transaction = state->saved.value888;
        state->navigation.current = 12;
        state->navigation.stack[state->navigation.depth++] = 12;
        state->navigation.current = 42;
        state->navigation.stack[state->navigation.depth++] = 42;
        state->navigation.current = 40;
        state->navigation.stack[state->navigation.depth++] = 40;
        state->navigation.current = 57;
        state->navigation.stack[state->navigation.depth++] = 57;
        state->navigation.current = 56;
        state->navigation.stack[state->navigation.depth++] = 56;
        state->navigation.current = 41;
        state->navigation.stack[state->navigation.depth++] = 41;
        state->navigation.current = 40;
        state->navigation.stack[state->navigation.depth++] = 40;
        state->navigation.current = 57;
        state->navigation.stack[state->navigation.depth++] = 57;
        state->navigation.current = 52;
        state->navigation.stack[state->navigation.depth++] = 52;
        state->navigation.current = 53;
    }
}
