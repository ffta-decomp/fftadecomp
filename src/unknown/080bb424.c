/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080BB424.c
 * Original SHA-256: 96f1bde49ea4ff22627aa67d104d0e63e560ae93ffe57a69afc87e975edfcafa
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct Motion080BB424 {
    s32 target_x;
    s32 target_y;
    s32 current_x;
    s32 current_y;
    s32 angle;
    s32 turn_percent;
    s32 speed;
} Motion080BB424;

typedef struct Entry080BB424 {
    u8 angle;
    u8 angle_step;
    s16 x;
    s16 z;
    s16 y;
    u8 flags;
    u8 unknown_09[3];
    Motion080BB424 horizontal;
    Motion080BB424 vertical;
} Entry080BB424;

typedef struct State080BB424 {
    u8 unknown_00[0x68];
    Entry080BB424 *entries;
    u8 count;
} State080BB424;

extern const u8 data_08394648[];
extern void func_080BB370(Entry080BB424 *);
extern void func_08007AD0(Motion080BB424 *);
extern void func_0801C984(s16, s16, s16, s16 *, s16 *);
extern void func_080018A0(const void *, s32, s32, u32, u32, u32, u32,
                          u32, u32, s16, s16, u16, u32);

/* Complete target [0x080BB424, 0x080BB4F8): 212 bytes. */
u32 func_080BB424(State080BB424 *state)
{
    Entry080BB424 *entry = state->entries;
    u32 active = 0;
    s32 i;

    for (i = 0; i < state->count; i++, entry++) {
        if (entry->flags & 1) {
            func_080BB370(entry);
            func_08007AD0(&entry->horizontal);
            func_08007AD0(&entry->vertical);
            entry->angle += entry->angle_step;
            entry->x = entry->horizontal.current_x >> 8;
            entry->y = entry->horizontal.current_y >> 8;
            entry->z = entry->vertical.current_y >> 8;
            active = 1;
        }
        if (entry->flags & 2) {
            s16 x;
            s16 y;

            func_0801C984(entry->x, entry->z, entry->y, &x, &y);
            func_080018A0(data_08394648, x, y, 1, 0, 0, 0, 0, 6,
                          0xC0, 0xC0, entry->angle << 8, 1);
        }
    }
    return active;
}
