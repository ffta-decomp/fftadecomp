typedef unsigned char u8;
struct SelectionContext { u8 prefix[16]; const void *selected_record; };
extern struct SelectionContext *selection_context;
__asm__(".global selection_context\n.set selection_context,0x0200f454");
const void *GetStoredSelectedRecord(void) __asm__("RemainingCore48_00066114");
const void *GetStoredSelectedRecord(void)
{
    return selection_context->selected_record;
}
