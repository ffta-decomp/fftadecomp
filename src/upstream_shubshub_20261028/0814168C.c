/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0814168C.c
 * Original SHA-256: 0fbafd50fd82ae6627cd1b6fd1a24278921944ffb206d301a5aaa7474660d16c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x0814168C, 0x081416D2), 70 bytes, 28 instructions.
 * Record views retain only the observed halfword at +4. */
typedef struct {
    u8 unknown_00[4];
    u16 value;
} Record0814168C;

extern u8 data_020084D8;
extern Record0814168C data_0200F2E0;
extern Record0814168C data_0200F320;

u32 func_0814168C(u16 selector)
{
    Record0814168C *record = 0;

    if (data_020084D8 & 2) {
        switch (selector) {
        case 1:
            record = &data_0200F2E0;
            break;
        case 2:
            record = &data_0200F320;
            break;
        }
        if (record != 0) {
            u32 result = record->value;

            if (result != 0)
                result = 1;
            return result;
        }
    }
    return 0;
}
