#include "interfaces.h"
u32 IsMissionDefinitionRestricted(const struct MissionIdentity *mission) __asm__("CoreFrontier_000D2E78");
u32 IsMissionDefinitionRestricted(const struct MissionIdentity *mission)
{
    const struct MissionDefinition *definition = &gMissionDefinitions[mission->mission_id];
    if (definition->restriction_flags & 4)
        return 1;
    return 0;
}
