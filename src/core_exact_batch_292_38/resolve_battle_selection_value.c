typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

struct ActiveSelection {
    u16 ordinal;
    u8 preceding_selector[2];
    u8 selector;
    u8 preceding_value[15];
    u32 selected_value;
    u8 preceding_codes[1128];
    u8 codes[0];
};

struct SelectionStatus {
    u8 preceding_flags[148];
    u16 flags;
};

extern struct ActiveSelection *gActiveSelection;
extern struct SelectionStatus gSelectionStatus;
__asm__(".global gActiveSelection\n.set gActiveSelection,0x0200f438\n"
        ".global gSelectionStatus\n.set gSelectionStatus,0x0200f390\n");

typedef char selection_value_offset[
    ((u32)&((struct ActiveSelection *)0)->selected_value == 20) ? 1 : -1];
typedef char selection_codes_offset[
    ((u32)&((struct ActiveSelection *)0)->codes == 1152) ? 1 : -1];

/* Ordinal zero wraps to 65535 before the case-specific additions. The original
 * does not establish the bounds of the code list or names of selector modes. */
u32 ResolveBattleSelectionValue(void)
{
    struct ActiveSelection *entry = gActiveSelection;
    u16 index;

    if (entry->selector == 0)
        return 0;
    index = entry->ordinal - 1;
    switch (entry->selector) {
    case 4:
        return index + 7;
    case 1:
    case 5:
    case 17:
        return gActiveSelection->codes[index];
    case 10:
        return 10;
    case 11:
        return index + 18;
    case 3:
        return index;
    case 2:
    case 6:
    case 7:
    case 8:
    case 13:
    case 14:
        {
            register u32 selected_value asm("r0") = gActiveSelection->selected_value;
            /* This original case-owned loaded value has a distinct return phase. */
            asm("" : "+r"(selected_value));
            return selected_value;
        }
    case 15:
        if ((gSelectionStatus.flags & 0x20) == 0)
            return gActiveSelection->selected_value;
        return 33;
    }
    return 0;
}
