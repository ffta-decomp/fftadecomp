/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08050CDC.c
 * Original SHA-256: bc21b47b7cc6a07854ec5a3b851ce4fa538b81544d76ba9ed586fed04ad29cd5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08050CDC..0x08050CE8: 12 bytes. */
typedef struct {
    u8 unknown_00[0x15];
    u8 value;
} SortRecord08050CDC;

s32 func_08050CDC(const void *first, const void *second)
{
    const SortRecord08050CDC *a = *(const SortRecord08050CDC * const *)first;
    const SortRecord08050CDC *b = *(const SortRecord08050CDC * const *)second;

    return a->value - b->value;
}
