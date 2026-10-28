#include "predicate_02_exact_types.h"
u32 TestEffectEquipmentCategory(EffectContext *context)
{
 EffectUnit *unit;
 s32 slot;
 if ((u8)UnitField19IsZero(context->unit) == 0)
  goto scan;
 goto rejected;
accepted:
 return 1;
scan:
 unit = context->unit;
 slot = 0;
 do {
  u32 item = unit->equipment[slot];
  if (item != 0) {
   u8 category = (u8)ItemProperty(item,3);
   if ((u8)(category - 1) <= 8)
    goto accepted;
  }
  slot++;
 } while (slot <= 4);
rejected:
 return 0;
}
