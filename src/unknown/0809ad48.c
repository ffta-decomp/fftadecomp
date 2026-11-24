typedef unsigned char u8;
typedef unsigned short u16;
typedef struct Unit { u8 unknown[40]; u16 flags; } Unit;
typedef struct UnitNode { Unit *unit; } UnitNode;
typedef struct EligibilityCounter EligibilityCounter;
extern int RetailCall_08098bb0(UnitNode *,EligibilityCounter *);
int CountFlag14EligibleBattleActor(UnitNode *node,EligibilityCounter *counter) __asm__("CoreRegion30_0009AD48");
int CountFlag14EligibleBattleActor(UnitNode *node,EligibilityCounter *counter)
{
    int result;
    if (node->unit->flags&0x4000) result=RetailCall_08098bb0(node,counter);
    else result=1;
    return result;
}
asm(".global RetailCall_08098bb0\n.thumb_set RetailCall_08098bb0,0x08098bb1\n");
