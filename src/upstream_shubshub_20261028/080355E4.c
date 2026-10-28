/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080355E4.c
 * Original SHA-256: 84d70c4ce33dfca5dcabce2965fd0d1c638068b5c431cf7d0ca0da816fddb809
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Complete target: [0x080355E4, 0x08035636), 82 bytes. */
void func_080355E4(const u16 *source, u16 *destination, u32 height,
                   u16 width, u16 stride, u16 offset)
{
    u32 row;
    u32 column;

    for (row = 0; row < height; row++) {
        for (column = 0; column < width; column++)
            destination[column] = offset + *source++;
        destination += stride;
    }
}
