#include "interfaces.h"
u16 SelectRandomMissionRewardItem(void) __asm__("CoreDependency29_000D2114");
u16 SelectRandomMissionRewardItem(void)
{
    u16 progression = gRewardProgressState.progression;
    u32 mask = 144;
    s32 eligible_count;
    s32 item_id;
    if (progression > 10) {
        mask = 192;
        if (progression <= 20)
            mask = 160;
    }
    eligible_count = 0;
    for (item_id = 1; item_id <= 375; item_id++) {
        if (gRewardItemDefinitions[item_id].reward_flags & mask)
            eligible_count++;
    }
    if (!eligible_count)
        return 0;
    {
        s32 ordinal = RewardSignedRemainder((s16)NextRandom15(), eligible_count);
        for (item_id = 1; item_id <= 375; item_id++) {
            if (gRewardItemDefinitions[item_id].reward_flags & mask) {
                if (!ordinal)
                    return item_id;
                ordinal--;
            }
        }
    }
    return 0;
}
