typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct NativeShopGridBuffer {
    u8 unknown00[12];
    void *buffer;
    u8 unknown16[5];
    u8 dimension_a;
    u8 dimension_b;
    u8 dimension_b_plus_one;
    u16 unknown24;
    u16 cleared26;
};
extern void FillNativeShopHalfwords(const void *, void *, u32);
__asm__(".global FillNativeShopHalfwords\n.thumb_set FillNativeShopHalfwords,0x0814186D\n");
void ResetNativeShopGridBuffer(struct NativeShopGridBuffer *grid)
    __asm__("SceneTaskDependency_0006F67C");
void ResetNativeShopGridBuffer(struct NativeShopGridBuffer *grid)
{
    u16 zero;
    grid->dimension_b_plus_one = grid->dimension_b + 1;
    grid->cleared26 = 0;
    zero = 0;
    FillNativeShopHalfwords(&zero, grid->buffer,
        ((grid->dimension_a * grid->dimension_b) << 1) | 0x01000000);
}
