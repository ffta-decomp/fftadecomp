/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08038324.c
 * Original SHA-256: 4263c962bf19f560787150e04cc4e24db9db8621f3332162ff90486128b780e7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
/* Complete [0x08038324, 0x080384F0): 460 bytes.
 * Conditional ordinary helper transport and local BIOS source units.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct {
    u8 unknown_00[0x88];
    void *field_88;
    void *field_8C;
    void *field_90;
    void *field_94;
} Resources;

typedef struct {
    u8 unknown_00[8];
    u8 *first;
    u8 *second;
} TileStorage;

typedef struct {
    u8 unknown_00[0x1C];
    u16 *second_plane;
    u8 unknown_20[0x2C];
} Window;

typedef struct {
    u8 unknown_00[0x2E58];
    u8 flags;
} SceneState;

extern Resources *g_state_03002810;
extern TileStorage data_03002740;
extern Window data_030009E0[];
extern u8 g_state_02000000[];
extern u8 data_06005000[], data_06006000[];
extern u8 data_06007000[], data_06007800[];
extern const u16 data_0895527C[], data_08955250[];
extern const u8 data_08951588[], data_089542A0[], data_08954B4C[];

void *func_0808A268(s32 index, u8 kind, void *first, void *second,
                    void *third, void *fourth, void *fifth, void *sixth,
                    u8 x, u8 y, u8 width, u8 height,
                    u32 x2, u32 y2, u32 width2, u32 height2,
                    u8 row_width, u8 row_height);
void func_08035578(const u16 *source, u16 *destination, u32 count, u16 offset);
void func_0814186C(const void *source, void *destination, u32 control);
void func_0814188C(const void *source, void *destination);
void func_08038B00(void);
void func_08038B2C(void);

void func_08038324(void)
{
    u16 zero_second;
    u16 zero_first;
    SceneState *state;

    func_0808A268(0, 3, g_state_03002810->field_8C,
                    g_state_03002810->field_88,
                    data_06005000, data_06006000, 0, 0,
                    0, 0, 32, 64, 0, 0, 32, 64, 32, 64);
    func_0808A268(1, 12, g_state_03002810->field_94,
                    g_state_03002810->field_90,
                    data_06007000, data_06007800, 0, 0,
                    0, 0, 32, 32, 0, 0, 32, 32, 32, 32);
    func_0808A268(2, 12, g_state_03002810->field_94,
                    g_state_03002810->field_90,
                    data_03002740.first, data_03002740.first + 0x3C, 0, 0,
                    0, 17, 10, 3, 0, 17, 10, 3, 10, 3);
    func_0808A268(3, 12, g_state_03002810->field_94,
                    g_state_03002810->field_90,
                    data_03002740.second, data_03002740.second + 0x2C, 0, 0,
                    19, 18, 11, 2, 19, 18, 11, 2, 11, 2);
    func_08035578(data_0895527C, data_030009E0[2].second_plane, 30, 132);
    func_08035578(data_08955250, data_030009E0[3].second_plane, 22, 149);
    func_0814188C(data_08951588, (void *)0x06000000);
    zero_second = 0;
    func_0814186C(&zero_second, g_state_03002810->field_8C, 0x01000400);
    func_0814188C(data_089542A0, g_state_03002810->field_8C);
    zero_first = 0;
    func_0814186C(&zero_first, g_state_03002810->field_88, 0x01000400);
    func_0814188C(data_08954B4C, g_state_03002810->field_88);
    state = (SceneState *)g_state_02000000;
    if (state->flags & 1)
        func_08038B00();
    if (state->flags & 2)
        func_08038B2C();
}
