#include "../../../src/task_tree_core.h"
struct BattleOwnerObjectPair {
    u8 unknown_00[84];
    void *primary_object;
    void *secondary_object;
};
typedef void (*BattleObjectStateOperation)(void *, u32);
extern BattleObjectStateOperation gBattleObjectStateOperation;

u32 VisitBattleOwnerObjectState(u32 owner_word, void *argument)
{
    struct BattleOwnerObjectPair *owner = (struct BattleOwnerObjectPair *)owner_word;
    u8 state = (u32)argument;
    gBattleObjectStateOperation(owner->primary_object, state);
    gBattleObjectStateOperation(owner->secondary_object, state);
    return 1;
}
asm(".global gBattleObjectStateOperation\n.set gBattleObjectStateOperation,0x08394048\n"
    ".global _call_via_r2\n.thumb_set _call_via_r2,0x0814224d\n");
