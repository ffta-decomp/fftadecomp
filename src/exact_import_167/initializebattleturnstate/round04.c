#include "interfaces.h"
void InitializeSortedTurnUnits(struct TurnContext *turn,const void *roster)
    __asm__("InitializeBattleTurnState");
void InitializeSortedTurnUnits(struct TurnContext *turn,const void *roster)
{
    s32 outer_index;
    s32 inner_index;
    gTurnContextClear((u8 *)turn,0xe1c);
    ((struct TurnRosterView *)turn)->roster = roster;
    turn->count = CollectTurnUnitRecords(roster,turn->records);
    for (outer_index = 0; outer_index < turn->count - 1; outer_index++) {
        for (inner_index = outer_index + 1; inner_index < turn->count; inner_index++) {
            struct TurnUnitRecord *left = turn->records[outer_index];
            const u8 *left_tag = &left->unit->ordering_tag;
            struct TurnUnitRecord *right = turn->records[inner_index];
            if (*left_tag > right->unit->ordering_tag) {
                turn->records[outer_index] = right;
                turn->records[inner_index] = left;
            }
        }
    }
    for (outer_index = 0; outer_index < turn->count; outer_index++) {
        gTurnUnitCopy((u8 *)&turn->units[outer_index],
            (const u8 *)turn->records[outer_index]->unit,264);
    }
}
