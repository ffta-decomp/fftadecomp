#include "mission_progression.h"
extern u8 MissionProgressionRam[] __asm__("0x02002cb4");
#undef PROGRESSION_RECORDS
#define PROGRESSION_RECORDS MissionProgressionRam

/* Source-backed12-byte progression record; only status offset1 is read here. */
struct ProgressionRecord { u8 field00; u8 status; u8 fields02[10]; };

void UpdateMissionProgressionSlot(u32 raw_index)
{
    u32 index = (u8)raw_index;
    u8 *record = PROGRESSION_RECORDS + index * 12;
    const u8 *definition = PROGRESSION_DEFINITIONS + index * 38;
    u32 save_index = index + 20;
    s8 quantity_byte;
    u8 quantity;
    s32 slot;

    {
        u32 flags = record[1] & 247;
        u32 cleared = 0;
        record[1] = flags | 2;
        record[2] = cleared;
    }
    quantity_byte = definition[1];
    quantity = (u8)quantity_byte;
    quantity = (u8)(quantity + SignedModulo((s16)NextRandom15(), (u8)quantity_byte >> 1));
    if (quantity == 0) quantity = 1;
    WriteSaveByte((u16)save_index, quantity);
    for (slot = 1; slot <= 30; ++slot) {
        if ((((const struct ProgressionRecord *)PROGRESSION_RECORDS)[slot].status & 3) != 3) return;
    }
    SetGameFlag(0x59f, 1);
}
