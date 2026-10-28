#include "turn_selection.h"
struct CollectorTables { u8 before_nodes[0xd6c]; volatile u32 nodes[26]; };

u32 CollectBattleTurnUnitPointers_0809F78C(const void *setup,
                                         void **output, u32 requested_count)
{
    u16 saved_count = requested_count;
    u8 *state = AllocateBattleRecordBlock(0xe1c);
    s32 remaining;
    InitializeBattleTurnState(state, setup);
    remaining = (s16)saved_count;
    if (remaining > 0) {
      u16 cleared = 0;
      do {
        s32 selected = RunBattleTurnManager(state);
        u8 *clear_base = (u8 *)(selected * 264 + (u32)state);
        /* Retail clears relative to the object, not its inline array at +4. */
        TURN_HALF(clear_base, 216) = cleared;
        TURN_HALF(clear_base, 212) = cleared;
        *output++ = (void *)((struct CollectorTables *)state)->nodes[selected];
        --remaining;
      } while (remaining != 0);
    }
    ReleaseBattleObject(state);
    return 1;
}
