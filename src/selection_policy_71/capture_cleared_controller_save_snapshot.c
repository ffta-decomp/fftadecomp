/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SaveImage {
 u8 unknown00[0x203d]; u8 field203d;
 u8 unknown203e[0x2190 - 0x203e]; u8 field2190; u8 field2191;
 u8 unknown2192[12]; u16 field219e;
 u8 unknown21a0[0x3c24 - 0x21a0]; u32 field3c24; u16 field3c28; u8 field3c2a;
 u8 unknown3c2b[0x3ca8 - 0x3c2b];
};
struct ControllerState {u8 unknown00[0x88c]; struct SaveImage snapshot;};
extern struct ControllerState *controller;
extern struct SaveImage live_save;
extern const u32 copy_options;
extern void InitializeBattleUnitRecord(void *,const void *,u32,u32);
extern void SetGameFlagInBuffer(u16,u16,u8 *);
typedef char SaveImageCopySize[sizeof(struct SaveImage)==0x3ca8?1:-1];
typedef char ControllerSize[sizeof(struct ControllerState)==0x4534?1:-1];
asm(".global controller\n.set controller,0x0200f450\n.global live_save\n.set live_save,0x02000000\n.global copy_options\n.set copy_options,0x0836d4bc");
asm(".global SetGameFlagInBuffer\n.thumb_set SetGameFlagInBuffer,0x080c960d");

void CaptureClearedControllerSaveSnapshot(void)
{
    struct ControllerState *state=controller;
    struct SaveImage *snapshot=&state->snapshot;
    const u32 *options=&copy_options;
    InitializeBattleUnitRecord(snapshot,&live_save,0x3ca8,*options);
    state->snapshot.field2191=state->snapshot.field2190;
    state->snapshot.field219e=0;
    state->snapshot.field3c28=0;
    state->snapshot.field3c2a=0;
    state->snapshot.field3c24=0;
    state->snapshot.field203d=0;
    SetGameFlagInBuffer(64,0,(u8 *)snapshot);
}
