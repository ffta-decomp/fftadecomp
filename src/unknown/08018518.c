typedef unsigned char u8;
typedef unsigned int u32;
struct NativeWindowDescriptor {u8 span,unknown01[3];};
extern const struct NativeWindowDescriptor gNativeWindowDescriptors[];
const struct NativeWindowDescriptor *GetNativeWindowDescriptor(u32) asm("CoreFrontier_00018518");
const struct NativeWindowDescriptor *GetNativeWindowDescriptor(u32 index)
{
    /* Original uses a wrapping full-word byte displacement, without narrowing
     * the index or dereferencing a table pointer. */
    u32 address=index*4;
    address+=(u32)gNativeWindowDescriptors;
    return (const struct NativeWindowDescriptor*)address;
}
__asm__(".global gNativeWindowDescriptors\n.set gNativeWindowDescriptors,0x0836d6e4");
