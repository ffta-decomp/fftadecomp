typedef unsigned char u8;
typedef unsigned short u16;
struct ChoiceSlot { u16 first; u16 second; };
struct SelectionContext {
    u8 prefix[0xA04];
    struct ChoiceSlot slots[0];
};
typedef void (*ClearCallback)(void *, unsigned);
extern struct SelectionContext *selection_context;
extern ClearCallback clear_callback;
extern void InvokeClearCallback(void *, unsigned, ClearCallback);
__asm__(".global selection_context\n.set selection_context,0x0200f454\n"
        ".global clear_callback\n.set clear_callback,0x0836d4b8\n"
        ".global InvokeClearCallback\n.thumb_set InvokeClearCallback,0x0814224d");

void ClearCategorySelection(u8 category) __asm__("RemainingCore48_00066120");
void ClearCategorySelection(u8 category)
{
    struct SelectionContext **context_cell = &selection_context;
    unsigned slot_offset;
    struct SelectionContext *context;
    struct ChoiceSlot *slot;
    /* The original address of the context cell is defined before the slot offset. */
    __asm__("" : "+r"(context_cell));
    slot_offset = (unsigned)category * 4 + 0xA04;
    context = *context_cell;
    slot = (struct ChoiceSlot *)((u8 *)context + slot_offset);
    slot->first = 0;
    slot->second = 0;
    if (category == 4) {
        ((u8 *)context)[9] = 0;
        {
            ClearCallback *callback_cell = &clear_callback;
            u8 *destination = (u8 *)*context_cell + 0xA24;
            InvokeClearCallback(destination, 24, *callback_cell);
        }
    }
}
