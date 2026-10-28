#include "interfaces.h"

/* Each nonzero item requirement is searched independently after its property read. */
u32 IsMissionRequirementStateSatisfied(u16 mission)
{
    u16 requirement;
    int ordinal;
    u32 progress;

    requirement = (u16)ReadMissionRequirementProperty(mission, 42);
    if (requirement != 0) {
        for (ordinal = 0; ordinal < 64; ++ordinal) {
            if (gRequirementItems.items[ordinal].item_id == requirement)
                break;
        }
        if (ordinal == 64)
            return 0;
    }
    requirement = (u16)ReadMissionRequirementProperty(mission, 44);
    if (requirement != 0) {
        for (ordinal = 0; ordinal < 64; ++ordinal) {
            if (gRequirementItems.items[ordinal].item_id == requirement)
                break;
        }
        if (ordinal == 64)
            return 0;
    }
    requirement = (u16)ReadMissionRequirementProperty(mission, 46);
    if (requirement != 0) {
        /* This byte is captured before the threshold helper is called. */
        progress = gRequirementProgress.progress[requirement].count;
        if (progress < ReadMissionRequirementProperty(mission, 47))
            return 0;
    }
    return 1;
}
