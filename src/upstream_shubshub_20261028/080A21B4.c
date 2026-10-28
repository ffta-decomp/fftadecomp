/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080A21B4.c
 * Original SHA-256: 635d351978fceeaa97a345cea74bc63e137947d253aacce9c308b47e8e45fd2d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xf6];
    u8 x;
    u8 y;
} Unit080A21B4;

typedef struct {
    Unit080A21B4 *unit;
    Unit080A21B4 *partner;
} Entry080A21B4;

typedef struct {
    Entry080A21B4 *first[6];
    Entry080A21B4 *second[6];
    u16 count;
} State080A21B4;

/* Complete [0x080A21B4, 0x080A220E): 90 bytes, 45 instructions. */
void func_080A21B4(State080A21B4 *state, Entry080A21B4 *first,
                  Entry080A21B4 *second)
{
    u8 x;
    u8 y;

    state->first[state->count] = first;
    state->second[state->count] = second;
    first->partner = second->unit;
    second->partner = first->unit;

    x = first->unit->x;
    y = first->unit->y;
    first->unit->x = second->unit->x;
    first->unit->y = second->unit->y;
    second->unit->x = x;
    second->unit->y = y;
    state->count++;
}
