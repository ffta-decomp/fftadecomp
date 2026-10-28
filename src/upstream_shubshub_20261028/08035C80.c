/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08035C80.c
 * Original SHA-256: 9817790efccf2e51222ee183458fe39b5a0947c87062518c6e536c70d85b2141
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08035C80..0x08035CAA: 42 bytes / 18 instructions. */
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern void func_08035BD4(u16 *destination, u16 digits, u32 value, u16 flags);
extern void func_0808A604(u8 index, u8 command);

void func_08035C80(u32 value)
{
    u16 *destination = func_0808B8E4(2, 1, 1, 1);

    func_08035BD4(destination, 8, value, 0xD000);
    func_0808A604(2, 2);
}
