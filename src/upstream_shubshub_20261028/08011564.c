/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08011564.c
 * Original SHA-256: 55a4b76f9a9ad788b8a24ea219867e87d0b7478cca33b26a0701310480e855e5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08011564..0x0801159C: 56 bytes / 25 instructions. */
typedef struct {
    u8 active;
    u8 unknown_01[0x3F];
} Slot;

typedef struct {
    u16 count;
    u8 unknown_02[2];
    u32 unknown_04;
    u32 unknown_08;
    u32 unknown_0C;
    u32 unknown_10;
    Slot *slots;
} SlotState;

extern SlotState data_02009170;

void func_08011564(void)
{
    s32 index;

    for (index = 0; index < data_02009170.count; index++)
        data_02009170.slots[index].active = 0;
    data_02009170.unknown_04 = 0;
    data_02009170.unknown_08 = 0;
    data_02009170.unknown_0C = 0;
    data_02009170.unknown_10 = 0;
}
