typedef unsigned char u8;
typedef unsigned short u16;
struct Actor;
extern void ApplyActorFlagMasks(struct Actor *, u16, u16);
void SelectActorFlag256(struct Actor *actor, u8 alternate)
{
    if (alternate != 0)
        ApplyActorFlagMasks(actor, 0, 256);
    else
        ApplyActorFlagMasks(actor, 256, 0);
}
asm(".global ApplyActorFlagMasks\n.thumb_set ApplyActorFlagMasks,0x0809a571\n");
