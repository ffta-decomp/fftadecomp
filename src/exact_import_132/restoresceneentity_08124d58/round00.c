#include "interfaces.h"
static inline struct Unit *SelectRestoreUnit(u8 selector)
{
    if(selector==255) {
        struct Unit *unit=(struct Unit*)0x02000080;
        int index;
        for(index=0;index<24;++index,++unit) if(unit->flags40&1024) return unit;
        return 0;
    }
    if((s8)selector<0) return ResolveSceneUnitByEncodedId(selector);
    return FindUnitPoolRecordById(selector);
}
void RestoreSceneEntity_08124D58(u8 selector)
{
    struct Unit *unit=SelectRestoreUnit(selector);
    struct Entity *entity;
    unit->value24=unit->saved26;
    unit->value28=unit->saved30;
    ClearRange((u8*)unit+232,8);
    ClearRange((u8*)unit+216,16);
    entity=FindSceneEntityForUnitRecord(GetSceneActionContextBase(),unit);
    entity->flags48=0;
    entity->flags40=0;
    PlacementHelper_0809A304(entity);
    PlacementHelper_08124710(entity,1,entity->identity);
}
