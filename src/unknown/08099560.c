typedef unsigned char u8;
typedef unsigned int u32;
struct BattleContext { u8 unknown_00[16]; void *primary_actors; };
struct ActorSearch { void *unit; u32 unaccessed_word; void *found; };
extern void WalkActorList(void *, void *, struct ActorSearch *);
asm(".global WalkActorList\n.thumb_set WalkActorList,0x080c7cc1");

void *FindPrimaryBattleActor(struct BattleContext *context, void *unit)
{
    struct ActorSearch search;
    search.unit = unit;
    search.found = 0;
    WalkActorList(context->primary_actors, (void *)0x0809ab5d, &search);
    return search.found;
}
