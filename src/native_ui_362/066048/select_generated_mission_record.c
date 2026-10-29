#include "interfaces.h"
asm(".global gContext\n.set gContext,0x0200f454\n.global gCopyRoutine\n.set gCopyRoutine,0x0836d4bc\n.global AllocateBuffer\n.thumb_set AllocateBuffer,0x8005b01\n.global FreeBuffer\n.thumb_set FreeBuffer,0x8005b0d\n.global GetGameFlag\n.thumb_set GetGameFlag,0x80c9541\n.global SetGameFlag\n.thumb_set SetGameFlag,0x80c9575\n.global FillRecords\n.thumb_set FillRecords,0x80d29d5\n.global CopyTrampoline\n.thumb_set CopyTrampoline,0x8142251\n");
void SelectGeneratedMissionRecord(u32 identifier) __asm__("RemainingCore48_00066048");
void SelectGeneratedMissionRecord(u32 identifier)
{
    int found = 0;
    int restore_flag = 0;
    struct Record *records;
    struct Record *record;
    int count;
    int index;
    u32 *copy_routine;
    records = AllocateBuffer(gContext->allocator,192);
    if (!GetGameFlag(54)) {
        restore_flag = 1;
        SetGameFlag(54,1);
    }
    count = FillRecords(records);
    if (restore_flag) SetGameFlag(54,0);
    record = records;
    index = 0;
    copy_routine = &gCopyRoutine;
    for (; index < count; index++,record++) {
        if (record->identifier == identifier) {
            found = 1;
            CopyTrampoline(&gContext->selection,record,16,*copy_routine);
            break;
        }
    }
    if (!found) {
        u32 *fallback_copy_address = &gCopyRoutine;
        /* The original defines the real copy-word address before preparing
           the destination, then reads the word for the fourth argument. */
        asm("" : "+l" (fallback_copy_address));
        CopyTrampoline(&gContext->selection,records,16,*fallback_copy_address);
    }
    FreeBuffer(gContext->allocator,records);
    gContext->selected = &gContext->selection;
}
