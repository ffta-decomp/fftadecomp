typedef unsigned char u8;
struct BattleRecordWorkspace {
    u8 unknown_0000[88];
    void *owned_allocation;
};
extern void FreeWorkspace(void *memory);
asm(".global FreeWorkspace\n.thumb_set FreeWorkspace,0x08022855");
void ReleaseBattleRecordWorkspace(struct BattleRecordWorkspace *workspace)
{
    if (workspace->owned_allocation != 0)
        FreeWorkspace(workspace->owned_allocation);
    FreeWorkspace(workspace);
}
