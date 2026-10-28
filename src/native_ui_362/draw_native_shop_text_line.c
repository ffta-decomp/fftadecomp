typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct NativeShopTextList { u8 unknown00[21]; u8 width; };
struct NativeShopTextBuffers { u8 unknown00[16]; u8 *buffer; };
extern u32 GetNativeShopTileOffset(struct NativeShopTextList *, s32);
extern void ClearNativeShopTextCells(void *, u16);
extern u32 ProcessNativeShopText(void *, u32, const u8 *, u32, u32);
__asm__(".global GetNativeShopTileOffset\n.thumb_set GetNativeShopTileOffset,0x08017B9D\n"
        ".global ClearNativeShopTextCells\n.thumb_set ClearNativeShopTextCells,0x08013A89\n"
        ".global ProcessNativeShopText\n.thumb_set ProcessNativeShopText,0x08015111\n");
void DrawNativeShopTextLine(const u8 *, struct NativeShopTextList *, s8, u8)
    __asm__("SceneTaskDependency_0006E60C");
void DrawNativeShopTextLine(const u8 *text, struct NativeShopTextList *list, s8 row, u8 mode)
{
    u32 offset = GetNativeShopTileOffset(list, row);
    struct NativeShopTextBuffers *buffers = (struct NativeShopTextBuffers *)0x03000990;
    u8 *buffer = buffers->buffer + ((u32)(u16)offset << 5);
    ClearNativeShopTextCells(buffer, list->width * 2);
    ProcessNativeShopText(*(u8 **)0x0200F428 + 0x39F4, (u32)buffer, text, mode, 1);
}
