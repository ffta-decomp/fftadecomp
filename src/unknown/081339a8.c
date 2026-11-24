typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;

extern u32 BattleDependency_00131DA4(const u8 *mask, s32 state_index,
                                    u8 channel_selector);
asm(".global BattleDependency_00131DA4\n"
    ".thumb_set BattleDependency_00131DA4, 0x08131da5");

/* The incoming selector is consumed as LOW8. Keep the original index
 * snapshot before normalization, then consume both values in the row query. */
u8 BattleDependency_001339A8(u32 record_index, s32 state_index,
                             u32 channel_selector)
{
    register u32 record_snapshot asm("r3") = record_index;
    register u32 channel_work asm("r2") = channel_selector;
    u32 row_offset;
    const u8 *effect_mask_row;
    u32 selected;

    /* Both initialized working values remain actual inputs to the query. */
    asm("" : "+r"(record_snapshot), "+r"(channel_work));
    channel_work = (u8)channel_work;
    /* The selector is now known LOW8; this boundary does not redefine it. */
    asm("" : "+r"(record_snapshot) : "r"(channel_work));
    row_offset = ((record_snapshot << 1) + record_snapshot) << 2;
    effect_mask_row = (const u8 *)(0x0852790Cu + row_offset);
    selected = BattleDependency_00131DA4(
        effect_mask_row, state_index, (u8)channel_work);
    return (u8)selected;
}
