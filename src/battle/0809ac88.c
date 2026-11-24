typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
struct PendingBattleActor { u8 unknown_00[116]; s8 pending_code; };
u32 MarkPendingBattleActor(struct PendingBattleActor *actor, u32 *pending)
{
    int result;
    result = actor->pending_code;
    if (result != 0) {
        result = 1;
        *pending = result;
        /* Native jumps over the other branch's redundant assignment of 1.
         * Both paths already return 1; B preserves every register and NZCV. */
        asm volatile ("b .L_actor_gate_return_0809ac88" : : "r" (result));
    } else {
        result = 1;
    }
    /* The instruction-free join preserves the already defined return value. */
    asm volatile (".L_actor_gate_return_0809ac88:" : "+r" (result));
    return result;
}
