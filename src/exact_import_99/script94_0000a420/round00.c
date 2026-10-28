#include "interfaces.h"
/* Opcode11: branch on the sum of actor-unit battle counters.
 * The dispatcher separately adds this descriptor's four-byte length. */
void Script94_0000A420(struct NestedScript *script,const u8 *command)
{
    struct Actor *actors[13];
    int sum=0;
    int count=NCollectActors(NActorContext(),actors);
    int index;
    for(index=0;index<count;index++) {
        struct Actor *actor=actors[index];
        if (!(u8)NUnitHasStatusBit12(actor->unit)) sum+=actor->unit->counter;
    }
    if(command[1]==sum) script->pc+=command[2] | (command[3]<<8);
}
