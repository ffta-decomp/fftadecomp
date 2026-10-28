/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C73D8.c
 * Original SHA-256: 0b662a952a081218afffb0c3601b82f82fb76834750f17e28d68367ffe40d0c6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0xAC];
    u8 count;
    u8 unknown_AD;
    u8 flags;
} InputState;

typedef struct {
    u8 unknown_00[2];
    u8 mode;
    u8 unknown_03[0x11D];
    u16 busy;
    u16 ticks;
} SystemState;

extern InputState data_02015738;
extern SystemState data_030028A0;
extern s32 func_08004D68(void);
extern u8 func_080C5F94(void *context);

static inline u8 input_blocked(void)
{
    if (data_02015738.flags & 0x40) {
        if (data_02015738.flags & 0x80)
            return func_08004D68() != 1;
        return 0;
    }
    if (((data_02015738.flags & 0x20) || data_02015738.count > 13) &&
        (data_030028A0.busy != 0 ||
         (data_030028A0.mode != 3 && data_030028A0.ticks > 16)))
        return 1;
    if (data_02015738.flags & 8)
        return 1;
    return 0;
}

u8 func_080C73D8(void *context)
{
    u8 result;

    if (!input_blocked())
        result = func_080C5F94(context);
    else
        result = 2;
    return result;
}
