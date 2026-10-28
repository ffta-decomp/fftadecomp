/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08021D40.c
 * Original SHA-256: 76aa10b7b504a7e28105845e03c75071c954985da06983c7c8db90262de77a91
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08021D40..0x08021D46: 6 bytes. */
typedef struct {
    u8 unknown_00[0x18];
    s16 x;
    s16 y;
} Position08021D40;

void func_08021D40(Position08021D40 *position, s16 x, s16 y)
{
    position->x = x;
    position->y = y;
}
