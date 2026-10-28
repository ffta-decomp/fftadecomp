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
    u8 unknown3c2b[0x3ca8-0x3c2b];
};
typedef void (*ControllerCallback)(u32);
union ControllerState {
    struct { u16 current; u16 depth; u16 stack[1]; } navigation;
    struct { u8 unknown00[81]; u8 mode; u8 result; } dispatch;
    struct { u8 unknown00[236]; ControllerCallback pending; } callback;
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
extern void InvokeControllerCallback(u32,ControllerCallback);
asm(".global InvokeControllerCallback\n.thumb_set InvokeControllerCallback,0x08142249");
typedef char SaveImageCopySize[sizeof(struct SaveImage)==0x3ca8?1:-1];

void RestoreSelectedSaveRecordGroups(void)
{
    union ControllerState *state=controller;
    if(state->dispatch.result==255) {
        struct SaveImage *embedded=(struct SaveImage *)((u8 *)state+0x88c);
        struct SaveImage *live=&live_save;
        const u32 *options;
        PrepareSaveSlot((u8)(live->slot_count-1),embedded);
        controller->dispatch.result=0;
        options=&copy_options;
        InitializeBattleUnitRecord((u8 *)live+128,(u8 *)state+0x90c,0x18c0,*options);
        InitializeBattleUnitRecord((u8 *)live+0x1940,(u8 *)state+0x21cc,0x5a4,*options);
        InitializeBattleUnitRecord((u8 *)live+0x1ee4,(u8 *)state+0x2770,56,*options);
        InitializeBattleUnitRecord((u8 *)live+0x2b08,(u8 *)state+0x3394,256,*options);
    } else if(state->callback.pending) {
        struct SaveImage *snapshot=&snapshot_save;
        const u32 *options;
        InvokeControllerCallback(1,state->callback.pending);
        controller->callback.pending=0;
        options=&copy_options;
        InitializeBattleUnitRecord(snapshot,&live_save,0x3ca8,*options);
        snapshot->field2191=snapshot->field2190;
        snapshot->field219e=0;
        snapshot->field3c28=0;
        snapshot->field3c2a=0;
        snapshot->field203d=0;
        SetGameFlagInBuffer(64,0,(u8 *)snapshot);
        controller->dispatch.result=PrepareSaveSlot((u8)(live_save.slot_count-1),snapshot);
    }
    controller->dispatch.mode=64;
    {
        union ControllerState *resume_state=controller;
        resume_state->navigation.current=resume_state->navigation.stack[--resume_state->navigation.depth];
    }
}
