#include "interfaces.h"
void InitializeFixedMissionItemChoices(void) __asm__("SceneTaskDependency_000CBC94");
void InitializeFixedMissionItemChoices(void)
{
    gFixedItemChoices.first_item = 4;
    gFixedItemChoices.second_item = 343;
    gFixedItemChoices.third_item = 292;
    gFixedItemChoices.fourth_item = 9;
    gFixedItemChoices.fifth_item = 125;
}
