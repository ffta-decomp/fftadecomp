#include "interfaces.h"
u32 EffectAuxiliary_00130E48(EffectContext *context)
{
 if ((u8)InitialGate(context) == 0)
  goto rejected;
 if ((u8)UnitStateGate(context->target) != 0)
  goto rejected;
 switch (context->selector) {
 case 189:
  if (UnitProperty(context->target,3) != 6)
   goto rejected;
  return 1;
 case 190:
  if (UnitProperty(context->target,3) != 7)
   goto rejected;
  return 1;
 case 191:
  if (UnitProperty(context->target,3) != 8)
   goto rejected;
  return 1;
 case 192:
  if (UnitProperty(context->target,3) != 9)
   goto rejected;
  return 1;
 case 193:
  if (UnitProperty(context->target,3) != 10)
   goto rejected;
  return 1;
 case 194:
  if (UnitProperty(context->target,3) != 11)
   goto rejected;
  return 1;
 case 195:
  if (UnitProperty(context->target,3) != 13)
   goto rejected;
  return 1;
 case 196:
  if (UnitProperty(context->target,3) != 14)
   goto rejected;
  return 1;
 case 197:
  if (UnitProperty(context->target,3) != 15)
   goto rejected;
  return 1;
 case 198:
  if (UnitProperty(context->target,3) != 16)
   goto rejected;
  return 1;
 case 199:
  if (UnitProperty(context->target,3) != 17)
   goto rejected;
  return 1;
 case 200:
  if (UnitProperty(context->target,3) != 18)
   goto rejected;
  return 1;
 case 201:
  if (UnitProperty(context->target,3) != 12)
   goto rejected;
  return 1;
 default:
  goto rejected;
 }
rejected:
 return 0;
}
