typedef unsigned short u16;
typedef unsigned int u32;
typedef void (*MemoryRoutine)(void *, u32);
struct BattlePhaseRecord {
    void *source;
    u32 unknown_04;
    u16 value;
    u16 unknown_0a;
    u16 selector;
    u16 depth;
    u16 continuation_selectors[34];
};
typedef char RecordViewIs84Bytes[sizeof(struct BattlePhaseRecord) == 84 ? 1 : -1];
extern MemoryRoutine const gClearBytesRoutine;
extern void CallMemoryRoutine(void *, u32, MemoryRoutine);
asm(".global gClearBytesRoutine\n.set gClearBytesRoutine,0x0836d4b8\n.global CallMemoryRoutine\n.thumb_set CallMemoryRoutine,0x0814224d");

void InitializeBattlePhaseRecord(struct BattlePhaseRecord *record, void *source, u16 value)
{
    MemoryRoutine const *routine_cell = &gClearBytesRoutine;
    CallMemoryRoutine(record, 84, *routine_cell);
    record->source = source;
    record->value = value;
    record->selector = 8;
    record->continuation_selectors[record->depth++] = 8;
    record->selector = 6;
    record->continuation_selectors[record->depth++] = 6;
    record->selector = 4;
    record->continuation_selectors[record->depth++] = 4;
    record->selector = 2;
    record->continuation_selectors[record->depth++] = 2;
    record->selector = 3;
    record->continuation_selectors[record->depth++] = 3;
    record->selector = 0;
}
