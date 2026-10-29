/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0807408C.c
 * Original SHA-256: 44354e4e5e650f5bd1e47dda602a88f2776d3647bafbce1c4f930990d1a62f07
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u8 unknown_00[0x0C];
    u16 *large_second;
    u16 *large_first;
    u16 *small_second;
    u16 *small_first;
} ResourceContext;

extern ResourceContext *data_03002818;
extern u16 data_06007000[];
extern u16 data_06006000[];
extern u16 data_06005800[];
extern u16 data_06005000[];

extern void func_0808A268(u32 index, u32 mode, u16 *first_resource,
    u16 *second_resource, u16 *first_tiles, u16 *second_tiles,
    u32 first_offset, u32 second_offset, u32 x, u32 y, u32 width, u32 height,
    u32 source_x, u32 source_y, u32 source_width, u32 source_height,
    u32 stride, u32 rows);
extern void func_080894AC(u32 first, u32 second, u32 count);

/* 0x0807408C..0x0807411C: 144 bytes, 58 instructions. */
void func_0807408C(void)
{
    func_0808A268(0, 3, data_03002818->large_first,
        data_03002818->large_second, data_06007000, data_06006000,
        0, 0, 0, 0, 32, 64, 0, 0, 32, 64, 32, 64);
    func_0808A268(1, 12, data_03002818->small_first,
        data_03002818->small_second, data_06005800, data_06005000,
        0, 0, 0, 0, 32, 32, 0, 0, 32, 32, 32, 32);
    func_080894AC(0, 0, 2);
}
