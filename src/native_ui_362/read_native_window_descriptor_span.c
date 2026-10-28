typedef unsigned char u8;
typedef unsigned int u32;
struct NativeWindowDescriptor {u8 span,unknown01[3];};
extern const struct NativeWindowDescriptor *GetNativeWindowDescriptor(u32) asm("RetailCall_08018518");
u32 ReadNativeWindowDescriptorSpan(u32) asm("Remaining38_000185B8");
u32 ReadNativeWindowDescriptorSpan(u32 index)
{
    return GetNativeWindowDescriptor((u8)index)->span;
}
__asm__(".global RetailCall_08018518\n.thumb_set RetailCall_08018518,0x08018519");
