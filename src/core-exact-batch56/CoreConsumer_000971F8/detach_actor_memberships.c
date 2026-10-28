typedef unsigned char u8;
struct ActorOwner {
    u8 unknown_00[16];
    void *primary_actors;
    void *default_actors;
    void *alternate_actors;
};
struct ContentActor { u8 unknown_00[128]; struct ActorOwner *owner; };
extern void *FindActorListSlot(void *list, struct ContentActor *actor);
extern void RemoveActorListSlot(void *list, void *slot);
extern void *FindActorIndexSlot(void *list, struct ContentActor *actor);
extern void RemoveActorIndexSlot(void *list, void *slot);
asm(".global FindActorListSlot\n.thumb_set FindActorListSlot,0x080c7bf5\n"
    ".global RemoveActorListSlot\n.thumb_set RemoveActorListSlot,0x080c7a35\n"
    ".global FindActorIndexSlot\n.thumb_set FindActorIndexSlot,0x080c7c15\n"
    ".global RemoveActorIndexSlot\n.thumb_set RemoveActorIndexSlot,0x080c7a5d");

void DetachBattleActorMemberships(struct ContentActor *actor)
{
    struct ActorOwner **owner = &actor->owner;
    void *slot;
    /* Helpers can replace the owner or list; reload each at its original site. */
    slot = FindActorListSlot((*owner)->primary_actors, actor);
    if (slot != 0)
        RemoveActorListSlot((*owner)->primary_actors, slot);
    slot = FindActorIndexSlot((*owner)->primary_actors, actor);
    if (slot != 0)
        RemoveActorIndexSlot((*owner)->primary_actors, slot);
    slot = FindActorListSlot((*owner)->default_actors, actor);
    if (slot != 0)
        RemoveActorListSlot((*owner)->default_actors, slot);
    slot = FindActorIndexSlot((*owner)->default_actors, actor);
    if (slot != 0)
        RemoveActorIndexSlot((*owner)->default_actors, slot);
    slot = FindActorListSlot((*owner)->alternate_actors, actor);
    if (slot != 0)
        RemoveActorListSlot((*owner)->alternate_actors, slot);
    slot = FindActorIndexSlot((*owner)->alternate_actors, actor);
    if (slot != 0)
        RemoveActorIndexSlot((*owner)->alternate_actors, slot);
}
