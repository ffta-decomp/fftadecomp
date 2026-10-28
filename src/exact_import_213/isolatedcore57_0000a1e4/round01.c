#include "interfaces.h"

/* The dispatcher independently adds the five-byte command length. */
void IsolatedCore57_0000A1E4(BattleScriptCursor *context, const u8 *command)
{
    u16 flag_id = command[1] | (command[2] << 8);

    if ((u8)ReadGameFlag(flag_id)) {
        u16 delta = command[3] | (command[4] << 8);
        context->cursor += delta;
    }
}
