/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804C7A0.c
 * Original SHA-256: 2e44ea6e11b230adb8bcb0ff00f75703bd733235af4a1f2f805ab10bd539e366
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0804C7A0..0x0804C7B2: 18 bytes. */
typedef struct {
    u8 unknown_00[0x0D];
    u8 active;
    u8 unknown_0E[0x0E];
} Entry0804C7A0;

void func_0804C7A0(Entry0804C7A0 *entries, u16 index)
{
    entries[index].active = 0;
}
