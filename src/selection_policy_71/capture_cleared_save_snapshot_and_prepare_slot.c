/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SaveImage {
    u8 unknown00[0x72]; u8 slot_count;
    u8 unknown73[0x203d-0x73]; u8 field203d;
    u8 unknown203e[0x2190-0x203e]; u8 field2190; u8 field2191;
    u8 unknown2192[12]; u16 field219e;
    u8 unknown21a0[0x3c28-0x21a0]; u16 field3c28; u8 field3c2a;
};
union ControllerState {
    struct { u16 current; u16 depth; u16 stack[1]; } navigation;
    struct { u8 unknown00[81]; u8 mode; u8 result; } dispatch;
};
extern struct SaveImage live_save;
extern struct SaveImage snapshot_save;
extern union ControllerState *controller;
extern void InitializeBattleUnitRecord(void *,const void *,u32,u32);
extern void SetGameFlagInBuffer(u16,u16,u8 *);
extern u32 PrepareSaveSlot(u8,struct SaveImage *);
asm(".global live_save\n.set live_save,0x02000000\n.global snapshot_save\n.set snapshot_save,0x02003cb0\n.global controller\n.set controller,0x0200f450\n.global PrepareSaveSlot\n.thumb_set PrepareSaveSlot,0x0813b0d5");
asm(".global SetGameFlagInBuffer\n.thumb_set SetGameFlagInBuffer,0x080c960d");
extern const u32 copy_options;
asm(".global copy_options\n.set copy_options,0x0836d4bc");

void CaptureClearedSaveSnapshotAndPrepareSlot(void)
{
    union ControllerState *state;
    struct SaveImage *snapshot=&snapshot_save;
    const u32 *options=&copy_options;
    InitializeBattleUnitRecord(snapshot,&live_save,0x3ca8,*options);
    snapshot_save.field2191=snapshot_save.field2190;
    snapshot_save.field219e=0;
    snapshot_save.field3c28=0;
    snapshot_save.field3c2a=0;
    snapshot_save.field203d=0;
    SetGameFlagInBuffer(64,0,(u8 *)&snapshot_save);
    controller->dispatch.result=PrepareSaveSlot((u8)(live_save.slot_count-1),&snapshot_save);
    controller->dispatch.mode=32;
    state=controller;
    state->navigation.current=state->navigation.stack[--state->navigation.depth];
    state->navigation.stack[state->navigation.depth++]=state->navigation.current;
    state->navigation.current=55;
}
