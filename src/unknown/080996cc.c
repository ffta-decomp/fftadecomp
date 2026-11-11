typedef unsigned char u8;
typedef unsigned int u32;

struct BattleActor { void *unit; u8 unknown_04[32]; u32 index_key; };
struct BattleContext { u8 unknown_00[20]; void *default_actors; };
struct ActorSearch { void *unit; u32 unaccessed_word; struct BattleActor *found; };

extern void WalkActorList(void *list, void *callback, struct ActorSearch *search);
extern struct BattleActor *CreateBattleActor(struct BattleContext *context, void *unit);
extern void AppendActorToList(void *list, struct BattleActor *actor);
extern void IndexActorInList(void *list, struct BattleActor *actor, u32 key);
asm(".global WalkActorList\n.thumb_set WalkActorList,0x080c7cc1\n"
    ".global CreateBattleActor\n.thumb_set CreateBattleActor,0x0809716d\n"
    ".global AppendActorToList\n.thumb_set AppendActorToList,0x080c7a75\n"
    ".global IndexActorInList\n.thumb_set IndexActorInList,0x080c7ab5");

struct BattleActor *FindOrCreateDefaultBattleActor(struct BattleContext *context,
                                                  void *unit)
{
    struct ActorSearch search;
    struct BattleActor *actor;
    search.unit = unit;
    search.found = 0;
    /* The retail callback reads only unit and found; word4 is unaccessed. */
    WalkActorList(context->default_actors, (void *)0x0809ab5d, &search);
    actor = search.found;
    if (actor == 0) {
        actor = CreateBattleActor(context, unit);
        AppendActorToList(context->default_actors, actor);
        IndexActorInList(context->default_actors, actor, actor->index_key);
    }
    return actor;
}
