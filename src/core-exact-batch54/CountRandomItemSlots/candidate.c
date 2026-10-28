typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

u32 CountRandomItemSlots(void)
{
    u8 slot_index = 0;
    u8 nonempty_slot_count = 0;
    const u16 *const random_item_choices = (const u16 *)0x02001F30;

    do {
        if (random_item_choices[slot_index] != 0)
            nonempty_slot_count = (u8)(nonempty_slot_count + 1);
        slot_index = (u8)(slot_index + 1);
    } while (slot_index <= 4);

    return (u32)nonempty_slot_count;
}
