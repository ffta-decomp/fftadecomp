/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08002108.c
 * Original SHA-256: 72455de0c2e45602c8f000cc86444c7b50be92df11a66ddaff0ffe069c9fcee1
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 data_03002F58;
extern u8 data_03003170[2][128];
extern u32 data_03003168[2];

extern u32 func_080016D4(const void *source, s32 x, s32 y, u32 attributes,
                         u8 priority, u32 layer, void *buffer, u32 count,
                         u32 cursor);

/* Complete target: 0x08002108..0x0800216C, 100 bytes. */
void func_08002108(const void *source, s32 x, s32 y, u32 attributes,
                   u8 priority, u32 layer)
{
    u8 *buffer_index = &data_03002F58;
    u8 *buffer = data_03003170[*buffer_index];
    u32 *cursors = data_03003168;
    u32 cursor = cursors[*buffer_index];

    cursors[*buffer_index] = func_080016D4(source, x, y, attributes, priority,
                                         layer, buffer, 16, cursor);
}
