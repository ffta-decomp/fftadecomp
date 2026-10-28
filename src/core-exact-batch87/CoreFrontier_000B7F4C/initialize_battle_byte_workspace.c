typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
typedef void (*MemoryRoutine)(void *, u32);
struct BattleByteWorkspace {
    u32 unknown_00[2];
    u8 first_sentinel;
    s8 second_sentinel;
    u8 unknown_0a[2];
};
extern struct BattleByteWorkspace gBattleByteWorkspace;
extern MemoryRoutine const gClearBytesRoutine;
extern void CallMemoryRoutine(void *, u32, MemoryRoutine);
asm(".global gBattleByteWorkspace\n.set gBattleByteWorkspace,0x02010050\n.global gClearBytesRoutine\n.set gClearBytesRoutine,0x0836d4b8\n.global CallMemoryRoutine\n.thumb_set CallMemoryRoutine,0x0814224d");

void InitializeBattleByteWorkspace(void)
{
    MemoryRoutine const *routine_cell = &gClearBytesRoutine;
    struct BattleByteWorkspace *workspace = &gBattleByteWorkspace;
    CallMemoryRoutine(workspace, 12, *routine_cell);
    workspace->first_sentinel = 255;
    workspace->second_sentinel = -1;
}
