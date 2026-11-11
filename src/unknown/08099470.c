#ifndef BATTLE_ELIGIBLE_UNIT_FLAG_INTERFACES_H
#define BATTLE_ELIGIBLE_UNIT_FLAG_INTERFACES_H
typedef unsigned char u8;
struct BattleContext;
struct BattleUnit;
struct BattleNode { struct BattleUnit *unit; };
extern struct BattleNode *SelectEligibleContextListNode(const struct BattleContext *,struct BattleUnit **);
extern void SetUnitStateEABit3(struct BattleUnit *,u8 enabled);
__asm__(
".global SelectEligibleContextListNode\n.thumb_set SelectEligibleContextListNode,0x08099495\n"
".global SetUnitStateEABit3\n.thumb_set SetUnitStateEABit3,0x080CE1B1\n");
#endif


/* Selection consumes the existing context and referenced unit; each returned
 * node supplies the unit whose EA bit3 is cleared before selecting again. */
void ClearEligibleUnitsStateEABit3(const struct BattleContext *context,
                                  struct BattleUnit **selected_unit)
{
    register const struct BattleContext *saved_context asm("r5") = context;
    register struct BattleUnit **saved_selection asm("r4");
    struct BattleNode *node;
    asm("" : "+r"(saved_context));
    saved_selection = selected_unit;
    asm("" : "+r"(saved_selection));
    while ((node = SelectEligibleContextListNode(saved_context,saved_selection)) != 0)
        SetUnitStateEABit3(node->unit,0);
}
