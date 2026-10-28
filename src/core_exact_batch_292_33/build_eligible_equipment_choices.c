typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
struct InventoryRecord { u16 item_id; u8 owned_count; u8 reserved_count; };
struct UnitEquipmentView { u8 prefix[42]; u16 equipment[5]; };
struct ActiveSelection { u8 prefix[24]; struct UnitEquipmentView *unit; };
struct ListDescriptor { u8 field_00; u8 layout; u8 field_02; u8 visible_count; u16 count; u8 tail[14]; };
struct ItemListContext { u8 prefix[128]; struct ListDescriptor list; u32 *item_ids; u8 *availability; void *field_9c; u8 *resource_buffer; };
typedef char ListDescriptorSize[(sizeof(struct ListDescriptor) == 20) ? 1 : -1];
typedef char ItemIdsOffset[((u32)&((struct ItemListContext *)0)->item_ids == 148) ? 1 : -1];
typedef char ResourceBufferOffset[((u32)&((struct ItemListContext *)0)->resource_buffer == 160) ? 1 : -1];
extern struct ActiveSelection *gActiveSelection __asm__("0x0200f438");
extern const u8 gItemListResource[] __asm__("0x083a9ca4");
extern const u8 gSmallListLayouts[] __asm__("0x0839144e");
extern void *AllocateContextBuffer(u32 size) __asm__("AllocateCurrentTaskBytes_08005B28");
extern void LoadResourceRange(const void *source, void *destination, u16 first, u16 count) __asm__("DecodeA7IndexedGraphics");
extern struct InventoryRecord *GetInventoryPartition(u16 item_id, s32 *count);
extern u8 IsItemIdInRange1To252(u16 item_id);
extern u8 UnitItemCategoryAllowed(const void *unit, u16 item_id);
extern u8 InspectEquipmentMode0(const void *unit, u16 item_id, u8 slot);

/* Declaration-only linkage to the existing exact Thumb helper. */
__asm__(".global InspectEquipmentMode0\n.thumb_set InspectEquipmentMode0, 0x080cb48d");


/* Build the eligible equipment choices and preserve caller-initialized flags. */
void BuildEligibleEquipmentChoices(struct ItemListContext *) asm("Source52_00027800");
void BuildEligibleEquipmentChoices(struct ItemListContext *context)
{
    u8 empty_slot = 0;
    struct ListDescriptor *list = &context->list;
    s32 index;
    s32 inventory_count;
    s32 choice_count;
    struct InventoryRecord *entry;
    u8 *resource_buffer;

    resource_buffer = AllocateContextBuffer(192);
    context->resource_buffer = resource_buffer;
    resource_buffer += 128;
    LoadResourceRange(gItemListResource, resource_buffer, 32, 1);
    for (index = 0; index < 5; index++) {
        if (gActiveSelection->unit->equipment[index] == 0) {
            empty_slot = index;
            break;
        }
    }
    entry = GetInventoryPartition(0, &inventory_count);
    choice_count = 0;
    for (index = 0; index < inventory_count; index++, entry++) {
        if (IsItemIdInRange1To252(entry->item_id)
            && entry->owned_count != 0
            && UnitItemCategoryAllowed(gActiveSelection->unit, entry->item_id)) {
            context->item_ids[choice_count] = entry->item_id;
            if (entry->owned_count == entry->reserved_count
                || InspectEquipmentMode0(gActiveSelection->unit, entry->item_id, empty_slot))
                context->availability[choice_count] = 0;
            choice_count++;
        }
    }
    {
        /* The actual R1 snapshot precedes storage narrowing and stays live
         * through the independent halfword count test. */
        register s32 visible_count asm("r1") = choice_count;
        asm("" : "+r" (visible_count));
        list->count = choice_count;
        if (list->count <= 5) {
            list->visible_count = visible_count;
            /* Preserve the original zero-count predecessor lookup. */
            list->layout = gSmallListLayouts[list->count - 1];
        }
    }
}
