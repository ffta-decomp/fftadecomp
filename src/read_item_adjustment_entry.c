typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct ItemAdjustmentDescriptor {
    u32 category_mask;
    u16 item_ids[30];
} __attribute__((packed));

extern const struct ItemAdjustmentDescriptor *GetItemAdjustmentRecord(u8 selector);

/* Read a one-based item slot; a missing table or slot zero yields zero. */
u16 ReadItemAdjustmentEntry(u8 selector, u8 index)
{
    const struct ItemAdjustmentDescriptor *descriptor = GetItemAdjustmentRecord(selector);
    if (!descriptor || !index) return 0;
    return descriptor->item_ids[index - 1];
}
