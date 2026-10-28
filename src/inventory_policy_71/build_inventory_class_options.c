/* Method-local interface declarations from the frozen build. */
#ifndef WORKER3_SCENE_TASK_0006EC60_INTERFACES_H
#define WORKER3_SCENE_TASK_0006EC60_INTERFACES_H

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;

struct InventoryRecord {
    u16 item_id;
    u8 owned_count;
    u8 reserved_count;
};

struct ItemClassOptions {
    u8 preceding_code;
    u8 codes[6];
    u8 count;
};

typedef char inventory_record_size_guard[(sizeof(struct InventoryRecord) == 4) ? 1 : -1];
typedef char item_class_options_size_guard[(sizeof(struct ItemClassOptions) == 8) ? 1 : -1];

extern struct InventoryRecord *GetInventoryPartition(u16 item_id, s32 *count);
extern u8 GetInventoryItemClass(u16 item_id);
extern const u8 ItemClassOptionCodes[5];

/* This ROM table binding adds no machine instructions. */
__asm__(".global ItemClassOptionCodes\n.set ItemClassOptionCodes, 0x08393b40");

#endif


/* BuildInventoryClassOptions: fill the caller's class option list and count.
 * The address-based export remains stable for the recovered caller.
 */
void BuildInventoryClassOptions(struct ItemClassOptions *options)
{
    u8 class_present[5];
    s32 inventory_count;
    struct InventoryRecord *inventory;
    u16 index;

    index = 0;
    do {
        class_present[index] = 0;
        index = (u16)(index + 1);
    } while (index <= 4);

    options->count = 0;
    inventory = GetInventoryPartition(1, &inventory_count);
    index = 0;
    while (index < inventory_count) {
        struct InventoryRecord *record =
            (struct InventoryRecord *)(((u32)index << 2) + (u32)inventory);
        if (record->owned_count != 0) {
            u8 item_class = GetInventoryItemClass(record->item_id);
            class_present[item_class] = 1;
        }
        index = (u16)(index + 1);
    }

    index = 0;
    do {
        if (class_present[index] == 1) {
            options->codes[options->count] = ItemClassOptionCodes[index];
            options->count = (u8)(options->count + 1);
        }
        index = (u16)(index + 1);
    } while (index <= 4);

    inventory = GetInventoryPartition(362, &inventory_count);
    index = 0;
    while (index < inventory_count) {
        struct InventoryRecord *record =
            (struct InventoryRecord *)(((u32)index << 2) + (u32)inventory);
        u8 item_class = GetInventoryItemClass(record->item_id);
        if (item_class == 5 && record->owned_count != 0) {
            options->codes[options->count] = item_class;
            options->count = (u8)(options->count + 1);
            break;
        }
        index = (u16)(index + 1);
    }
}
