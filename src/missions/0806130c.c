/* Method-local interface declarations from the frozen build. */
#include "ffta/unsigned_types.h"
extern u8 GetGameFlag(u16 flag);
extern void SetGameFlag(u16 flag, u16 value);


/* A nonzero definition byte selects a progression flag in bank0x500. */
void UnlockDefinitionProgressFlag(const u8 *definition)
{
    u16 flag;

    if (definition == 0 || definition[0] == 0)
        return;
    flag = definition[0] | 0x500;
    if (!GetGameFlag(flag)) {
        SetGameFlag(flag, 1);
        if (flag == 0x537)
            SetGameFlag(0x582, 1);
    }
}
