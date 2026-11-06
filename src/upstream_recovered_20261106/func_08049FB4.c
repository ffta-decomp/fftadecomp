/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/08049FB4.c
 * Original SHA-256: c0420e06a2650895bbccc248cbf3d05cb357861bc67a79f4e6fe3f713b1fecef
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

/* Complete target [0x08049FB4, 0x0804A15C), 424 bytes.
 * Local offset views do not establish original declarations or object bounds.
 */
typedef struct {
    u8 unknown_00[0x32];
    u8 phase;
    u8 panel_phase;
    u8 selection;
    u8 unknown_35[9];
    u16 row_mode;
    u8 unknown_40[0x88];
    void *panel;
} MenuRecord;

typedef struct {
    u8 unknown_000[0x4BE];
    u8 entry_flags[1];
    u8 unknown_4BF[0x495];
    MenuRecord records[1];
} MenuContext;

typedef struct {
    u8 active;
    u8 unknown_01[4];
    u8 transition_speed;
    u8 unknown_06[0x12];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown_20[0x2C];
} TileWindow;

extern MenuContext *g_state_03002810;
extern u8 data_02003CB0[];
extern u8 data_0201F534;
extern u8 data_0201F535;
extern TileWindow data_030009E0[];

/* Conditional transport views from this caller and complete helper entries. */
extern s32 func_08049E10(void *, u8);
extern void func_08049C24(u32, u32, u32);
extern u16 *func_0808B8E4(u32, u32, u32, u32);
extern u32 func_08018524(void *, u16, u8);
extern void func_08035678(u16, u16 *, u32, u16);
extern u32 func_08040388(u32, u16);
extern u32 func_0808A604(u32, u16);

void func_08049FB4(u32 index)
{
    switch (g_state_03002810->records[index].panel_phase) {
    case 0: {
        s32 count;
        u8 *text = data_02003CB0;

        g_state_03002810->entry_flags[index] = 0;
        count = func_08049E10(g_state_03002810->records[index].panel,
                            g_state_03002810->records[index].selection);
        if (count > 6)
            func_08049C24(index, 15, 1);
        else
            func_08049C24(index, (count % 7) * 2 + 3, 0);
        func_08035678(0xC03E, func_0808B8E4(4, 1, 1, 1),
                      func_08018524(text, 62, 10), 1);
        data_0201F534 = 1;
        g_state_03002810->records[index].panel_phase = 3;
        break;
    }
    case 1:
        if (func_08040388(index, 1) == 3 &&
            g_state_03002810->records[index].row_mode == 1) {
            data_0201F535 = 4;
            data_030009E0[data_0201F535].transition_speed = 3;
            func_0808A604(4, 12);
            data_0201F534 = 0xFF;
            g_state_03002810->records[index].panel_phase = 2;
        } else {
            func_0808A604(4, 2);
        }
        break;
    case 2:
        if (data_030009E0[data_0201F535].active == 0)
            g_state_03002810->records[index].panel_phase = data_0201F534;
        break;
    case 3:
        if (func_08040388(index, 0) == 3)
            g_state_03002810->records[index].panel_phase = data_0201F534;
        break;
    case 0xFF:
        g_state_03002810->records[index].phase = 0xFF;
        break;
    }
}
