/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0805D91C.c
 * Original SHA-256: 2ca1cc3cbaa946e48172f1835df43353f74d0f528bd2ae8d864c6bacc7b8f717
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0805D91C..0x0805D948: 44 bytes. */
extern const u8 data_08393890[];
extern void func_08001F34(const void *source, s32 x, s32 y, u8 variant,
                        u8 flip_x, u8 flip_y, u8 flag_28, u8 flag_29,
                        u32 value, u8 mode, const void *transform);

void func_0805D91C(void)
{
    func_08001F34(data_08393890, 40, 7, 0, 0, 0, 0, 0, 0, 0, 0);
}
