typedef unsigned char u8;
typedef unsigned int u32;
struct ResourceHandleView {
    u32 flags;
    u8 reserved[36];
    void *resource;
};
typedef char ResourceOffset[(u32)&(((struct ResourceHandleView *)0)->resource)==40?1:-1];
void *ReadExistingResourceFlags(struct ResourceHandleView *handle,
                                 u8 *horizontal_flag, u8 *vertical_flag)
{
    u32 flags = handle->flags;
    void *resource;
    if (flags & 64) {
        u32 first_axis = (flags >> 3) & 1;
        u32 second_axis = (flags >> 5) & 1;
        /* Both single-bit operands exist before the original XOR. This empty
         * input-only constraint prevents combining their masks across it. */
        asm("" : : "r"(first_axis), "r"(second_axis));
        *horizontal_flag = second_axis ^ first_axis;
        *vertical_flag = (flags >> 4) & 1;
        resource = handle->resource;
    } else {
        resource = 0;
    }
    return resource;
}
