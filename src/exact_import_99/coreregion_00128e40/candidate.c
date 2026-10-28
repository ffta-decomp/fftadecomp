#include "contract.h"

/* Shuffle occupied saved slots four times before applying the capped removal
 * count. The original uses a signed16 RNG operand for signed remainder. */
void CoreRegion_00128E40(u8 requested_count)
{
    u8 occupied_slots[20];
    s32 occupied_count;
    s32 slot;
    s32 pass;
    s32 random_slot;
    u8 previous;

    occupied_count = 0;
    for (slot = 0; slot <= 19; slot++) {
        if (gSaveData.slots[slot] != 0) {
            occupied_slots[occupied_count] = slot;
            occupied_count++;
        }
    }
    if (occupied_count != 0) {
        for (pass = 0; pass <= 3; pass++) {
            for (slot = 0; slot < occupied_count; slot++) {
                random_slot = SignedModulo((s16)NextRandom15(), occupied_count);
                if (random_slot != slot) {
                    previous = occupied_slots[slot];
                    occupied_slots[slot] = occupied_slots[random_slot];
                    occupied_slots[random_slot] = previous;
                }
            }
        }
        if (occupied_count < requested_count)
            requested_count = occupied_count;
        for (slot = 0; slot < requested_count; slot++)
            ClearSavedInventorySlot(occupied_slots[slot]);
        CompactPendingHalfwordRecords();
    }
}
