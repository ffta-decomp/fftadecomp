typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct ItemAdjustmentDescriptor {
    u32 category_mask;
    u16 item_ids[30];
} __attribute__((packed));

extern const struct ItemAdjustmentDescriptor *GetItemAdjustmentRecord(u8 selector);

static inline u16 ReadOneBasedEntry(u8 selector, u8 index)
{
    const struct ItemAdjustmentDescriptor *descriptor = GetItemAdjustmentRecord(selector);
    if (!descriptor || !index) return 0;
    return descriptor->item_ids[index - 1];
}

/* Scan the observed 31-slot range for an item ID. */
u8 ItemInAdjustmentList(u8 selector, u16 item_id)
{
    u8 index;
    /* Retain the original pre-loop descriptor lookup; the loop resolves it again. */
    GetItemAdjustmentRecord(selector);
    for (index = 0; index <= 30; ++index) {
        if (ReadOneBasedEntry(selector, index) == item_id) return 1;
    }
    return 0;
}
