/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801DC5C.c
 * Original SHA-256: b3c9284e8065b50901a2db258422f4ae9b34c633bf759bfd47c2ee674098912b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x12];
    u16 value;
} SelectionState;

extern SelectionState data_02007F10;
extern u8 data_02008390[];

/* 0801DC5C..0801DC7A: 30 bytes. */
u8 *func_0801DC5C(void)
{
    if (data_02007F10.value == 0xFF)
        return 0;
    return data_02008390;
}
