/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804C598.c
 * Original SHA-256: 6cfb15117f331aa3f95735d4c460908b7d9c86ff6bfc5149bac656ed2fd07f9b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern void func_0804C4D4(Entry *base, u16 index, u16 selector,
                        u8 width, u8 count, u8 mode, u8 delay,
                        const u8 *graphics, const u8 *layout, u16 attributes);

/* Complete target: [0x0804C598, 0x0804C5F8), 96 bytes. */
void func_0804C598(Entry *base, u16 index, u16 selector,
                   u8 width, u8 count, u8 mode, u8 delay,
                   const u8 *graphics, const u8 *layout, u16 attributes)
{
    func_0804C4D4(base, index, selector, width, count, mode, delay,
                   graphics, layout, attributes);
    base[index].field_0c = 1;
}
