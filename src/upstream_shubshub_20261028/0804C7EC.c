/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804C7EC.c
 * Original SHA-256: 0184aef0d015142392222df6b2fc2ca366045013df5dc3c233f8cc4f21faceac
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0804C7EC..0x0804C832: 70 bytes / 35 instructions. */
struct Record0804C7EC {
    u8 unknown_00[8];
    u16 position;
    u16 mode;
    u8 type;
    u8 active;
    u8 count;
    u8 unknown_0F[13];
};

void func_0804C7EC(struct Record0804C7EC *records, u16 index)
{
    if (records[index].active != 0 && records[index].type == 6) {
        ++records[index].position;
        if (records[index].mode == 1) {
            if (records[index].position + 1 >= records[index].count)
                records[index].position = 0;
        } else {
            if (records[index].position + 1 >= records[index].count)
                records[index].position = records[index].count - 1;
        }
    }
}
