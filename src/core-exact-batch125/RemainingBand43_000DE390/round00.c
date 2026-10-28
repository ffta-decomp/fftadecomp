typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct ActorDirectionView { u8 unknown_00[31]; s8 direction; };
extern void ApplyActorMotionState(struct ActorDirectionView *, u32, s32, u32);
extern void ApplyActorFlagMasks(struct ActorDirectionView *, u16, u16);
extern void RefreshActorPresentation(struct ActorDirectionView *, u8);
void RestoreActorMotionPresentation(struct ActorDirectionView *actor)
{
    ApplyActorMotionState(actor, 1, actor->direction, 0);
    ApplyActorFlagMasks(actor, 0, 256);
    RefreshActorPresentation(actor, 1);
}
asm(".global ApplyActorMotionState\n.thumb_set ApplyActorMotionState,0x0809836d\n"
    ".global ApplyActorFlagMasks\n.thumb_set ApplyActorFlagMasks,0x0809a571\n"
    ".global RefreshActorPresentation\n.thumb_set RefreshActorPresentation,0x0809a531\n");
