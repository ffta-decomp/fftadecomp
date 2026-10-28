#include "../../../src/task_tree_core.h"

typedef signed short s16;
typedef signed int s32;
struct ActorRecordReference { void *actor; };
extern void ProjectDefinitionActorPosition(void *,u16 *,u16 *);
extern void CopyDefinitionRecordCoordinates(void *,u16 *,u16 *,u16 *);
extern void ApplyActorDefaultDirection(void *);
extern void ApplyDefinitionRecordCurrentValue(void *,u16);

void *ProjectActorAndApplyValue(void *record,
    u16 *x,u16 *y,u16 *z,u16 value)
{
    s32 signed_value;
    register u32 shifted_value __asm__("r1");
    record = record != 0 ? ((struct ActorRecordReference *)record)->actor : 0;
    if (z == 0)
        ProjectDefinitionActorPosition(record,x,y);
    else
        CopyDefinitionRecordCoordinates(record,x,y,z);
    shifted_value = (u32)value << 16;
    /* Native R1 retains the initialized bits for both signed and unsigned views. */
    __asm__("" : : "r" (shifted_value));
    signed_value = (s32)shifted_value >> 16;
    if (signed_value != -1) {
        if (signed_value == -2)
            ApplyActorDefaultDirection(record);
        else
            ApplyDefinitionRecordCurrentValue(record,shifted_value >> 16);
    }
    return record;
}

__asm__(".global ProjectDefinitionActorPosition\n"
        ".thumb_set ProjectDefinitionActorPosition,0x080dbdc9\n"
        ".global CopyDefinitionRecordCoordinates\n"
        ".thumb_set CopyDefinitionRecordCoordinates,0x080dbd5d\n"
        ".global ApplyActorDefaultDirection\n"
        ".thumb_set ApplyActorDefaultDirection,0x080de269\n"
        ".global ApplyDefinitionRecordCurrentValue\n"
        ".thumb_set ApplyDefinitionRecordCurrentValue,0x080de10d\n");
