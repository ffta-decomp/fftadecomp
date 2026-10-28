#include "turn_selection.h"

struct TurnWorkspaceTables { u8 fields_before_nodes[0xd6c]; volatile u32 nodes[26]; volatile u32 values[18]; };

typedef void (*TurnCopyBytes)(void *destination, const void *source, u32 size);

void *ProcessSelectedBattleTurnRecords_0809F850(const void *setup)
{
    u8 *state = AllocateBattleRecordBlock(0xe1c);
    s32 selected;
    s32 index;
    void *result;
    InitializeBattleTurnState(state, setup);
    selected = RunBattleTurnManager(state);
    index = 0;
    if (index < (s32)TURN_WORD(state, 0)) {
        TurnCopyBytes volatile *copy_cell = (TurnCopyBytes volatile *)0x0836d4bc;
        u8 *source = state + 4;
        do {
            s32 byte_offset = index * 4;
            volatile u32 *slot = ((struct TurnWorkspaceTables *)state)->nodes;
            u8 *node;
            void *destination;
            slot = (volatile u32 *)((u8 *)slot + byte_offset);
            destination = (void *)TURN_WORD((void *)*slot, 0);
            (*copy_cell)(destination, source, 264);
            /* The opaque copy may replace the slot and alter the live count. */
            node = (u8 *)*slot;
            TURN_WORD(node, 40) = ((struct TurnWorkspaceTables *)state)->values[index];
            source += 264;
            ++index;
        } while (index < (s32)TURN_WORD(state, 0));
    }
    result = (void *)((struct TurnWorkspaceTables *)state)->nodes[selected];
    ReleaseBattleObject(state);
    return result;
}
