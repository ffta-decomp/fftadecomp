/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0805D13C.c
 * Original SHA-256: 5d07a760f3bce725225a03ed08fb96aa2587ce73ff1eee05a89af9a6aa1c794e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0805D13C..0x0805D174: 56 bytes. */
typedef struct {
    u8 unknown_00[0x145C];
    u16 values[16];
} ValueState;

extern ValueState *data_0200F448;

void func_0805D13C(u16 value)
{
    s32 index;

    for (index = 0; index < 16; index++) {
        if (data_0200F448->values[index] != 0 && data_0200F448->values[index] == value) {
            data_0200F448->values[index] = 0;
            break;
        }
    }
}
