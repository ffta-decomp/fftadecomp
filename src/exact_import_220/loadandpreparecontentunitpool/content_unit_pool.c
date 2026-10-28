#include "interfaces.h"

void LoadAndPrepareContentUnitPool(u16 bank_index, u32 receiver)
{
    const struct ContentUnitDefinitionBank *bank;
    struct ContentUnitRecord *record;
    struct PreparedUnitNode *node;
    int remaining;

    bank = &ContentUnitDefinitionBanks[bank_index];
    record = ContentUnitPool;
    LoadContentUnitRecords(bank, record, 12);
    remaining = 11;
    do {
        if (record->occupied != 0) {
            node = AppendContentUnit(receiver, record);
            node->unit->initial_x = node->unit->x;
            node->unit->initial_y = node->unit->y;
        }
        --remaining;
        ++record;
    } while (remaining >= 0);
}
