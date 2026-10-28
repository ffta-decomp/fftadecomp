typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct ActorActionView { u8 unknown_00[52]; u16 action; };
typedef char action_offset[(u32)&(((struct ActorActionView *)0)->action)==52?1:-1];
extern struct ActorActionView *ResolveActor(struct ActorActionView *);
extern void ApplyMappedActorDefaultAction(struct ActorActionView *, s32, u32);
extern u32 ReadActorFlag15(const struct ActorActionView *);
extern void RefreshActorDirectionForFlags(struct ActorActionView *, s32);
void ApplyActorVariantAction(struct ActorActionView *actor_argument, u32 direction_argument)
{
    register struct ActorActionView *actor asm("r4") = actor_argument;
    register u32 direction asm("r6");
    register struct ActorActionView *incoming_actor asm("r0") = actor_argument;
    register struct ActorActionView *resolved asm("r5");
    register u32 action asm("r0");
    /* These initialized native snapshots occupy distinct saved registers. */
    /* Native actor capture precedes the independent input-byte projection. */
    asm("" : : "r"(actor), "r"(incoming_actor));
    direction = (u8)direction_argument;
    resolved = ResolveActor(incoming_actor);
    asm("" : : "r"(actor), "r"(direction), "r"(resolved));
    ApplyMappedActorDefaultAction(actor, (s8)direction, 1);
    if ((u8)ReadActorFlag15(actor) != 0)
        action = 230;
    else
        action = 42;
    /* Both native arms define the full action value before the halfword store. */
    asm("" : "+r"(action));
    resolved->action = action;
    /* Preserve the live unsigned snapshot until the second projection phase. */
    asm("" : "+r"(direction));
    RefreshActorDirectionForFlags(actor, (s8)direction);
}
asm(".global ResolveActor\n.thumb_set ResolveActor,0x080dd351\n"
    ".global ApplyMappedActorDefaultAction\n.thumb_set ApplyMappedActorDefaultAction,0x080de33d\n"
    ".global ReadActorFlag15\n.thumb_set ReadActorFlag15,0x080dd73d\n"
    ".global RefreshActorDirectionForFlags\n.thumb_set RefreshActorDirectionForFlags,0x080de279\n");
