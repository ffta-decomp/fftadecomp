#include "interfaces.h"
void RefreshConstrainedMissionItemChoices(void) __asm__("SceneTaskDependency_000CC788");
void RefreshConstrainedMissionItemChoices(void)
{
    u8 slot = 0;
    const struct ItemChoiceDefinition *definitions = gRandomChoiceDefinitions;
    u16 *choices = gRandomMissionItemChoices;
    for (; slot <= 4;) {
        u32 choice_byte_offset = slot * sizeof(*choices);
        u32 next_slot = slot + 1;
        u16 *destination = (u16 *)(choice_byte_offset + (u32)choices);
        u16 item_id;
        do {
            item_id = MissionItemSignedRemainder((s16)NextRandom15(), 376);
        } while (!definitions[item_id].enabled);
        *destination = item_id;
        slot = next_slot;
    }
}
