#ifndef BATTLE_ELIGIBLE_UNIT_ED_INTERFACES_H
#define BATTLE_ELIGIBLE_UNIT_ED_INTERFACES_H
typedef unsigned char u8;
typedef unsigned int u32;
struct BattleUnit;
struct UnitCategoryView;
struct BattleNode { struct BattleUnit *unit; };
extern struct BattleNode *FindLowestEligibleUnitRecord(u32,const struct UnitCategoryView *);
extern void SetUnitStateEDBit3(struct BattleUnit *,u8 enabled);
__asm__(
".global FindLowestEligibleUnitRecord\n.thumb_set FindLowestEligibleUnitRecord,0x080970E9\n"
".global SetUnitStateEDBit3\n.thumb_set SetUnitStateEDBit3,0x080CE2F1\n");
#endif


/* Materialize the observed full target argument before ordinary call setup.
 * This is the original fresh load, not a persistent snapshot. */
static __inline__ struct UnitCategoryView *ReadCurrentTargetForSelection(
    struct UnitCategoryView **target_ref)
{
    register struct UnitCategoryView *current_target asm("r1") = *target_ref;
    asm("" : : "r"(current_target));
    return current_target;
}

/* The referenced target is freshly loaded for each selection after any unit
 * mutation, matching the original alias-visible load/call sequence. */
void ClearEligibleUnitsStateEDBit3(u32 selector,struct UnitCategoryView **target_ref)
{
    register u32 saved_selector asm("r5") = selector;
    register struct UnitCategoryView **saved_target_ref asm("r4");
    struct BattleNode *node;
    asm("" : "+r"(saved_selector));
    saved_target_ref = target_ref;
    asm("" : "+r"(saved_target_ref));
    while ((node = FindLowestEligibleUnitRecord(saved_selector,ReadCurrentTargetForSelection(saved_target_ref))) != 0)
        SetUnitStateEDBit3(node->unit,0);
}
