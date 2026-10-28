#include "interfaces.h"
u32 ActionDependency_00130FBC(void)
{
 {
  EffectContext *prefix = (EffectContext*)0x0200f3f0;
  if (prefix->descriptor[0] != 28 &&
      (u8)InitialStateGate(prefix->target) != 0)
   return 0;
 }
 if ((u8)ChargeStateGate(BattleState.current.target) != 0)
  return 0;
 {
  EffectContext *current = &BattleState.current;
  u32 result;
  if (current->actor == 0 || current->target == 0)
   result = 0;
  else
   result = EffectPredicates[current->descriptor[0]](current);
  return (u8)result;
 }
}
