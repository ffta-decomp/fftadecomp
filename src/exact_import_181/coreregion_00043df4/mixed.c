#include "interfaces.h"

/* Only candidate slots1/2 are conditioned on progression flags303/559. */
u32 BuildFlagFilteredChoiceRows(struct ChoiceRows *output, u32 width)
{
    u16 choice_ids[5];
    s32 count;
    s32 index;
    const u16 *id;
    const void *const *contents;
    struct ChoiceRow *row;
    u32 height;

    CopyChoiceBytes(choice_ids, gChoiceIds, 10);
    output->rows = output->storage;
    count = 0;
    index = 0;
    contents = gChoiceContents;
    id = choice_ids;
    row = output->storage;
    do {
        if (index == 1 && GetGameFlag(0x303) == 0)
            goto next_choice;
        if (index == 2 && GetGameFlag(0x559) == 0)
            goto next_choice;
        row->ordinal = count;
        row->flags = 1;
        row->source_index = index;
        row->content = contents[*id];
        {
            u32 metric_address;
            /* Original halfword read/scale/add. Both address inputs must be
             * ready before the read; early clobber preserves them throughout.
             * The exact memory input models the ID read, with no barrier. */
            __asm__("ldrh %0, [%2]\n\tlsl %0, %0, #1\n\tadd %0, %0, %1"
                    : "=&l" (metric_address)
                    : "l" (CHOICE_METRICS), "l" (id), "m" (*id)
                    : "cc");
            row->metric = *(const u16 *)metric_address;
        }
        ++row;
        ++count;
next_choice:
        ++id;
        ++index;
    } while (index <= 4);
    if (count > 6)
        height = 15;
    else
        height = count * 2 + 3;
    output->header_content = gChoiceHeaderContent;
    output->origin_x = 0;
    output->origin_y = 0;
    output->width = width;
    output->height = height;
    output->style = 203;
    output->kind = 0;
    output->offset = 0;
    output->stride = 16;
    output->flags = 0;
    output->count = count;
    return count;
}
