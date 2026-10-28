#include "contract.h"
/* Game-owned continuation queue; count wrapping does not establish capacity. */
void IsolatedCore57_0000A210(void *unused_context, const u8 *command)
{
    u8 previous_count = gSave.choice_count++;
    gSave.choices[previous_count] = command[1] | (command[2] << 8);
}
