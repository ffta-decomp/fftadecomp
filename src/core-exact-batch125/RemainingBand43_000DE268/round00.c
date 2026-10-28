typedef unsigned char u8;
typedef signed char s8;
struct ActorDirectionView { u8 unknown_00[31]; s8 direction; };
extern void RefreshActorDirectionForFlags(struct ActorDirectionView *actor, int direction);
void RefreshActorCurrentDirection(struct ActorDirectionView *actor)
{
    RefreshActorDirectionForFlags(actor, actor->direction);
}
asm(".global RefreshActorDirectionForFlags\n.thumb_set RefreshActorDirectionForFlags,0x080de279\n");
