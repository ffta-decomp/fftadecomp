#include "update_unit_derived_bytes_exact_types.h"
void UpdateUnitDerivedBytes(Unit *unit)
{
 DerivedBytes *derived;
 u8 first=UnitProperty(unit,34);
 u8 second=UnitProperty(unit,35);
 u8 third=UnitProperty(unit,31);
 if ((u8)StateGate(unit)!=0 && first!=1) first=1;
 switch (unit->mode) {
 case 2: ++third; break;
 case 3: third+=2; break;
 case 4: second=5; break;
 case 5: if ((u8)(second-1)<=1) second=3; break;
 case 6: first=3; break;
 }
 third+=EquipmentValue(unit,17);
 derived=&unit->derived;
 derived->first=first;
 derived->second=second;
 derived->third=third;
 derived->complement=~third;
}
