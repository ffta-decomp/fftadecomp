typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;
struct BattleActor;
/* These call-site declarations retain the original full signed projection;
 * the existing implementations consume the low byte of direction. */
extern void ApplyExistingActorVisual(struct BattleActor *, u16, s32, u32);
extern void RefreshExistingActorValues(struct BattleActor *, u16, s32);
void UpdateBattleActorActionAutomatic(struct BattleActor *actor_argument,
                                      u32 value_argument, s32 direction_argument)
{
    /* The native entry captures all three full inputs before narrowing.
     * Each boundary consumes initialized snapshots, not ABI scratch.
     * Input-only operands retain known pointer equality and the value bound. */
    register struct BattleActor *actor __asm__("r6") = actor_argument;
    register u32 value __asm__("r5") = value_argument;
    register s32 direction __asm__("r4") = direction_argument;
    __asm__("" : "+r"(value), "+r"(direction) : "r"(actor));
    value = (u16)value;
    __asm__("" : "+r"(direction) : "r"(actor), "r"(value));
    direction = (s8)direction;
    ApplyExistingActorVisual(actor, value, direction, 1);
    {
        /* The original restores the actor in r0 before setting r1/r2. */
        register struct BattleActor *refresh_actor __asm__("r0") = actor;
        __asm__("" : "+r"(refresh_actor) : "r"(value), "r"(direction));
        RefreshExistingActorValues(refresh_actor, value, direction);
    }
}

asm(".global ApplyExistingActorVisual\n.thumb_set ApplyExistingActorVisual,0x080975dd\n"
    ".global RefreshExistingActorValues\n.thumb_set RefreshExistingActorValues,0x08097705\n");
