typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
struct ActorDirectionByteView { u8 unknown_00[31]; u8 stored_direction; };
struct ActorActionRecord { struct ActorDirectionByteView *actor; };
extern void ApplyRecordActorActionOverride(struct ActorActionRecord *, s32 direction);
void ApplyCurrentRecordActorAction(struct ActorActionRecord *record)
{
    u32 shifted = record->actor->stored_direction;
    shifted <<= 24;
    ApplyRecordActorActionOverride(record, (s32)shifted >> 24);
}
asm(".global ApplyRecordActorActionOverride\n.thumb_set ApplyRecordActorActionOverride,0x080ddda1\n");
