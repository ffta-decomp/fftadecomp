typedef unsigned char u8;
struct BattleNodeObjectPair {
    u8 unaccessed_prefix[84];
    void *primary_object;
    void *secondary_object;
};
typedef void (*BattleObjectUnaryOperation)(void *object);
extern BattleObjectUnaryOperation gBattleObjectUnaryOperation;
/* Route completion requests this operation; its engine-internal effect is opaque. */
void ApplyBattleNodeObjectOperation(struct BattleNodeObjectPair *node)
{
    void *object = node->primary_object;
    if (object != 0)
        gBattleObjectUnaryOperation(object);
    object = node->secondary_object;
    if (object != 0)
        gBattleObjectUnaryOperation(object);
}
asm(".global gBattleObjectUnaryOperation\n.set gBattleObjectUnaryOperation,0x0839403C\n"
    ".global _call_via_r1\n.thumb_set _call_via_r1,0x08142249\n");
