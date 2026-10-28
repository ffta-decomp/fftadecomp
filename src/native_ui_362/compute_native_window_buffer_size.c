typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
u16 GetNativeWindowBufferBytes(u32, u32, u32) asm("CoreDependency29_00013B08");
u16 GetNativeWindowBufferBytes(u32 width_input, u32 height_input, u32 flags_input)
{
    u32 width_top = width_input << 24;
    u32 height_top = height_input << 24;
    u32 flags = (u16)flags_input;
    u32 width = width_top >> 24;
    u32 height = height_top >> 24;
    u32 layout_mask = flags & 0xC20;
    if (!(flags & 2))
        width = (u8)(width - 2);
    if (flags & 4)
        height = (u8)(height + 2);
    if (!layout_mask)
        height = (u8)(height - 1);
    return (u16)(width * height * 2);
}
