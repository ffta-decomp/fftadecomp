/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800D884.c
 * Original SHA-256: af59bd118dbb35415a886e3b2f8ec73e9bb5c2b6376637da2dffec488329da05
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800D884..0x0800D8F8: 116 bytes. */
typedef struct {
    u8 unknown_00[16];
    u8 value_10;
    u8 value_11;
    u8 value_12;
    u8 value_13;
    u8 unknown_14[8];
} ResourceRecord;

extern ResourceRecord *func_0800C614(void *);

void func_0800D884(void *object, u8 mode, u8 index, u8 value_12,
                  u8 value_13, u8 value_11, u8 value_10)
{
    ResourceRecord *record = 0;

    switch (mode) {
    case 0:
        record = func_0800C614(object);
        break;
    case 1:
        record = func_0800C614(object) + index;
        break;
    case 2:
        record = func_0800C614(object) + index;
        break;
    }
    record->value_10 = value_10;
    record->value_12 = value_12;
    record->value_13 = value_13;
    record->value_11 = value_11;
}
