/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800BE78.c
 * Original SHA-256: ba6038ee3fa3d5468df0820ae4e5b2ef74c25ffc56a78aa150a6304b7abc9ca2
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800BE78 .. 0x0800BED8: 96 bytes. */
typedef struct {
    u8 id;
    u8 unknown_01[27];
    u8 left;
    u8 top;
    u8 right;
    u8 bottom;
} Region0800BE78;

extern u16 func_0800C050(u8 id);
extern u16 func_0800C068(u8 id);

void func_0800BE78(Region0800BE78 *region, u8 left, u8 top,
                   u8 right, u8 bottom)
{
    u16 width = func_0800C050(region->id);
    u16 height = func_0800C068(region->id);

    if (left < width && right < width && top < height && bottom < height) {
        region->left = left;
        region->top = top;
        region->right = right + 1;
        region->bottom = bottom + 1;
    }
}
