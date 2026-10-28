#ifndef WORKER2_DE210_COMMAND_ABI_H
#define WORKER2_DE210_COMMAND_ABI_H
typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
/* Accessed prefix only; no full actor producer-size assertion. */
typedef struct BattleActionActor {
    u8 unknown_00[31];
    s8 direction;
} BattleActionActor;
extern void QueueActorAction(BattleActionActor *, u16, s8, u16);
#endif


/* Keep the actor owner; its direction contents are reread after mode10. */
void SequenceBattleActorDirection(BattleActionActor *actor, s8 direction)
    __asm__("RemainingBand43_000DE210");
void SequenceBattleActorDirection(BattleActionActor *actor, s8 direction)
{
    QueueActorAction(actor, 10, direction, 0);
    QueueActorAction(actor, 9, actor->direction, 0);
}
__asm__(".global QueueActorAction\n.thumb_set QueueActorAction,0x0809836d\n");
