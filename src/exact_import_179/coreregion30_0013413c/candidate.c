#include "interfaces.h"
/* Supplies a candidate-retention chance input; its numerical scale is unproved. */
u32 GetBattleCandidateChance(const u8 *unit, u16 action_id)
    __asm__("CoreRegion30_0013413C");
u32 GetBattleCandidateChance(const u8 *unit, u16 action_id)
{
    u32 chance;
    if (action_id == 0) {
        u32 definition_offset = unit[5] * 52;
        const u8 *definition = definition_offset + (const u8 *)JobChanceDefinitions;
        chance = definition[50];
    } else {
        u32 definition_offset = action_id * 28;
        const u8 *definition = definition_offset + (const u8 *)AbilityChanceDefinitions;
        chance = definition[26];
    }
    return chance;
}
