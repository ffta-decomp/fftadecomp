/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct ProgressUnit {
    u8 prefix[10];
    u8 progress;
} ProgressUnit;
typedef struct ProgressNode {
    ProgressUnit *unit;
} ProgressNode;
typedef struct ProgressEntry {
    ProgressNode *node;
    u16 increment;
    u16 unknown_6;
} ProgressEntry;
typedef struct ProgressResult {
    ProgressNode *advanced_nodes[13];
    u16 advanced_count;
    u8 unknown_54[6];
    ProgressEntry *entries;
    u8 unknown_64;
    u8 processed_count;
    u8 remaining[74];
} ProgressResult;
#define OFFSET(T,M) ((u32)&(((T*)0)->M))
typedef char EntrySize[sizeof(ProgressEntry)==8?1:-1];
typedef char ResultSize[sizeof(ProgressResult)==140?1:-1];
typedef char ResultCount[OFFSET(ProgressResult,advanced_count)==52?1:-1];
typedef char ResultEntries[OFFSET(ProgressResult,entries)==60?1:-1];
typedef char ResultProcessed[OFFSET(ProgressResult,processed_count)==65?1:-1];
extern void *Allocate(u32);
extern void Release(void *);
extern void (*ClearMemory)(void *,u32);
extern void GatherProgress(ProgressResult *, void *, ProgressEntry *);
extern u32 ReadUnitField(const void *,u8);
extern u32 AdvanceUnitGrowth(ProgressUnit *);
__asm__(".global Allocate\n.thumb_set Allocate, 0x08022841");
__asm__(".global Release\n.thumb_set Release, 0x08022855");
__asm__(".global ClearMemory\n.set ClearMemory, 0x0836d4b8");
__asm__(".global GatherProgress\n.thumb_set GatherProgress, 0x080a7041");
__asm__(".global ReadUnitField\n.thumb_set ReadUnitField, 0x080c7ea5");
__asm__(".global AdvanceUnitGrowth\n.thumb_set AdvanceUnitGrowth, 0x080c9b8d");

__asm__(".global _call_via_r0\n.thumb_set _call_via_r0, 0x08142245");

__asm__(".global _call_via_r1\n.thumb_set _call_via_r1, 0x08142249");

__asm__(".global _call_via_r2\n.thumb_set _call_via_r2, 0x0814224d");

__asm__(".global _call_via_r3\n.thumb_set _call_via_r3, 0x08142251");

__asm__(".global _call_via_r4\n.thumb_set _call_via_r4, 0x08142255");

__asm__(".global _call_via_r5\n.thumb_set _call_via_r5, 0x08142259");

__asm__(".global _call_via_r6\n.thumb_set _call_via_r6, 0x0814225d");


/* Gather progress from one or two inputs and retain each successfully advanced
 * node. Field sums narrow to signed16 before the threshold, never before addition. */
ProgressResult *BuildUnitProgressResults(void *first, void *second)
{
    ProgressResult *result = Allocate(140);
    ProgressEntry *entries;
    ProgressEntry *entry;
    int index;
    s16 progress;

    ClearMemory(result, 140);
    entries = Allocate(104);
    ClearMemory(entries, 104);
    GatherProgress(result, first, entries);
    if (second != 0)
        GatherProgress(result, second, entries);
    for (index = 0; index < 13 && entries[index].node != 0; index++) {
        entry = &entries[index];
        progress = ReadUnitField(entry->node->unit, 7) + entry->increment;
        if (progress <= 99) {
            entry->node->unit->progress = progress;
        } else {
            entry->node->unit->progress = 0;
            if ((u8)AdvanceUnitGrowth(entry->node->unit))
                result->advanced_nodes[result->advanced_count++] = entry->node;
        }
    }
    result->processed_count = index;
    result->entries = entries;
    if (result->advanced_count == 0 && result->processed_count == 0) {
        Release(entries);
        Release(result);
        return 0;
    }
    return result;
}
