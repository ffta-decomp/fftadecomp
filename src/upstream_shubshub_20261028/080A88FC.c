/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080A88FC.c
 * Original SHA-256: f4345f148564d9bf3b80f8aaabf266667e21862c66f28d264bbaf4f40a5d1cf0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080A88FC..0x080A892E: 50 bytes, 25 instructions. */
typedef struct {
    void *object;
    u8 unknown_04[0x28];
} ObjectRecord;

typedef struct {
    u8 unknown_00[0x20];
    ObjectRecord records[15];
    u8 unknown_2B4[0x0C];
    u8 count;
} ObjectRecordList;

ObjectRecord *func_080A88FC(ObjectRecordList *list, void *object)
{
    s32 i;

    for (i = 0; i < list->count; i++) {
        ObjectRecord *record = &list->records[i];
        if (record->object == object) {
            return record;
        }
    }
    return 0;
}
