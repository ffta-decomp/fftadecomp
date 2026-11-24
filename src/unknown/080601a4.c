typedef unsigned int u32;

extern u32 SelectionValueForIndex(u32 index, u32 mode);
__asm__(".global SelectionValueForIndex\n.thumb_set SelectionValueForIndex,0x08060155");

u32 CoreRegion30_000601A4(u32 ignored_context, u32 selection_index)
{
    (void)ignored_context;
    return SelectionValueForIndex(selection_index, 0);
}
