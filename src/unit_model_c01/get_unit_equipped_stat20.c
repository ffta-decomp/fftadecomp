#include "get_unit_equipped_stat20_exact_types.h"
s32 GetUnitEquippedStat20(UnitStatView *unit,u8 include_equipment)
{
 s16 value = unit->base_stat;
 s32 result;
 if (include_equipment != 0) {
  u32 bonus = 0;
  u16 *equipment = unit->equipment;
  s32 remaining = 4;
  do {
   u32 item = *equipment;
   if (item != 0)
    bonus += ItemProperty(item,10);
   equipment++;
   remaining--;
  } while (remaining >= 0);
  {
   s32 signed_base = value;
   u32 total = (u32)signed_base + bonus;
   value = total;
  }
 }
 result = (s16)value;
 if (result > 999)
  result = 999;
 return result;
}
