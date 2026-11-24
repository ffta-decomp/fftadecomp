typedef unsigned char u8;
typedef unsigned int u32;
typedef void (*MemoryRoutine)(void *, u32);
struct BattleNodeWorkspaceView {
    u8 unknown_00[116];
    void *node;
    u8 unknown_78[72];
};
extern struct BattleNodeWorkspaceView gBattleNodeWorkspace;
extern MemoryRoutine const gClearBytesRoutine;
extern void CallMemoryRoutine(void *, u32, MemoryRoutine);
asm(".global gBattleNodeWorkspace\n.set gBattleNodeWorkspace,0x02010130\n.global gClearBytesRoutine\n.set gClearBytesRoutine,0x0836d4b8\n.global CallMemoryRoutine\n.thumb_set CallMemoryRoutine,0x0814224d");

void InitializeBattleNodeWorkspace(void *node)
{
    MemoryRoutine const *routine_cell = &gClearBytesRoutine;
    struct BattleNodeWorkspaceView *workspace = &gBattleNodeWorkspace;
    CallMemoryRoutine(workspace, 192, *routine_cell);
    workspace->node = node;
}
