/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08041FB4.c
 * Original SHA-256: 703af2461f771342a1bbd690928fac6270baffd7912c0cf6c891064530a1b5fa
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 *destination;
    u16 *source;
    u8 unknown_10[5];
    u8 width;
    u8 visible_rows;
    u8 source_rows;
    s16 row_limit;
    u8 unknown_1A[4];
    u8 destination_stride;
    u8 unknown_1F;
} MenuList;

extern u16 func_08017B50(MenuList *list);
extern s32 func_08142950(s32 dividend, s32 divisor);
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete owner: 0x08041FB4..0x08042024, 112 bytes. */
void func_08041FB4(MenuList *list, u16 row)
{
    u16 rows = func_08017B50(list) * 2;
    u16 width = list->width;
    u16 *destination = list->destination;
    u32 remaining = rows;

    while (remaining != 0)
    {
        row = func_08142950(row, list->source_rows * 2);
        func_0814186C(list->source + row * width, destination, ((width * 2) >> 1) & 0x001FFFFF);
        destination += list->destination_stride;
        remaining--;
        row++;
    }
}
