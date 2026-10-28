/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
struct ListContext { u8 prefix[10]; u8 ability_list; u8 gap[137]; u32 *rows; u8 unknown[8]; const u8 *direct[0]; };
struct SelectionRoot { u8 prefix[4]; u8 kind; u8 gap[1147]; u8 categories[0]; };
struct PackedNameRecord { u8 low,high,unknown[2]; };
struct AbilityEntry { u16 name; u8 rest[6]; };
extern struct SelectionRoot *gSelectionRoot;
extern const struct AbilityEntry *const gAbilityLists[];
extern const u8 *const gCatalogTexts[], *const gItemNames[];
extern const struct PackedNameRecord gRecordNames[];
extern u32 ReadUnitField(const void*,u8), GetItemProperty(u16,u8);
extern const u8 *ResolveEquipmentCategoryName(u16);
__asm__(".global gSelectionRoot\n.set gSelectionRoot,0x0200F438");
__asm__(".global gAbilityLists\n.set gAbilityLists,0x0851BA84");
__asm__(".global gCatalogTexts\n.set gCatalogTexts,0x085567F0");
__asm__(".global gItemNames\n.set gItemNames,0x08526680");
__asm__(".global gRecordNames\n.set gRecordNames,0x08527244");
__asm__(".global ResolveEquipmentCategoryName\n.thumb_set ResolveEquipmentCategoryName,0x080CB4E1");

/* Select the encoded label for the active game record list. */
const u8 *ResolveSelectionRecordLabel(struct ListContext *context, s16 index)
{
    switch (gSelectionRoot->kind) {
    case 6:
    case 7:
    case 8:
    case 15: {
        const struct AbilityEntry *list = gAbilityLists[context->ability_list];
        const struct AbilityEntry *entry = &list[context->rows[index]];
        return gCatalogTexts[entry->name];
    }
    case 1:
    case 4:
    case 10:
        return gCatalogTexts[context->rows[index]];
    case 5: {
        int category = gSelectionRoot->categories[index];
        switch (category) {
        case 12:
        case 16:
        case 17:
            return gCatalogTexts[context->rows[index]];
        default: {
            const u8 *const *texts = gCatalogTexts;
            const struct PackedNameRecord *record = &gRecordNames[context->rows[index]];
            u32 low = record->low;
            return texts[(record->high << 8) | low];
        }
        }
    }
    case 12:
        return context->direct[0];
    case 2:
        return (const u8*)ReadUnitField((const void*)context->rows[index],0);
    case 3:
        return ResolveEquipmentCategoryName(*(u16*)&context->rows[index]);
    case 13:
    case 14:
        return gItemNames[GetItemProperty(*(u16*)&context->rows[index],0)];
    default:
        return gItemNames[context->rows[index]];
    }
}
