/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08011634.c
 * Original SHA-256: a801da02c56221c4cbdd8bbc4bc6ec482e6c31e8a2a281339b221b411e379e00
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* 0x08011634 - 16 bytes: capture a shared word and its address. */
#include "ffta.h"

extern u32 data_02009174;

typedef struct {
    u32 *address;
    u32 value;
} WordSnapshot08011634;

void func_08011634(WordSnapshot08011634 *snapshot)
{
    snapshot->address = &data_02009174;
    snapshot->value = data_02009174;
}
