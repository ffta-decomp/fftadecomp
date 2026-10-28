/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804C4D4.c
 * Original SHA-256: 86b1d20eafe1203c3db235f7616aa664cdd2341154db14e75fa00daeb616f84c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern void func_0804C524(Entry *base, u16 index, u32 selector,
                         u8 width, u8 count, u32 mode, u8 delay,
                         const u8 *graphics, const u8 *layout,
                         u16 attributes, u8 extra);

/* 0804C4D4..0804C524: 80 bytes, 39 instructions. */
void func_0804C4D4(Entry *base, u16 index, u16 selector,
                   u8 width, u8 count, u8 mode, u8 delay,
                   const u8 *graphics, const u8 *layout, u16 attributes)
{
    func_0804C524(base, index, selector, width, count, mode, delay,
                   graphics, layout, attributes, 0);
}
