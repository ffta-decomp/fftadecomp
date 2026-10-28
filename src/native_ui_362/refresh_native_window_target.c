typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef struct NativeWindowSurface {
    u16 *first_buffer;
    u16 *second_buffer;
    u8 unknown08[8];
    u8 origin_x, origin_y, width, height;
    u16 flags20;
    u8 stride, rows;
    u16 unknown24, unknown26;
    u8 flags28;
    u8 unknown29[3];
    u16 current_width, current_height;
    s16 target_width, target_height;
} NativeWindowSurface;
extern u32 GetNativeWindowCellOffset(u32,u32,u32) asm("RetailCall_080161A0");
extern void ClearNativeWindowRows(void *,u32,u32,u32,u32) asm("RetailCall_08016A98");
extern void CopyNativeWindowRows(void *,u32,u32,u32) asm("RetailCall_08016A08");
u32 RefreshNativeWindowTargetSize(NativeWindowSurface *) asm("TaskConstructor45_000172F0");
u32 RefreshNativeWindowTargetSize(NativeWindowSurface *surface)
{
    u16 width, height;
    u32 offset_bytes;
    u8 *destination;
    u32 ready;
    if (!(surface->flags28 & 4)) {
        u32 clear_offset = (u16)GetNativeWindowCellOffset(
            surface->origin_x, surface->origin_y, surface->stride) * 2;
        ClearNativeWindowRows((u8 *)surface->first_buffer + clear_offset,
            surface->width, surface->height, 0, surface->stride);
        ClearNativeWindowRows((u8 *)surface->second_buffer + clear_offset,
            surface->width, surface->height, 0, surface->stride);
    }
    surface->current_width = (u16)surface->target_width;
    surface->current_height = (u16)surface->target_height;
    width = surface->current_width;
    height = surface->current_height;
    offset_bytes = (u16)GetNativeWindowCellOffset(
        surface->origin_x, surface->origin_y, surface->stride) * 2;
    destination = (u8 *)surface->second_buffer + offset_bytes;
    CopyNativeWindowRows(destination, (u8)width, (u8)height, surface->stride);
    ready = 0;
    if (width == surface->target_width && height == surface->target_height)
        ready = 1;
    return ready;
}
__asm__(".global RetailCall_080161A0\n.thumb_set RetailCall_080161A0,0x080161A1");
__asm__(".global RetailCall_08016A98\n.thumb_set RetailCall_08016A98,0x08016A99");
__asm__(".global RetailCall_08016A08\n.thumb_set RetailCall_08016A08,0x08016A09");
