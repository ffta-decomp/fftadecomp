/* Original authored threshold command; retain existing helper bodies. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct SceneCommandHandleRecord { u8 prefix[4]; u8 active; u8 reserved05[19]; u16 current_value; u16 maximum_value; };
typedef char threshold_current_offset_check[((u32)&(((struct SceneCommandHandleRecord*)0)->current_value)==24)?1:-1];
extern struct SceneCommandHandleRecord *ResolveSceneCommandHandle(u32);
extern u32 SceneCommandRecordBlocksUpdateA(struct SceneCommandHandleRecord *);
extern u32 SceneCommandRecordBlocksUpdateB(struct SceneCommandHandleRecord *);
extern s32 DivideSignedValues(s32,s32);
u32 AddSceneContextDeltaWhenCommandThresholdIsExceeded(u16 *scene_context,const u8 *command)
{
    struct SceneCommandHandleRecord *record;
    u32 threshold;
    int should_add;
    s32 current_value;
    record = ResolveSceneCommandHandle(command[1]);
    if (record == 0)
        goto finished;
    if (record->active == 0)
        goto finished;
    if ((u8)SceneCommandRecordBlocksUpdateA(record) != 0)
        goto finished;
    if ((u8)SceneCommandRecordBlocksUpdateB(record) != 0)
        goto finished;
    threshold = command[2];
    should_add = 0;
    if (threshold <= 9) {
        if (record->current_value <= threshold)
            goto test_add;
        goto add_delta;
    } else {
        current_value = record->current_value;
        if (current_value > DivideSignedValues(record->maximum_value * threshold, 100))
            should_add = 1;
    }
test_add:
    if (should_add == 0)
        goto finished;
add_delta:
    scene_context[0] += command[3] | (command[4] << 8);
finished:
    return 0x110;
}
