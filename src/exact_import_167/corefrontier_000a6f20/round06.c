#include "interfaces.h"

static inline struct Row *GetLiveRow(struct Block *block, int index)
{
    if (block->count < index)
        return 0;
    return (struct Row *)(block->row_storage + 44 * index);
}

/* Snapshot loop bounds, but preserve live row eligibility and pointer reloads. */
int CoreFrontier_000A6F20(struct Context *context)
{
    int block_count;
    int block_index;
    int row_count;
    int row_index;
    struct Block *block;
    struct Row *row;
    if ((u8)ReadSaveByte(13) == 0)
        return 0;
    if ((u8)GetGameFlag(65) == 0)
        return 0;
    block_count = context->count;
    for (block_index = 0; block_index < block_count; ++block_index) {
        block = &context->blocks[block_index];
        /* Retail A6F68 snapshots a distinct header view before either node
         * load. Keep that single pointer definition; no fixed register, memory
         * clobber or extra volatile access is required. ADD updates flags. */
        __asm__("add %0, %1, #0" : "=l"(row) : "l"(block) : "cc");
        if (!block->node)
            continue;
        if ((u8)UnitField27HasBit15(block->node->unit) != 0)
            continue;
        if ((u8)IsSpecialNode(block->node) != 0) {
            if ((u8)GetGameFlag(66) == 1)
                continue;
        } else {
            if ((u8)GetGameFlag(66) == 0)
                continue;
        }
        if (row->kind == 11)
            continue;
        if (row->kind == 12)
            continue;
        if (row->payload.action == 265)
            continue;
        row_count = block->count;
        for (row_index = 0; row_index < row_count; ++row_index) {
            row = GetLiveRow(block, row_index);
            if (!(row->flags & 128))
                continue;
            if ((u8)UnitField19IsZero(row->node->unit) != 0)
                continue;
            if (row->flags & 64)
                continue;
            if (row->payload.properties & 2048)
                continue;
            if ((u8)CheckUnitContinuation(row->node->unit) != 0)
                return 1;
        }
    }
    return 0;
}
