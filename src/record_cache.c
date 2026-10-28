#include "record_cache.h"

/* Reuse an equal record in the active bank, or claim its first free slot.
 * Volatile accesses retain the retail read order and the read-before-write
 * sequence when a free slot is populated.
 */
int FindOrInsertRecord8(const volatile struct Record8 *record)
{
    u8 active_bank = gRecordBankIndex;
    volatile u8 *slot_used = gRecordSlotUsed + active_bank * 32;
    struct Record8 *bank_records = gRecordEntries + active_bank * 32;
    int record_index;

    for (record_index = 0; record_index < 32; record_index++) {
        volatile struct Record8 *candidate = &bank_records[record_index];
        if (slot_used[record_index] != 0 &&
            record->words[0] == candidate->words[0] &&
            record->words[1] == candidate->words[1] &&
            record->words[2] == candidate->words[2] &&
            record->words[3] == candidate->words[3]) {
            return record_index;
        }
    }

    for (record_index = 0; record_index < 32; record_index++) {
        volatile struct Record8 *free_record = &bank_records[record_index];
        if (slot_used[record_index] == 0) {
            slot_used[record_index] = 1;
            free_record->words[0] = record->words[0];
            free_record->words[1] = record->words[1];
            free_record->words[2] = record->words[2];
            free_record->words[3] = record->words[3];
            return record_index;
        }
    }
    return 0;
}
