#include "interfaces.h"
u8 HasSavedCollectionForProgressId(u16 progress_id) __asm__("Source52_000268DC");
u8 HasSavedCollectionForProgressId(u16 progress_id)
{
    u8 group_slots[3];
    int group_index;
    group_slots[0] = group_slots[1] = group_slots[2] = -1;
    switch (progress_id) {
    case 202: group_slots[0] = 0; group_slots[1] = 1; break;
    case 203: group_slots[0] = 2; group_slots[1] = 3; group_slots[2] = 4; break;
    case 204: group_slots[0] = 5; group_slots[1] = 6; break;
    case 205: group_slots[0] = 7; group_slots[1] = 8; group_slots[2] = 9; break;
    case 206: group_slots[0] = 10; group_slots[1] = 11; break;
    case 207: group_slots[0] = 12; group_slots[1] = 13; break;
    case 208: group_slots[0] = 14; group_slots[1] = 15; break;
    case 209: group_slots[0] = 16; group_slots[1] = 17; break;
    case 210: group_slots[0] = 18; group_slots[1] = 19; break;
    }
    for (group_index = 0; group_index < 3; group_index++) {
        if (group_slots[group_index] == 255)
            return 0;
        if (gProgressCollectionRecords[group_slots[group_index]].presence_word)
            return 1;
    }
    return 0;
}
