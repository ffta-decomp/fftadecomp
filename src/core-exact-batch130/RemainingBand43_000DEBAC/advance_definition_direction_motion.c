#include "../../../src/task_tree_core.h"

typedef signed char s8;
struct DefinitionSetupStartupBytes {
    void *record;
    u8 period;
    u8 clockwise;
    u8 repetitions;
    u8 unconsumed;
};
struct DefinitionDirectionMotion {
    void *record;
    u16 delay;
    u8 ticks_remaining;
    u8 initial_direction;
    u8 direction;
    u8 period;
    u8 clockwise;
    u8 repetitions;
    u16 value;
    u16 unknown_0e;
};
typedef char MotionPayloadSize[sizeof(struct DefinitionDirectionMotion)==16?1:-1];
extern u8 ReadDefinitionRecordDirection(const void *);
extern void ApplyDefinitionRecordSignedValue(void *,u16,int);
extern void ApplyMappedActorDefaultAction(void *,int,u32);
u32 AdvanceDefinitionDirectionMotion(TaskNode *,u16 *,struct DefinitionDirectionMotion *)
    asm("RemainingBand43_000DEBAC");
u32 AdvanceDefinitionDirectionMotion(TaskNode *task,u16 *event,
                                     struct DefinitionDirectionMotion *payload)
{
    switch (event[0]) {
    case 0: {
        struct DefinitionSetupStartupBytes *startup=*(struct DefinitionSetupStartupBytes **)(event+2);
        payload->record=startup->record;
        payload->period=startup->period;
        payload->clockwise=startup->clockwise;
        payload->repetitions=startup->repetitions;
        payload->initial_direction=ReadDefinitionRecordDirection(payload->record);
        payload->direction=payload->initial_direction;
        payload->ticks_remaining=payload->period;
        payload->delay=event[10]+1;
        break;
    }
    case 1:
        break;
    case 256:
        if (payload->delay!=0) {
            payload->delay--;
            if (payload->delay!=0)
                break;
        }
        payload->ticks_remaining--;
        if (payload->ticks_remaining!=0)
            break;
        if (payload->clockwise!=0) {
            if ((s8)payload->direction==3)
                payload->direction=0;
            else
                payload->direction++;
        } else {
            if ((s8)payload->direction==0)
                payload->direction=3;
            else
                payload->direction--;
        }
        if (payload->value!=0)
            ApplyDefinitionRecordSignedValue(payload->record,payload->value,(s8)payload->direction);
        else
            ApplyMappedActorDefaultAction(payload->record,(s8)payload->direction,0);
        payload->ticks_remaining=payload->period;
        if ((s8)payload->repetitions!=-1)
            payload->repetitions--;
        if ((s8)payload->repetitions==0)
            event[0]=2;
        break;
    }
    return 0;
}
asm(".global ReadDefinitionRecordDirection\n.thumb_set ReadDefinitionRecordDirection,0x080dbc89\n"
    ".global ApplyDefinitionRecordSignedValue\n.thumb_set ApplyDefinitionRecordSignedValue,0x080de12d\n"
    ".global ApplyMappedActorDefaultAction\n.thumb_set ApplyMappedActorDefaultAction,0x080de33d\n");
