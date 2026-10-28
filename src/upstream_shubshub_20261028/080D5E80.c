/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D5E80.c
 * Original SHA-256: 49d347089faa0e69b383813625bffa0bd34223b84a70c0176e6e7267ab3dc03f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Resource080D5E80 {
    u16 flags;
    u16 offset;
    u8 data[0];
} __attribute__((packed));

extern u32 func_08011348(const void *entries, const void *data, u16 index,
                        u8 layer, s16 x, s16 y, s16 width, s16 height,
                        u8 mode, u16 attributes);

/* Complete [0x080D5E80, 0x080D5F22): 162 bytes, 80 instructions. */
u32 func_080D5E80(const struct Resource080D5E80 *header,
                 u16 index, u16 x, u16 y,
                 u16 width, u16 height, u8 mode)
{
    const void *entries = header->data;
    const void *data = (const u8 *)header + header->offset;
    u16 attributes = 0;

    if (header->flags & 4)
        attributes |= 0x2000;
    if (header->flags & 8)
        attributes |= 0x4000;
    return func_08011348(entries, data, index, 2,
                         (s16)x, (s16)y, (s16)width, (s16)height,
                         mode, attributes);
}
