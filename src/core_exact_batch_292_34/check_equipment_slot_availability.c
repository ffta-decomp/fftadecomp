typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct UnitEquipmentView { u8 unknown[42]; u16 equipment[5]; };
extern u32 RetailCall_080cb1f4(u16);
extern u32 RetailCall_080cd50c(const struct UnitEquipmentView *);
asm(".global RetailCall_080cb1f4
.thumb_set RetailCall_080cb1f4,0x080cb1f5
.global RetailCall_080cd50c
.thumb_set RetailCall_080cd50c,0x080cd50d");

u32 Source52_000269D8(const struct UnitEquipmentView *unit)
{
    u32 has_empty = 0;
    u8 matching_count = 0;
    int slot;
    for (slot=0;slot<5;slot++) {
        register u32 byte_offset __asm__("r0") = slot * 2;
        register const u8 *equipment_base __asm__("r1");
        u16 item_id;
        /* Retain each actual address working value at its native phase. */
        asm("" : "+r"(byte_offset));
        equipment_base = (const u8 *)unit + 42;
        asm("" : "+r"(equipment_base));
        equipment_base += byte_offset;
        /* Consume the actual derived slot address before loading its halfword. */
        asm("" : "+r"(equipment_base));
        item_id = *(const u16 *)equipment_base;
        if (item_id != 0) {
            if ((u8)RetailCall_080cb1f4(item_id))
                matching_count++;
        } else {
            has_empty = 1;
        }
    }
    if (has_empty && (((u8)RetailCall_080cd50c(unit) == 8 && matching_count == 1) || matching_count == 0))
        return 1;
    return 0;
}
