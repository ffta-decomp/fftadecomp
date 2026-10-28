#include "interfaces.h"
u32 CoreContinuation_0012D07C(const struct UnitState *unit,u32 incoming_item,u32 action)
{
 const struct Item *item=&gItems[(u16)incoming_item];int index;
 for(index=0;index<3;++index) {
  if(!CheckActionRule(unit,item->rules[index],(u16)action))return 0;
 }
 return 1;
}
