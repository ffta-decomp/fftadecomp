#include "interfaces.h"
struct BattleResultList *CoreFrontier_000A89D8(struct BattleResultList *list,u32 selector,u8 *changed)
{
    struct BattleResultList *selected=(struct BattleResultList *)0x0200f8c0;
    u8 *count;
    u8 enabled;
    if (list!=0)
        selected=list;
    enabled=RetailCall_080a6f20(selector);
    count=&selected->count;
    if ((u8)enabled) {
        u32 previous=(u8)GetGameFlag(66);
        u32 one=1;
        SetGameFlag(66,previous^one);
        *changed=one;
        if ((u8)RetailCall_080a780c((u8 *)selected+*count*12,0,0,3))
            (*count)++;
        /* Explicit ABI setup order, then the original flag-restoration call.
         * Call-clobbers and memory effects are those of this actual helper. */
        __asm__ volatile ("add r1, %0, #0\n\tmov r0, #66\n\tbl SetGameFlag"
                          : : "r" (previous)
                          : "r0", "r1", "r2", "r3", "r12", "lr", "cc", "memory");
    }
    if (!*count)
        return 0;
    return selected;
}
