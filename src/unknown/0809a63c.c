typedef unsigned char u8;
typedef unsigned int u32;
struct BattleNodeObjectPair {
    u8 unaccessed_prefix[84];
    void *primary_object;
    void *secondary_object;
};
typedef void (*BattleObjectStateOperation)(void *object, u32 state);
extern BattleObjectStateOperation gBattleObjectStateOperation;
void ApplyBattleNodeObjectState(struct BattleNodeObjectPair *node, u8 state)
{
    gBattleObjectStateOperation(node->primary_object, state);
    gBattleObjectStateOperation(node->secondary_object, state);
}
asm(".global gBattleObjectStateOperation\n.set gBattleObjectStateOperation,0x08394048\n"
    ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224D\n");
