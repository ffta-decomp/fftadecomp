typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct NativeWindowSurface {
    u16 *first_buffer;
    u16 *second_buffer;
    u8 opaque08[8];
    u8 origin_x, origin_y, width, height;
    u16 layout_flags;
    u8 stride, palette;
    u16 first_tile, second_tile;
    u8 update_flags;
    u8 opaque29[2];
    u8 alignment_mode;
    u16 current_width, current_height;
    s16 target_width, target_height;
} NativeWindowSurface;
extern void PrepareNativeWindowFrame(NativeWindowSurface *) asm("RetailCall_08016FE4");
extern void AdvanceNativeWindowDimensions(NativeWindowSurface *) asm("RetailCall_08016B50");
extern u32 GetNativeWindowCellOffset(u32,u32,u32) asm("RetailCall_080161A0");
extern void ClearNativeWindowRows(void *,u32,u32,u32,u32) asm("RetailCall_08016A98");
extern void RenderNativeWindowRectangle(void *,void *,u32,u32,u32,u32,u32,u32,u32) asm("RetailCall_08016268");
extern void WriteNativeWindowDescriptors(NativeWindowSurface *,u32,u32) asm("RetailCall_08016E88");
u32 RefreshNativeWindowFrame(NativeWindowSurface *) asm("SceneTaskDependency_00017180");
u32 RefreshNativeWindowFrame(NativeWindowSurface *surface)
{
    u8 origin_y;
    u16 width, height;
    u16 cell_offset;
    u32 offset_bytes;
    u32 ready;
    u8 update_flags;
    u32 clear_mask;
    if (!(surface->update_flags & 4))
        PrepareNativeWindowFrame(surface);
    AdvanceNativeWindowDimensions(surface);
    origin_y = surface->origin_y;
    width = surface->current_width;
    height = surface->current_height;
    {
        u32 origin_x = surface->origin_x;
        register u32 row_argument asm("r1") = origin_y;
        __asm__("" : "+r"(row_argument));
        cell_offset = GetNativeWindowCellOffset(origin_x, row_argument, surface->stride);
    }
    if (surface->alignment_mode & 1)
        cell_offset += (surface->width - width) >> 1;
    else if (surface->alignment_mode & 2)
        cell_offset += surface->width - width;
    update_flags = surface->update_flags;
    clear_mask = update_flags & 4;
    offset_bytes = cell_offset * 2;
    if (clear_mask && width > 2 && height > 2) {
        u32 style_mask = 8;
        __asm__("" : "+r"(style_mask));
        if (style_mask & surface->update_flags) {
            u32 clear_offset = (u16)GetNativeWindowCellOffset(
                0, (u8)(origin_y - 1), surface->stride) * 2;
            ClearNativeWindowRows((u8 *)surface->first_buffer + clear_offset,
                30, (u8)(surface->target_height + 2), 0, surface->stride);
            ClearNativeWindowRows((u8 *)surface->second_buffer + clear_offset,
                30, (u8)(surface->target_height + 2), 0, surface->stride);
        } else {
            ClearNativeWindowRows((u8 *)surface->first_buffer + offset_bytes,
                (u8)width, (u8)height, 0, surface->stride);
        }
    }
    if (surface->second_buffer) {
        RenderNativeWindowRectangle((u8 *)surface->first_buffer + offset_bytes,
            (u8 *)surface->second_buffer + offset_bytes, (u8)width, (u8)height,
            surface->layout_flags, surface->stride, surface->first_tile,
            surface->second_tile, surface->palette);
    } else {
        RenderNativeWindowRectangle((u8 *)surface->first_buffer + offset_bytes,
            0, (u8)width, (u8)height,
            surface->layout_flags, surface->stride, surface->first_tile,
            surface->second_tile, surface->palette);
    }
    WriteNativeWindowDescriptors(surface, cell_offset, (u8)width);
    ready = 0;
    if (width == surface->target_width && height == surface->target_height)
        ready = 1;
    return ready;
}
__asm__(".global RetailCall_08016FE4\n.thumb_set RetailCall_08016FE4,0x08016FE5\n"
        ".global RetailCall_08016B50\n.thumb_set RetailCall_08016B50,0x08016B51\n"
        ".global RetailCall_080161A0\n.thumb_set RetailCall_080161A0,0x080161A1\n"
        ".global RetailCall_08016A98\n.thumb_set RetailCall_08016A98,0x08016A99\n"
        ".global RetailCall_08016268\n.thumb_set RetailCall_08016268,0x08016269\n"
        ".global RetailCall_08016E88\n.thumb_set RetailCall_08016E88,0x08016E89");
