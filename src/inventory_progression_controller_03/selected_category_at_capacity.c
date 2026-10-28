/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct SelectionContext { u8 unknown[88]; u32 current; u32 requested; u32 previous; };
struct InventoryRecord { u16 item_id; u8 count; u8 unknown; };
typedef char RecordSize[(sizeof(struct InventoryRecord)==4)?1:-1];
typedef char ContextSize[(sizeof(struct SelectionContext)==100)?1:-1];
extern struct SelectionContext *gCapacitySelectionContext;
asm(".global gCapacitySelectionContext\n.set gCapacitySelectionContext,0x0200f450");
#define ACTIVE_CONTEXT gCapacitySelectionContext
extern s32 RetailCall_080caa74(void);
extern u32 RetailCall_080cca80(void);
asm(".global RetailCall_080caa74\n.thumb_set RetailCall_080caa74,0x080caa75");
asm(".global RetailCall_080cca80\n.thumb_set RetailCall_080cca80,0x080cca81");

/* Capacity rejection for the selected inventory/queue category. */
u32 SelectedCategoryAtCapacity(void)
{
    s32 category = ACTIVE_CONTEXT->current >> 16;
    if ((ACTIVE_CONTEXT->previous >> 16) == category && category != 0)
        return 0;
    switch (category) {
    case 0: {
        u16 item_id = ACTIVE_CONTEXT->requested;
        const struct InventoryRecord *record = (const struct InventoryRecord *)0x02001940;
        int index;
        for (index = 0; index < 361; index++, record++) {
            if (record->item_id == item_id)
                return record->count == 99;
        }
        record = (const struct InventoryRecord *)0x02001ee4;
        for (index = 0; index < 14; index++, record++) {
            if (record->item_id == item_id)
                return record->count == 99;
        }
        break;
    }
    case 1:
        return RetailCall_080caa74() == 64;
    case 2:
        return (u8)RetailCall_080cca80() == 20;
    }
    return 0;
}
