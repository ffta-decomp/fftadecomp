typedef unsigned char u8;
typedef unsigned int u32;
struct TurnSelectionWorkspace {
    u8 unknown_0000[32];
    void *handle;
    u32 unknown_0036;
    void *allocation;
};
extern struct TurnSelectionWorkspace *gTurnSelectionWorkspace;
extern void ReleaseHandleContents(void *handle, void *allocation);
asm(".global gTurnSelectionWorkspace\n.set gTurnSelectionWorkspace,0x0200f438\n.global ReleaseHandleContents\n.thumb_set ReleaseHandleContents,0x08005b0d");
void ReleaseSelectedBattleHandle(void)
{
    struct TurnSelectionWorkspace *workspace = gTurnSelectionWorkspace;
    void *allocation = workspace->allocation;
    if (allocation != 0)
        ReleaseHandleContents(workspace->handle, allocation);
}
