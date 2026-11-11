#ifndef WORKER2_BATTLE_ACTOR_SEARCH_H
#define WORKER2_BATTLE_ACTOR_SEARCH_H
typedef unsigned char u8;
typedef unsigned int u32;
struct LinkedNode;
struct ListOwner;
typedef u32 (*ActorNodeVisitor)(struct LinkedNode *,void *);
struct BattleActorContext20 {u8 unknown0[20];struct ListOwner *actors;};
struct ActorSearch {void *unit;u32 unaccessed_word;void *found;};
typedef char search12[(sizeof(struct ActorSearch)==12)?1:-1];
extern void VisitBattleActorList(const struct ListOwner *,ActorNodeVisitor,void *);
#endif

/* Actual full-unit-identity visitor and node payload implementation retained. */
void *FindContext20BattleActor(struct BattleActorContext20 *context,void *unit)
 __asm__("ResolveContentSelectionAt14");
void *FindContext20BattleActor(struct BattleActorContext20 *context,void *unit)
{
 struct ActorSearch search;
 search.unit=unit;
 search.found=0;
 VisitBattleActorList(context->actors,(ActorNodeVisitor)0x0809ab5d,&search);
 return search.found;
}
__asm__(".global VisitBattleActorList\n.thumb_set VisitBattleActorList,0x080c7cc1\n");
