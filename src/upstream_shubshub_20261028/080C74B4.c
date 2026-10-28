/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C74B4.c
 * Original SHA-256: 9243debb63ee7091606c5ccfefe557c2e0cb4fd9842d13b6f2843cfe527a5a2a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080C74B4..0x080C7546: 146 bytes, including literal pools. */
typedef struct {
    u8 unknown_00[0xAC];
    u8 value;
    u8 unknown_AD;
    u8 flags;
} Status;

typedef struct {
    u8 unknown_00[2];
    u8 type;
    u8 unknown_03[0x11D];
    u16 active;
    u16 value;
} Control;

extern Status data_02015738;
extern Control data_030028A0;
extern s32 func_08004D68(void);
extern u8 func_080C6480(void *object);

static inline u8 is_blocked(void)
{
    if (data_02015738.flags & 0x40) {
        if (data_02015738.flags & 0x80)
            return func_08004D68() != 1;
        return 0;
    }

    if (((data_02015738.flags & 0x20) || data_02015738.value > 13) &&
        (data_030028A0.active != 0 ||
         (data_030028A0.type != 3 && data_030028A0.value > 16)))
        return 1;
    if (data_02015738.flags & 8)
        return 1;
    return 0;
}

u8 func_080C74B4(void *object)
{
    if (is_blocked())
        return 2;
    return func_080C6480(object);
}
