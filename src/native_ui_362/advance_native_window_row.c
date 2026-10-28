typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
typedef struct NativeWindowScrollPrefix {
    u8 opaque00[26];
    u16 row_offset;
} NativeWindowScrollPrefix;
extern u32 CanAdvanceNativeWindowRow(NativeWindowScrollPrefix *,u32) asm("RetailCall_08017A90");
s32 AdvanceNativeWindowRow(NativeWindowScrollPrefix *,u32) asm("CoreDependency29_0001784C");
s32 AdvanceNativeWindowRow(NativeWindowScrollPrefix *window, u32 input_mask)
{
    u16 mask = input_mask;
    if (!(u8)CanAdvanceNativeWindowRow(window, mask))
        return -1;
    if (mask == 128)
        window->row_offset++;
    else
        window->row_offset--;
    return (s16)(window->row_offset * 2);
}
__asm__(".global RetailCall_08017A90\n.thumb_set RetailCall_08017A90,0x08017A91");
