#include "turn_selection.h"

extern void *RetailCall_08096d7c(void);
extern u32 CollectBattleTurnUnitPointers_0809F78C(const void *, void **, u32);

void StoreBattleTurnOrderInContext_08027528(u8 *context)
{
    void *nodes[20];
    s32 index;
    CollectBattleTurnUnitPointers_0809F78C(RetailCall_08096d7c(), nodes, 20);
    for (index = 0; index < 20; ++index) {
        u32 *destination = (u32 *)TURN_WORD(context, 148);
        destination[index] = TURN_WORD(nodes[index], 0);
    }
}
