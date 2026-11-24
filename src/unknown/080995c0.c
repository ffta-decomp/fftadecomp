typedef unsigned char u8;

struct ActorOwner { void *pool; };
struct ContentActor {
    void *unit;
    u8 unknown_04[60];
    void *resource_64;
    void *attachment_68;
    void *attachment_72;
    u8 unknown_76[8];
    void *resource_84;
    void *resource_88;
    u8 unknown_92[36];
    struct ActorOwner *owner;
};

extern void BeginActorDisposal(struct ContentActor *actor);
extern void ReleaseActorPendingData(struct ContentActor *actor);
extern void DetachActorResource(void *resource, void *attachment);
extern void DestroyActorResource(void *resource);
extern void ReleaseActorVisual(void *resource);
extern void FreeActorStorage(void *pool, void *allocation);

asm(".global BeginActorDisposal\n.thumb_set BeginActorDisposal,0x080971f9\n"
    ".global ReleaseActorPendingData\n.thumb_set ReleaseActorPendingData,0x0809a09d\n"
    ".global DetachActorResource\n.thumb_set DetachActorResource,0x08021bd5\n"
    ".global DestroyActorResource\n.thumb_set DestroyActorResource,0x08021b55\n"
    ".global ReleaseActorVisual\n.thumb_set ReleaseActorVisual,0x0808f7cd\n"
    ".global FreeActorStorage\n.thumb_set FreeActorStorage,0x08007171");

/* Keep post-helper field reloads: disposal can mutate the actor's resources. */
void *DisposeBattleContentActor(struct ContentActor *actor)
{
    void *unit;
    BeginActorDisposal(actor);
    unit = actor->unit;
    ReleaseActorPendingData(actor);
    if (actor->resource_64 != 0) {
        if (actor->attachment_72 != 0)
            DetachActorResource(actor->resource_64, actor->attachment_72);
        if (actor->attachment_68 != 0)
            DetachActorResource(actor->resource_64, actor->attachment_68);
        DestroyActorResource(actor->resource_64);
    }
    if (actor->resource_84 != 0)
        ReleaseActorVisual(actor->resource_84);
    if (actor->resource_88 != 0)
        ReleaseActorVisual(actor->resource_88);
    FreeActorStorage(actor->owner->pool, actor);
    return unit;
}
