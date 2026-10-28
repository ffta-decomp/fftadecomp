/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct InventoryEntry { u16 item; u8 total; u8 used; };
typedef char InventoryStride[sizeof(struct InventoryEntry)==4?1:-1];
extern const struct InventoryEntry gInventory[361];
extern const struct InventoryEntry gSpecialInventory[14];
__asm__(".global gInventory\n.set gInventory, 0x02001940");
__asm__(".global gSpecialInventory\n.set gSpecialInventory, 0x02001ee4");

u32 HasAvailableInventoryItem(void);
u32 HasAvailableInventoryItem(void)
{
    const struct InventoryEntry *entry = gInventory;
    s32 index = 0;
    s32 primary_limit;
    do {
        u16 item = entry->item;
        if (item == 0) goto next_primary;
        if (item == 51) goto next_primary;
        if (item == 148) goto next_primary;
        if (item == 286) goto next_primary;
        if (item == 302) goto next_primary;
        if (entry->total > entry->used)
            return 1;
next_primary:
        ++index;
        ++entry;
        /* Keep the retail tail's two Thumb instructions. Fixed O2 otherwise
         * hoists 360 and adds a live register across this entire scan.
         * An unconstrained output lets normal allocation choose the scratch
         * register; condition flags are the only clobbered machine state. */
        __asm__ volatile ("mov %0, #180\n\tlsl %0, %0, #1"
                          : "=r" (primary_limit) : : "cc");
    } while (index <= primary_limit);
    entry = gSpecialInventory;
    index = 0;
    do {
        if (entry->item == 0) goto next_special;
        if (entry->total == 0) goto next_special;
        return 1;
next_special:
        ++index;
        ++entry;
    } while (index <= 13);
    return 0;
}
