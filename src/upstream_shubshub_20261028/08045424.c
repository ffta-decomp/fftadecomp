/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08045424.c
 * Original SHA-256: cb65c980e582b5340ca95d5184ed6a82d50d7332c7f20a298ae88415be0c80b5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Entry08045424 {
    u8 unknown_00[6];
    u8 selector;
    u8 unknown_07[5];
};

struct Record08045424 {
    u8 unknown_00;
    u8 unknown_08 : 5;
    u8 value : 8;
    u8 unknown_15 : 3;
    u8 unknown_03[24];
} __attribute__((packed));

extern const struct Entry08045424 g_table_08563A70[];
extern const struct Record08045424 g_table_08564670[];
extern u32 func_08036330(u8);

/* Target: [0x08045424, 0x08045482), 94 bytes, 41 instructions. */
u8 func_08045424(u8 index)
{
    u8 value = g_table_08564670[g_table_08563A70[index].selector].value;
    s32 result;

    if (value == 0)
        return 0xff;
    if (value & 0x80)
        result = value + 0x7f;
    else
        result = func_08036330(value) - 1;
    return result;
}
