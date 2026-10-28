/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08019FC8.c
 * Original SHA-256: fd6325a67ccf0049fab83c8919a7492413335bbe87ab4cb48eab2aa947d07e0a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct PackedRecord08019FC8 {
    u8 unknown_00[0x20];
    u32 first[4];
    u32 second[4];
    u32 parameters[4];
    u8 unknown_50[8];
} __attribute__((packed));

extern u16 data_02007F10;
extern const struct PackedRecord08019FC8 data_08569104[];
extern void *func_08020DA0(const void *first, u32 parameters, const void *second);
extern void func_08020FA4(void *object, u32 value);

/* Complete [0x08019FC8, 0x0801A060): 152 bytes, 70 instructions. */
void *func_08019FC8(u8 index)
{
    const u8 *base = (const u8 *)data_08569104;
    const u8 *first = base + data_08569104[data_02007F10].first[index];
    const u8 *second = base + data_08569104[data_02007F10].second[index];
    u32 parameters = data_08569104[data_02007F10].parameters[index];
    void *object = func_08020DA0(first, parameters, second);

    func_08020FA4(object, 0);
    return object;
}
