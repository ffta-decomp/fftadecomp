/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804C7C8.c
 * Original SHA-256: fafa648ff745571f7ab538c12d98b7318c7d9a8cc695536b6fa95b9f30bcb78d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0804C7C8..0x0804C7EA: 34 bytes. */
typedef struct {
    u8 unknown_00[8];
    u16 current;
    u8 unknown_0A[4];
    u8 count;
    u8 unknown_0F[13];
} Record0804C7C8;

u8 func_0804C7C8(const Record0804C7C8 *records, u16 index)
{
    u8 result = 0;

    if (records[index].current + 1 == records[index].count)
        result = 1;
    return result;
}
