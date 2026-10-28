typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct ActorUnit {
    u8 unknown_00[40];
    u16 flags;
    u8 unknown_42[206];
    u8 direction;
    u8 unknown_249[2];
    u8 actor_index;
};
struct BattleContext;
struct BattleActor {
    struct ActorUnit *unit;
    u8 unknown_04[28];
    u8 direction;
    u8 unknown_33[3];
    u32 index_key;
    u8 unknown_40[16];
    u16 state;
    u16 unknown_58;
    void *shared_resource;
    u8 unknown_64[64];
    struct BattleContext *owner;
};
struct BattleContext {
    void *pool;
    u8 unknown_04[12];
    void *primary_actors;
    u8 unknown_20[8];
    void *shared_resource;
};
struct ActorSearch { struct ActorUnit *unit; u32 unaccessed_word; struct BattleActor *found; };

extern void WalkActorList(void *, void *, struct ActorSearch *);
extern void *AllocateActorStorage(void *, u32);
extern void ClearActorStorage(void *, u32, void *);
extern u32 ChooseActorIndex(struct BattleContext *);
extern void AppendActorToList(void *, struct BattleActor *);
extern void IndexActorInList(void *, struct BattleActor *, u32);
asm(".global WalkActorList\n.thumb_set WalkActorList,0x080c7cc1\n"
    ".global AllocateActorStorage\n.thumb_set AllocateActorStorage,0x08007139\n"
    ".global ClearActorStorage\n.thumb_set ClearActorStorage,0x0814224d\n"
    ".global ChooseActorIndex\n.thumb_set ChooseActorIndex,0x08099cb9\n"
    ".global AppendActorToList\n.thumb_set AppendActorToList,0x080c7a75\n"
    ".global IndexActorInList\n.thumb_set IndexActorInList,0x080c7ab5");

struct BattleActor *FindOrCreatePrimaryBattleActor(struct BattleContext *context,
                                                  struct ActorUnit *unit)
{
    struct ActorSearch search;
    struct BattleActor *actor;
    search.unit = unit;
    search.found = 0;
    WalkActorList(context->primary_actors, (void *)0x0809ab5d, &search);
    actor = search.found;
    if (actor == 0) {
        u32 association_flag;
        actor = AllocateActorStorage(context->pool, 132);
        ClearActorStorage(actor, 132, *(void **)0x0836d4b8);
        actor->unit = unit;
        actor->index_key = ChooseActorIndex(context);
        actor->unit->actor_index = actor->index_key;
        actor->owner = context;
        actor->shared_resource = context->shared_resource;
        association_flag = actor->state = 1;
        AppendActorToList(context->primary_actors, actor);
        IndexActorInList(context->primary_actors, actor, actor->index_key);
        unit->flags |= association_flag;
        actor->direction = unit->direction;
    }
    return actor;
}
