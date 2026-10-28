/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806FFE4.c
 * Original SHA-256: ab5d619a655e703a64b8e8ff87229b39f79601bf142fa1e926f9af085ad553f3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0c];
    u8 width;
    u8 height;
    u8 unknown_0e[6];
    const void *data;
} Image0806FFE4;

extern void func_0814186C(const void *source, void *destination, u32 size);

/* 0x0806FFE4..0x0806FFF8: 20 bytes, 9 instructions. */
void func_0806FFE4(const Image0806FFE4 *image, void *destination)
{
    func_0814186C(image->data, destination, image->width * image->height);
}
