typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct BattlePhaseSequence {
    u8 unknown0[4];
    u16 phase;
    u16 count;
    u16 queue[34];
};
typedef void (*ClearMemory)(void *, u32);
__asm__(".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
typedef char size_check[sizeof(struct BattlePhaseSequence)==76?1:-1];
/* Keep the seven original store/postincrement pairs distinct. */
void InitializeBattlePhaseSequence(struct BattlePhaseSequence *state)
{
    (*(const ClearMemory *)0x0836d4b8)(state, 76);
    state->phase = 0;
    state->queue[state->count++] = 0;
    state->phase = 8;
    state->queue[state->count++] = 8;
    state->phase = 11;
    state->queue[state->count++] = 11;
    state->phase = 10;
    state->queue[state->count++] = 10;
    state->phase = 5;
    state->queue[state->count++] = 5;
    state->phase = 7;
    state->queue[state->count++] = 7;
    state->phase = 6;
    state->queue[state->count++] = 6;
    state->phase = 3;
}
