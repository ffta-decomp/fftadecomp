/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081257D0.c
 * Original SHA-256: c144a82810b0f04d7935c09203241f0a3b5887cf854224ff9c042063d000ceaf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 x;
    u8 y;
    u8 map_value;
    u8 unknown_03;
} CoordinateEntry081257D0;

typedef struct {
    CoordinateEntry081257D0 entries[32];
    s32 count;
} CoordinateList081257D0;

typedef void (*ClearBuffer081257D0)(void *destination, u32 size);
typedef void (*CopyBuffer081257D0)(void *destination, const void *source, u32 size);

extern ClearBuffer081257D0 const g_callbacks_0836D4B8[];
extern CopyBuffer081257D0 const data_0836D4BC[];
extern void *func_08121B64(u32 size);
extern void func_08121B78(void *object);
extern CoordinateList081257D0 *func_08121C58(u8 selector);

/* Complete [0x081257D0, 0x08125884): 180 bytes, 77 instructions. */
void func_081257D0(u8 first_selector, u8 second_selector, u8 destination_selector)
{
    CoordinateList081257D0 *temporary = func_08121B64(sizeof(*temporary));
    CoordinateList081257D0 *first;
    CoordinateList081257D0 *second;
    u16 first_size;

    g_callbacks_0836D4B8[0](temporary, sizeof(*temporary));
    first = func_08121C58(first_selector);
    second = func_08121C58(second_selector);
    temporary->count = first->count + second->count - 1;
    first_size = (first->count - 1) * sizeof(first->entries[0]);
    {
        CopyBuffer081257D0 const *copy = data_0836D4BC;

        copy[0](temporary, first, first_size);
        copy[0]((u8 *)temporary + first_size, second,
                (u16)(second->count * sizeof(second->entries[0])));
        first = func_08121C58(destination_selector);
        copy[0](first, temporary, sizeof(*temporary));
    }
    func_08121B78(temporary);
}
