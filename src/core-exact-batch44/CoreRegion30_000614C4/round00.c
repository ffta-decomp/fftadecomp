typedef unsigned int u32;
typedef struct MissionRecord MissionRecord;
typedef struct Unit Unit;
extern MissionRecord *CurrentMission __asm__("0x020020d0");
extern u32 RetailCall_080cf310(MissionRecord *,Unit *,unsigned char);
u32 GetMissionOutcomeDispatchValue(Unit *unit) __asm__("CoreRegion30_000614C4");
u32 GetMissionOutcomeDispatchValue(Unit *unit)
{
    u32 dispatch_value=0;
    switch(RetailCall_080cf310(CurrentMission,unit,0)) {
    case 1:
    case 2:
        dispatch_value=24;
        break;
    case 3:
    case 4:
        dispatch_value=0;
        break;
    case 0:
    case 5:
        dispatch_value=12;
        break;
    }
    return dispatch_value;
}
asm(".global RetailCall_080cf310\n.thumb_set RetailCall_080cf310,0x080cf311\n");
