/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D47DC.c
 * Original SHA-256: 42117fafb81d5757eab5d3f462e86338dddf6866ad4218ebac9f542a4febbf8d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080D47DC..0x080D480C: 48 bytes, 23 instructions. */
typedef struct {
    u8 unknown_00[4];
    u16 value;
} TaskRecord;

extern TaskRecord *func_08005BFC(void *task);

void func_080D47DC(void *task, u16 value)
{
    TaskRecord *record = func_08005BFC(task);
    u16 previous = record->value;
    u16 replacement = (previous & 0xF) | (value << 4);

    if (previous > 0xFF) {
        replacement += 0x100;
    }
    record->value = replacement;
}
