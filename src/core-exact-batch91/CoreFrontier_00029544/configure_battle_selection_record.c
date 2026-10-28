typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct TurnSelectionWorkspace {
    u8 unknown_0000[32];
    void *handle;
    u32 unknown_0036;
    void *allocation;
};
extern u16 gBattleStateFlags;
extern struct TurnSelectionWorkspace *gTurnSelectionWorkspace;
extern u8 gSelectionOutput[];
extern u8 gSelectionState[];
extern const u8 gFirstSelectionCallback[];
extern const u8 gSecondSelectionCallback[];
extern void *AllocateSelectionMemory(void *handle,u32 size);
extern void ConfigureSelectionRecord(void *record,u8 layout,u16 code,
    void *output,void *state,u16 first,u16 second,u8 width,u8 option,u16 limit);
extern void SetSelectionState(u16 state);
extern void SetSelectionCallbacks(const void *first,const void *second);
asm(".global gBattleStateFlags\n.set gBattleStateFlags,0x03000940\n.global gTurnSelectionWorkspace\n.set gTurnSelectionWorkspace,0x0200f438\n.global gSelectionOutput\n.set gSelectionOutput,0x030008b0\n.global gSelectionState\n.set gSelectionState,0x03000990\n.global gFirstSelectionCallback\n.set gFirstSelectionCallback,0x08028b95\n.global gSecondSelectionCallback\n.set gSecondSelectionCallback,0x08028ba9\n.global AllocateSelectionMemory\n.thumb_set AllocateSelectionMemory,0x08005b01\n.global ConfigureSelectionRecord\n.thumb_set ConfigureSelectionRecord,0x0801174d\n.global SetSelectionState\n.thumb_set SetSelectionState,0x0801339d\n.global SetSelectionCallbacks\n.thumb_set SetSelectionCallbacks,0x08013405");
void ConfigureBattleSelectionRecord(u8 mode)
{
    int expanded = 0;
    u8 code = 0;
    void *allocation;
    register u32 old_flags asm("r1") = gBattleStateFlags;
    register u32 mask asm("r4") = 0x0c00;
    register u32 merged_flags asm("r0");
    /* Preserve the observed old-halfword operand across mask formation. */
    asm("" : "+r" (old_flags), "+r" (mask));
    merged_flags = mask | old_flags;
    /* The observed OR result occupies r0 independently of its old-value input. */
    asm("" : "+r" (merged_flags));
    gBattleStateFlags = merged_flags;
    switch (mode) {
    case 1: expanded = 1; code = 1; break;
    case 2: expanded = 1; code = 13; break;
    case 3: code = 5; break;
    case 4: code = 6; break;
    case 5: code = 33; break;
    case 6: case 7: case 9: case 10: code = (u8)(mode + 18); break;
    case 8: code = 35; break;
    case 11: code = 12; break;
    }
    allocation = AllocateSelectionMemory(gTurnSelectionWorkspace->handle,2564);
    gTurnSelectionWorkspace->allocation = allocation;
    if (expanded) {
        ConfigureSelectionRecord(allocation,2,code,gSelectionOutput,
                                 gSelectionState,2,2,24,0,928);
        SetSelectionState(2);
    } else {
        ConfigureSelectionRecord(allocation,1,code,gSelectionOutput,
                                 gSelectionState,2,2,24,4,928);
        SetSelectionState(2);
    }
    SetSelectionCallbacks(gFirstSelectionCallback,gSecondSelectionCallback);
}
