typedef unsigned char u8;
typedef signed char s8;
typedef signed int s32;
typedef unsigned int u32;
struct ActorDirectionView { u8 unknown_00[31]; s8 direction; };
typedef char direction_offset[(u32)&(((struct ActorDirectionView *)0)->direction)==31?1:-1];
extern void ApplyActorVariantAction(struct ActorDirectionView *, s32);
void ApplyCurrentActorVariantAction(struct ActorDirectionView *actor)
{
    ApplyActorVariantAction(actor, actor->direction);
}
asm(".global ApplyActorVariantAction\n.thumb_set ApplyActorVariantAction,0x080df871\n");
