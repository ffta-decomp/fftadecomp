/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct LiveSave {
 u8 unknown00[0x1f64]; u32 balance;
 u8 unknown1f68[0x219e - 0x1f68]; u16 field219e;
 u8 unknown21a0[0x3c24 - 0x21a0]; u32 field3c24; u16 field3c28; u8 field3c2a;
};
union ControllerState {
 struct {u16 current; u16 depth; u16 first;} navigation;
 struct {u8 unknown00[84]; u32 flags;} transaction;
 struct {u8 unknown00[0x884]; void *buffer;} display;
};
struct SceneStatus {u8 unknown00[5]; u8 active;};
extern struct LiveSave live_save;
extern union ControllerState *controller;
extern struct SceneStatus scene_status;
extern u8 graphics_context[], palette_context[];
extern void ReleaseOwnedBuffer(void *);
extern void WriteSaveByte(u16,u8);
extern void ResetSceneHardware(void);
extern void *Allocate(u32);
extern void InitializeSceneDisplay(void *,u8,u16,void *,void *,u16,u16,u8,u8,u16);
extern void SetSceneDisplayFlags(u16);
extern void SetSceneDisplayBounds(u8,u8,u8,u8);
typedef char LiveSaveStorage[(sizeof(struct LiveSave)==0x3c2c)?1:-1];
asm(".global live_save\n.set live_save,0x02000000");
asm(".global controller\n.set controller,0x0200f450");
asm(".global scene_status\n.set scene_status,0x03000ed0");
asm(".global graphics_context\n.set graphics_context,0x030008b0");
asm(".global palette_context\n.set palette_context,0x03000990");
asm(".global ReleaseOwnedBuffer\n.thumb_set ReleaseOwnedBuffer,0x080c746d");
asm(".global ResetSceneHardware\n.thumb_set ResetSceneHardware,0x08004c41");
asm(".global Allocate\n.thumb_set Allocate,0x08022841");
asm(".global InitializeSceneDisplay\n.thumb_set InitializeSceneDisplay,0x0801174d");
asm(".global SetSceneDisplayFlags\n.thumb_set SetSceneDisplayFlags,0x0801339d");
asm(".global SetSceneDisplayBounds\n.thumb_set SetSceneDisplayBounds,0x0802a2c1");

void ResetSelectionAndCreateDisplay(void)
{
    void *buffer;
    scene_status.active=1;
    live_save.field3c24=0;
    live_save.field219e=0;
    live_save.field3c28=0;
    live_save.field3c2a=0;
    if(controller->transaction.flags&64) {
        live_save.balance+=5000;
        controller->transaction.flags&=~64;
    }
    ReleaseOwnedBuffer((u8 *)controller+108);
    WriteSaveByte(13,0);
    ResetSceneHardware();
    buffer=Allocate(0xa04);
    controller->display.buffer=buffer;
    InitializeSceneDisplay(buffer,1,12,graphics_context,palette_context,2,2,24,4,928);
    SetSceneDisplayFlags(2);
    SetSceneDisplayBounds(2,2,26,6);
    controller->navigation.depth=1;
    controller->navigation.first=1;
    controller->navigation.current=52;
}
