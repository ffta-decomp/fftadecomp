/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801DC24.c
 * Original SHA-256: 441c9aa24e05ae341f25f90af28e41a232fd1302122d7811863d684fabaf4f8a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct TransferState0801DC24 {
    u8 unknown_00[0x10];
    u8 enabled;
    u8 unknown_11;
    u16 selector;
} TransferState0801DC24;

extern TransferState0801DC24 data_02007F10;
extern u16 data_03003860;
extern u16 func_0801D980(u16 index, u8 mode);

/* Complete [0x0801DC24, 0x0801DC5C): 56 bytes, 22 instructions. */
void func_0801DC24(u16 index)
{
    TransferState0801DC24 *state = &data_02007F10;

    if (state->selector != 0xFF) {
        if (state->enabled != 0)
            data_03003860 = func_0801D980(index, 1);
        else
            func_0801D980(index, 0);
    }
}
