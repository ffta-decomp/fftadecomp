typedef unsigned char u8;
typedef unsigned int u32;
struct Unit;
struct Actor;
/* List role at 0x18 remains tentative; identity predicate is established. */
struct BattleContext {u8 unknown_00[24];void *actor_list_at18;};
struct ActorSearch {struct Unit *unit;u32 unaccessed_word;struct Actor *found;};
extern void WalkActorList(void *,void *,struct ActorSearch *);
struct Actor *FindActorInContextList18(struct BattleContext *context,struct Unit *unit)
{
    struct ActorSearch search;
    search.unit=unit;
    search.found=0;
    WalkActorList(context->actor_list_at18,(void *)0x0809ab5d,&search);
    return search.found;
}
__asm__(".global ResolveContentSelectionAt18\n.thumb_set ResolveContentSelectionAt18, FindActorInContextList18\n.global WalkActorList\n.thumb_set WalkActorList, 0x080c7cc1");
