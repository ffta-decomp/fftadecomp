#ifndef WORKER2_DE168_BATTLE_COMMAND_ABI_H
#define WORKER2_DE168_BATTLE_COMMAND_ABI_H
typedef unsigned short u16;
typedef signed char s8;
/* Selected actor-action engine keeps its original body and four-argument ABI. */
extern void QueueActorAction(void *actor, u16 mode, s8 direction, u16 options);
#endif


/* DD900/DD9AC command-record consumers supply mode/options before direction.
 * Native DE168 narrows each at its original interface and swaps call positions.
 * POP R0/BX R0 restores LR, so no incidental helper result is returned. */
void QueueBattleActorCommandWithOptions(void *actor, u16 mode, u16 options,
                                        s8 direction)
    __asm__("RemainingBand43_000DE168");
void QueueBattleActorCommandWithOptions(void *actor, u16 mode, u16 options,
                                        s8 direction)
{
    QueueActorAction(actor, mode, direction, options);
}
__asm__(".global QueueActorAction\n.thumb_set QueueActorAction,0x0809836d\n");
