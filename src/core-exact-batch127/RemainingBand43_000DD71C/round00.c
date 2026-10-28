typedef unsigned char u8;
typedef unsigned int u32;
struct ActorFlagView { u8 unknown_00[48]; u32 flags; };
typedef char flag_offset[(u32)&(((struct ActorFlagView *)0)->flags)==48?1:-1];
u32 ReadActorFlagWord(const struct ActorFlagView *actor)
{
    return actor->flags;
}
