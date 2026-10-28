#include "interfaces.h"

u32 ClassifyMissionSpecialOperandPair(const struct MissionOperandView *record)
    __asm__("CoreRegion_00045484");
u32 ClassifyMissionSpecialOperandPair(const struct MissionOperandView *record)
{
    if (record->operand_a == 96 || record->operand_b == 96)
        return 2;
    if (record->operand_a == 95 || record->operand_b == 95)
        return 1;
    return 0;
}
