#include "interfaces.h"
u32 BattleDependency_0012F0E4(const struct ActorRule *actor,u32 incoming_x,u32 incoming_y)
{
 u8 x=incoming_x,y=incoming_y;
 if((u8)QueryCellPayload(x,y)) {
  if(actor->candidate_mode!=2 || !(ReadCellFlags(x,y)&2))return 1;
 }
 return 0;
}
