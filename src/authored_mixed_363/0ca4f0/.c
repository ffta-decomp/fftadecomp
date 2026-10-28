/* MIXED: one actual2B address ADD; five-slot game rule/loop/calls remain C. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct EquippedPropertyUnit { u8 unknown_00[42]; u16 items[5]; };
typedef char EquipmentOffset[((u32)&((struct EquippedPropertyUnit *)0)->items == 42) ? 1 : -1];
extern u32 GetItemProperty(u16, u8) __asm__("0x080ca7a4");
u32 SumEquippedItemProperty(const struct EquippedPropertyUnit *unit, u32 selector_raw)
{
    u8 selector = (u8)selector_raw;
    u32 total = 0;
    int slot;
    for (slot = 0; slot <= 4; ++slot) {
        register u32 slot_byte_offset __asm__("r0") = slot * 2;
        register const u16 *first_item __asm__("r1") = unit->items;
        u16 item;
        __asm__ volatile(".Lw6_CA4F0_actual_item_address:\nadd %0,%0,%1"
            : "+r"(first_item) : "r"(slot_byte_offset) : "cc");
        item = *first_item;
        if (item != 0)
            total += GetItemProperty(item, selector);
    }
    return total;
}
