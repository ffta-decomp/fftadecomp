#include "interfaces.h"

/* The action resolver prepares this shared game-state object before row effects. */
void InitializeGlobalBattleActionState(u16 first_id, u16 second_id, u8 mode)
    asm("ActionDependency_0012F2A4");
void InitializeGlobalBattleActionState(u16 first_id, u16 second_id, u8 mode)
{
    InitializePreservedActionState(gBattleActionState, first_id, second_id, mode);
}
