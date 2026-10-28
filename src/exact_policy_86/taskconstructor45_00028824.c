/* Method-local interface declarations from the frozen build. */
#ifndef SELECTION_RECORD_CODE_INTERFACES_H
#define SELECTION_RECORD_CODE_INTERFACES_H
typedef unsigned char u8; typedef unsigned short u16; typedef signed short s16; typedef unsigned int u32;
union SelectionCell { u32 word; u16 half[2]; };
struct SelectionContext { u8 unknown0[10]; u8 selector; u8 unknown11[137]; union SelectionCell *cells; };
struct SelectionRoot { u8 unknown0[4]; u8 kind; u8 unknown5[1147]; u8 categories[0]; };
struct AbilityName { u16 unknown0, code; u8 unknown4[4]; };
struct PackedCode { u8 unknown0[2], low, high; };
extern struct SelectionRoot *gCodeSelectionRoot;
extern const struct AbilityName *const gAbilityNameLists[];
extern const u16 gCatalogCodes[],gOtherCodes[];
extern const struct PackedCode gPackedCodes[];
extern u32 GetItemProperty(u16,u8);
__asm__(".global gCodeSelectionRoot\n.set gCodeSelectionRoot,0x0200f438\n.global gAbilityNameLists\n.set gAbilityNameLists,0x0851ba84\n.global gCatalogCodes\n.set gCatalogCodes,0x0852a13e\n.global gOtherCodes\n.set gOtherCodes,0x0852a212\n.global gPackedCodes\n.set gPackedCodes,0x08527244\n.global GetItemProperty\n.thumb_set GetItemProperty,0x080ca7a5");
typedef char check_cell4[sizeof(union SelectionCell)==4?1:-1];
typedef char check_name8[sizeof(struct AbilityName)==8?1:-1];
typedef char check_cellsoffset[(u32)&((struct SelectionContext *)0)->cells==148?1:-1];
#endif

u16 ResolveSelectionRecordCode(struct SelectionContext *context, u16 index)
{
    u16 result = 0;
    switch (gCodeSelectionRoot->kind) {
    case 6:
    case 7:
    case 8:
    case 15: {
        const struct AbilityName *list = gAbilityNameLists[context->selector];
        list += context->cells[(s16)index].word;
        result = list->code + 1;
        break;
    }
    case 1:
    case 4:
    case 10:
        result = gCatalogCodes[context->cells[(s16)index].word] + 1;
        break;
    case 5:
        switch (gCodeSelectionRoot->categories[(s16)index]) {
        case 12:
        case 16:
        case 17:
            result = gCatalogCodes[context->cells[(s16)index].word] + 1;
            break;
        default: {
            const struct PackedCode *record = &gPackedCodes[context->cells[(s16)index].word];
            u32 low = record->low;
            result = ((record->high << 8) | low) + 1;
            break;
        }
        }
        break;
    case 3:
        result = gOtherCodes[context->cells[(s16)index].word] + 1;
        break;
    case 13:
    case 14:
        result = GetItemProperty(context->cells[(s16)index].half[0], 1) + 1;
        break;
    case 2:
    case 9:
    case 11:
    case 12:
    case 16:
    case 17:
        break;
    }
    return result;
}
