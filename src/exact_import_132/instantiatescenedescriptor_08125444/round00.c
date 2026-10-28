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
void InstantiateSceneDescriptor_08125444(const u8 *input)
{
    struct SpawnDescriptor spawn;
    struct Unit *reference;
    struct Entity *entity;
    int index;
    spawn.type=input[0];
    spawn.reference=input[1];
    spawn.x[0]=input[2];
    spawn.y[0]=input[3];
    spawn.x[1]=input[4];
    spawn.y[1]=input[5];
    spawn.x[2]=input[6];
    spawn.y[2]=input[7];
    spawn.x[3]=0;
    spawn.y[3]=0;
    for(index=0;index<3;++index) {
        if(RetailCall_08099644(GetSceneActionContextBase(),(signed char)spawn.x[index],(signed char)spawn.y[index])==0) {
            spawn.x[3]=spawn.x[index];
            spawn.y[3]=spawn.y[index];
            break;
        }
    }
    reference=SelectRestoreUnit(spawn.reference);
    entity=FindSceneEntityForUnitRecord(GetSceneActionContextBase(),reference);
    if(entity==0) spawn.reference=0;
    else spawn.reference=DetermineSceneFacing_08124ACC(spawn.x[3],spawn.y[3],((u8*)*(struct Unit**)entity)[246],((u8*)*(struct Unit**)entity)[247]);
    entity=PlacementHelper_081242A0(spawn.type,spawn.x[3],spawn.y[3],spawn.reference,0,0,2);
    entity->flags48|=1;
}
