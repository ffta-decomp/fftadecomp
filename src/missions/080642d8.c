/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
struct SaveImage {u8 unknown00[0x219e]; u16 field219e;};
union ControllerState {
 struct {u16 current;u16 depth;u16 stack[1];} navigation;
 struct {u8 unknown00[77];u8 enabled;u16 field78;} dispatch;
};
extern struct SaveImage live_save;
extern union ControllerState *controller;
extern void WriteSaveByte(u16,u8);
extern void ResetSceneHardware(void);
asm(".global live_save\n.set live_save,0x02000000\n.global controller\n.set controller,0x0200f450\n.global ResetSceneHardware\n.thumb_set ResetSceneHardware,0x08004c41");
typedef char SaveLayout[sizeof(struct SaveImage)==0x21a0?1:-1];

void ResetSaveModeAndScheduleSelection(void)
{
    union ControllerState *state;
    WriteSaveByte(13,0);
    ResetSceneHardware();
    live_save.field219e=0;
    controller->dispatch.field78=166;
    controller->dispatch.enabled=1;
    state=controller;
    state->navigation.current=2;
    state->navigation.stack[state->navigation.depth++]=2;
    state->navigation.current=49;
    state->navigation.stack[state->navigation.depth++]=49;
    state->navigation.current=52;
    state->navigation.stack[state->navigation.depth++]=52;
    state->navigation.current=53;
}
