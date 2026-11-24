#include "story/entities/interfaces/08124850_bindings.h"
void FilterSceneEntitiesForTransition_08124850(u8 selector)
{
    u32 records[13];
    s32 count,index;
    u8 *record,*unit;
    count=(s32)CountBattleUnitRecords(GetSceneActionContextBase(),records);
    for(index=0;index<count;index++) {
        record=(u8 *)records[index];
        unit=(u8 *)WORD(record);
        if((u8)EntityHelper_080C8280(unit)) continue;
        if((u16)UnsignedDivide(HALF(unit+26),10)>=HALF(unit+24)) continue;
        if((u8)EntityHelper_080CD92C(unit)) continue;
        if((u8)EntityHelper_080CDADC(unit)) continue;
        if((u8)EntityHelper_080CDA04(unit)) continue;
        if((u8)EntityHelper_080CDB24(unit)) continue;
        {
            /* One original byte snapshot feeds separate fullword equality
             * branches; an OR expression folds 49/50 into a range test. */
            u32 unit_kind = unit[7];
            if (unit_kind == 49) continue;
            if (unit_kind == 50) continue;
            if (unit_kind == 69) continue;
            if (unit_kind == 70) continue;
            if (unit_kind == 71) continue;
        }
        if(unit[4]==30 || unit[4]==57 || unit[4]==58 || unit[4]==59 || unit[4]==60 || unit[4]==61 || unit[4]==62 || unit[4]==63) continue;
        /* The filter snapshot is retained, but selector predicates reload record->unit. */
        switch(selector) {
        case 0:
            if((u8)EntityHelper_080C8240((void *)WORD(record))) continue;
            if((u8)EntityHelper_080C8260((void *)WORD(record))) continue;
            if((u8)EntityHelper_080C8298((void *)WORD(record))) continue;
            break;
        case 1:
            if(!(u8)EntityHelper_080C8240((void *)WORD(record))) continue;
            break;
        case 2:
            if(!(u8)EntityHelper_080C8260((void *)WORD(record))) continue;
            break;
        default:
            goto apply_default_mask;
        }
        /* Selected modes fall through to the first original effect site. */
        ApplySceneEntityStateMasks(record,2,0);
        continue;
apply_default_mask:
        ApplySceneEntityStateMasks(record,2,0);
    }
}
