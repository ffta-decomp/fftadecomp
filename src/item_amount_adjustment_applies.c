typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct ItemAdjustmentDescriptor {
    u32 category_mask;
} __attribute__((packed));

extern const struct ItemAdjustmentDescriptor *GetItemAdjustmentRecord(u8 selector);
extern u32 GetItemProperty(u16 item_id, u8 property);

/* Test whether the descriptor selected for this item category includes it. */
u8 ItemAmountAdjustmentApplies(u8 selector, u16 item_id)
{
    const struct ItemAdjustmentDescriptor *descriptor = GetItemAdjustmentRecord(selector);

    if (descriptor) {
        u32 category = GetItemProperty(item_id, 3);
        if (descriptor->category_mask & (1u << (category - 1))) return 1;
    }
    return 0;
}
