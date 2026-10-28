typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
typedef signed char s8;

struct ItemAmountView {
    u16 name_id;
    u16 property_01;
    u16 base_amount;
    u16 minimum_amount;
    u8 property_03[6];
    u16 property_09;
    s8 modifiers[8];
    u8 unknown_18[5];
    u8 ability_set;
    u8 unknown_1e[2];
};
typedef char ItemAmountViewMustBe32Bytes[(sizeof(struct ItemAmountView) == 32) ? 1 : -1];

struct AmountAdjustmentRecord {
    u8 prefix[8];
    u8 percentage_reduction;
    u8 unknown_09;
} __attribute__((packed));

extern const struct ItemAmountView gItems[];
extern const struct AmountAdjustmentRecord gAmountRecords10[];
extern volatile u8 gSaveData[];
extern u8 ItemAmountAdjustmentApplies(u8 selector, u16 item_id);
extern s32 DivideSignedValues(s32 numerator, s32 denominator);

u32 CalculateItemAmount(u8 selector, u16 item_id)
{
    const struct ItemAmountView *items = gItems;
    const struct ItemAmountView *item;
    u32 result;

    item = &items[item_id];
    if (item->property_03[4] & 8) {
        u8 reduction = gAmountRecords10[gSaveData[0x21b4]].percentage_reduction;
        if (ItemAmountAdjustmentApplies(selector, item_id)) reduction += 10;
        result = (u32)DivideSignedValues((s32)(item->base_amount * (100 - reduction)), 100);
        if (result < item->minimum_amount) result = item->minimum_amount;
    } else {
        result = item->base_amount;
    }
    if (!result) result = 1;
    return result;
}
