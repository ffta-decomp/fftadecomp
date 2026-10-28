typedef unsigned char u8;
typedef unsigned int u32;
struct BattleNodeEffectPair {
    u8 unaccessed_prefix[84];
    void *primary_object;
    void *secondary_object;
};
typedef void (*BattleObjectEffect)(void *object, u32 state);
extern BattleObjectEffect gBattleObjectEffect;
void SetBattleNodeEffectState(struct BattleNodeEffectPair *node, u8 state)
{
    void *object = node->primary_object;
    if (object != 0)
        gBattleObjectEffect(object, state);
    {
        void *secondary_object = node->secondary_object;
        if (secondary_object != 0)
            gBattleObjectEffect(secondary_object, state);
    }
}
asm(".global gBattleObjectEffect\n.set gBattleObjectEffect,0x08394054\n"
    ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224D\n");
