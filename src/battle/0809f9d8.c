/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned int u32;
struct BattleActor { void *unit; u8 unknown04[36]; u32 state40; };
typedef char AssertActorState40[((u32)&((struct BattleActor *)0)->state40 == 40) ? 1 : -1];
extern u8 ActorEA7(const void *unit);
extern u8 ActorE83(const void *unit);
extern u8 ActorE91(const void *unit);
__asm__(".global ActorEA7\n.thumb_set ActorEA7, 0x080cdadd");
__asm__(".global ActorE83\n.thumb_set ActorE83, 0x080cd8e5");
__asm__(".global ActorE91\n.thumb_set ActorE91, 0x080cd975");

/* EA bit7 rejects first; remaining state checks retain their short-circuit order. */
u32 ActorHasPendingUnitState(struct BattleActor *actor)
{
    if ((u8)ActorEA7(actor->unit) != 0)
        goto reject;
    if ((actor->state40 & 1) != 0 ||
        (u8)ActorE83(actor->unit) != 0 ||
        (u8)ActorE91(actor->unit) != 0 ||
        actor->state40 != 0)
        goto accept;
reject:
    return 0;
accept:
    return 1;
}
