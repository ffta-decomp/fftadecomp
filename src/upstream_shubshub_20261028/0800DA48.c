/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0800DA48.c
 * Original SHA-256: 9b497eee192cf532ce10214e132de723d88c5a826530f35190938f2a38539ff6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0800DA48..0x0800DA86: 62 bytes / 29 instructions. */
struct Object0800DA48;

extern void *func_0800C614(const struct Object0800DA48 *object);

u8 *func_0800DA48(const struct Object0800DA48 *object, u8 mode, u8 index)
{
    u8 *data = 0;

    switch (mode) {
    case 0:
        data = func_0800C614(object);
        break;
    case 1:
        data = (u8 *)func_0800C614(object) + index * 0x140;
        break;
    case 2:
        data = (u8 *)func_0800C614(object) + index * 0x140;
        break;
    }
    return data;
}
