typedef unsigned int u32;
struct BattleAuxiliaryState { unsigned char opaque[536]; };
typedef void (*MemoryClear)(void *, u32);
extern void *AllocateBattleAuxiliaryBytes(u32);
__asm__(".global AllocateBattleAuxiliaryBytes\n.thumb_set AllocateBattleAuxiliaryBytes,0x08022841\n.global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d");
/* Only allocation/publication/clearing are established for this object. */
void InitializeBattleAuxiliaryState(void)
{
    struct BattleAuxiliaryState **slot = (struct BattleAuxiliaryState **)0x020101f0;
    struct BattleAuxiliaryState *state = AllocateBattleAuxiliaryBytes(sizeof(struct BattleAuxiliaryState));
    *slot = state;
    (*(const MemoryClear *)0x0836d4b8)(state, sizeof(struct BattleAuxiliaryState));
}
