#include "interfaces.h"
/* Opcode8: a matching nonzero active mission applies the relative PC displacement.
 * The dispatcher still adds the descriptor's five-byte length afterward. */
void IsolatedCore57_0000A330(struct NestedScript *script,const u8 *command)
{
    if (gMissionData.active_mission && gMissionData.active_mission==(command[1] | (command[2]<<8)))
        script->pc+=command[3] | (command[4]<<8);
}
