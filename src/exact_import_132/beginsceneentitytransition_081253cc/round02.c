#include "interfaces.h"

void BeginSceneEntityTransition_081253CC(void)
{
    u32 selector = gSceneContentSave.selector;
    const struct SceneContentDefinition *definition = &gSceneContentDefinitions[selector];
    if (definition->flags & 4) {
        struct Unit *unit = FindUnitPoolRecordById(2);
        void *context = GetContentConsumerContext();
        if (ResolveContentConsumerSelection(context, unit) != 0)
            SetUnitStateEDBit7(unit, 1);
    }
    UpdateSceneEntityActions(255);
    gSceneTransitionControl.state = 0;
    gSceneTransitionControl.flags = (gSceneTransitionControl.flags & 0xfffe) | 2;
    gSceneTransitionControl.mode = 0;
}
