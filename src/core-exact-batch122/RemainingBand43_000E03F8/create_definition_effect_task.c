#include "../../../src/task_tree_core.h"
typedef signed short s16;

struct DefinitionEffectStartup {
    u32 delay : 16;
    u32 count : 8;
    u32 reserved : 8;
    const void *sequence;
};
typedef char DefinitionEffectStartupMustBe8Bytes[
    sizeof(struct DefinitionEffectStartup) == 8 ? 1 : -1];
extern void *GetRecordNestedPointer(void *record);
extern void ProjectNestedRecord(void *, s16 *, s16 *, s16 *);
extern u32 QueryRecordBoundary(void *record);
extern u32 QueryCurrentBoundary(void);
extern u32 QueryNestedBoundary(void *record);
extern void ProjectRecordPosition(void *, s16 *, s16 *, s16 *);
extern u32 QueryPositionBoundary(s16 x, s16 y);
extern TaskGroup *gDefinitionEffectTaskGroup;
extern void AdvanceDefinitionEffectChild(TaskNode *, u16 *, void *);

TaskNode *CreateDefinitionEffectTask(void *record, const void *sequence,
                                    u8 count, u8 position_mode,
                                    const s16 *coordinates, TaskNode *parent)
{
    struct DefinitionEffectStartup startup;
    s16 nested_x, nested_y, nested_z;
    s16 record_x, record_y, record_z;
    u32 event[7];

    if (count == 0 && position_mode == 7)
        return 0;
    /* The reserved byte is not consumed by the immediate initialization. */
    startup.count = count;
    startup.sequence = sequence;
    startup.delay = 0;
    switch (position_mode) {
    case 0:
        ProjectNestedRecord(GetRecordNestedPointer(record),
                            &nested_x, &nested_y,
                            &nested_z);
        QueryPositionBoundary((s16)(nested_x - 120),
                              (s16)(nested_y - 96));
        break;
    case 1:
        if ((u8)QueryRecordBoundary(record) != 0)
            startup.delay = 20;
        break;
    case 2:
        QueryRecordBoundary(record);
        break;
    case 3:
        if ((u8)QueryCurrentBoundary() != 0)
            startup.delay = 20;
        break;
    case 4:
        if ((u8)QueryNestedBoundary(record) != 0)
            startup.delay = 20;
        break;
    case 5:
        ProjectRecordPosition(record, &record_x,
                              &record_y, &record_z);
        QueryPositionBoundary((s16)(record_x - 120),
                              (s16)(record_y - 120));
        break;
    case 6:
        if ((u8)QueryPositionBoundary(coordinates[0], coordinates[1]) != 0)
            startup.delay = 20;
        break;
    }
    /* The creator sets state 0; its immediate callback reads only word 1. */
    event[1] = (u32)&startup;
    return CreateTaskNode_08005954(gDefinitionEffectTaskGroup,
                                  AdvanceDefinitionEffectChild, 12,
                                  event, parent);
}

asm(".global GetRecordNestedPointer\n.thumb_set GetRecordNestedPointer,0x080DD47D\n"
    ".global ProjectNestedRecord\n.thumb_set ProjectNestedRecord,0x080DBDA1\n"
    ".global QueryRecordBoundary\n.thumb_set QueryRecordBoundary,0x080D8CD5\n"
    ".global QueryCurrentBoundary\n.thumb_set QueryCurrentBoundary,0x080D85A1\n"
    ".global QueryNestedBoundary\n.thumb_set QueryNestedBoundary,0x080DC1D1\n"
    ".global ProjectRecordPosition\n.thumb_set ProjectRecordPosition,0x080D8BD9\n"
    ".global QueryPositionBoundary\n.thumb_set QueryPositionBoundary,0x080D8B29\n"
    ".global CreateTaskNode_08005954\n.thumb_set CreateTaskNode_08005954,0x08005955\n"
    ".global gDefinitionEffectTaskGroup\n.set gDefinitionEffectTaskGroup,0x0200F430\n"
    ".global AdvanceDefinitionEffectChild\n.thumb_set AdvanceDefinitionEffectChild,0x080DFF05\n");
