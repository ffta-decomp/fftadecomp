/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/0808A1EC.c
 * Original SHA-256: 29635cb1bface87d2662e9224dfb2e5096635137112e44245c7d5acb70658d3e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

typedef struct {
    u32 enabled : 1;
    u32 unknown_00_1 : 2;
    u32 palette : 4;
    u32 unknown_00_7 : 1;
    u32 mode : 2;
    u32 plane : 1;
    u32 unknown_01_3 : 2;
    u32 dirty : 1;
    u32 unknown_01_6 : 2;
    u8 unknown_002[0x10B];
    u8 index;
    u8 unknown_10e[2];
    u8 width;
    u8 count;
} MenuPanel;

typedef struct {
    u32 unknown_00;
    void *surface;
} RenderState;

extern RenderState data_03000E30;
extern const u8 data_08950D38[];
extern const u8 data_089514F4[];
extern void func_0804C4D4(void *surface, u16 index, u16 selector,
    u8 width, u8 count, u8 mode, u8 delay,
    const u8 *graphics, const u8 *layout, u16 attributes);

/* 0x0808A1EC..0x0808A268: 124 bytes, 51 instructions. */
void func_0808A1EC(MenuPanel *panel)
{
    panel->dirty = 0;
    panel->enabled = 1;
    if (panel->mode == 1) {
        func_0804C4D4(data_03000E30.surface, panel->index,
            panel->plane + 2, panel->width, panel->count, panel->mode,
            panel->palette, data_08950D38, data_089514F4, 0x120);
    }
}
