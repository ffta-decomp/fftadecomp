typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct TreeNode;
struct Record { u16 preceding[9]; u16 order, previous_order, extent; };
struct RangeScan { u16 cursor, limit, width, flags; };
struct NodeWords { struct Record *record; u32 key; };
extern void CopyRangeNodeWords(struct TreeNode *, struct Record **, u32 *);
__asm__(".global CopyRangeNodeWords\n.thumb_set CopyRangeNodeWords,0x080c7b79");
u32 ScanRecordRange(struct TreeNode *node, struct RangeScan *scan)
{
    struct NodeWords words;
    struct Record *record;
    u32 first_limit, record_order, cursor, width, bit;
    s32 boundary;
    u32 extent, order, flags;
    u32 result;
    CopyRangeNodeWords(node, &words.record, &words.key);
    record = words.record;
    /* Preserve the first samples separately from later explicit reads. */
    first_limit = *(volatile u16 *)&scan->limit;
    record_order = record->order;
    if (first_limit <= record_order) {
        result = 0;
        goto finished;
    }
    if (*(volatile u16 *)&scan->cursor > record_order)
        goto keep_going;
    cursor = scan->cursor;
    width = scan->width;
    boundary = cursor + width;
    if (scan->limit >= boundary)
        goto check_gap;
    flags = scan->flags;
    bit = 2;
    goto mark;
check_gap:
    if (cursor >= record_order)
        goto advance_cursor;
    if ((s32)*(volatile u16 *)&record->order - (s32)cursor - (s32)width < 0)
        goto advance_cursor;
    flags = scan->flags;
    bit = 1;
mark:
    scan->flags = bit | flags;
    result = 0;
    goto finished;
advance_cursor:
    {
        register struct Record *advance __asm__("r1") = *(struct Record *volatile *)&words.record;
        /* This defined late pointer occupies the original r1 address role. */
        __asm__("" : "+r" (advance));
        extent = advance->extent;
        order = advance->order;
        scan->cursor = extent + order;
    }
keep_going:
    result = 1;
finished:
    return result;
}
