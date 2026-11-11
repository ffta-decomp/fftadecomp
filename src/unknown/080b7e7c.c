typedef unsigned int u32;
typedef void (*MemoryRoutine)(void *destination, u32 byte_count);
extern MemoryRoutine const gClearBytesRoutine;
extern void CallMemoryRoutine(void *destination, u32 byte_count, MemoryRoutine routine);
extern void ReleaseGlobalPoolAllocation(void *allocation);
asm(".global gClearBytesRoutine\n.set gClearBytesRoutine,0x0836d4b8\n.global CallMemoryRoutine\n.thumb_set CallMemoryRoutine,0x0814224d\n.global ReleaseGlobalPoolAllocation\n.thumb_set ReleaseGlobalPoolAllocation,0x08022855");

void ClearAndReleaseBattleRecord(void *record)
{
    MemoryRoutine const *routine_cell = &gClearBytesRoutine;
    CallMemoryRoutine(record, 4448, *routine_cell);
    ReleaseGlobalPoolAllocation(record);
}
