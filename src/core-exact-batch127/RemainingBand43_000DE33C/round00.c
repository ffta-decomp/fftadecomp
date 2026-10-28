typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct Actor;
extern void *CopyExistingBytes(void *, const void *, u32);
extern void ApplyActorMotionState(struct Actor *, u32, s32, u32);
extern void ApplyActorFlagMasks(struct Actor *, u16, u16);
extern void RefreshActorPresentation(struct Actor *, u8);
void ApplyMappedActorDefaultAction(struct Actor *actor, u8 direction, u8 variant)
{
    u16 values[2];
    u16 value;
    s32 signed_direction;
    CopyExistingBytes(values, (const void *)0x08149b70, 4);
    value = values[variant];
    signed_direction = (s8)direction;
    ApplyActorMotionState(actor, value, signed_direction, 0);
    ApplyActorFlagMasks(actor, 0, 256);
    if (variant == 0)
        RefreshActorPresentation(actor, 1);
}
asm(".global CopyExistingBytes\n.thumb_set CopyExistingBytes,0x081443fd\n"
    ".global ApplyActorMotionState\n.thumb_set ApplyActorMotionState,0x0809836d\n"
    ".global ApplyActorFlagMasks\n.thumb_set ApplyActorFlagMasks,0x0809a571\n"
    ".global RefreshActorPresentation\n.thumb_set RefreshActorPresentation,0x0809a531\n");
