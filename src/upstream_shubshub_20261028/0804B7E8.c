/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804B7E8.c
 * Original SHA-256: 1e37d83230ea085604de7e52deb9ee55e214f1e29e5df915f3175ee9ae8efb5d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x32];
    u8 mode;
    u8 state;
    u8 selection;
    u8 timer;
    u8 unknown_36[0x92];
    void *data;
} MenuRecord0804B7E8;

typedef struct {
    u8 unknown_000[0x4B8];
    u8 active[6];
    u8 pending[6];
    u8 unknown_4C4[0x490];
    MenuRecord0804B7E8 records[1];
} MenuState0804B7E8;

typedef struct {
    u8 active;
    u8 unknown_01[4];
    u8 mode;
    u8 unknown_06[0x46];
} Unit0804B7E8;

extern MenuState0804B7E8 *g_state_03002810;
extern Unit0804B7E8 data_030009E0[];
extern u8 data_0201F53A;
extern u8 data_0201F53B;

extern void func_0804B95C(void *data, u8 selection);
extern void func_0804A4CC(s32 index, u8 selection);
extern s32 func_08043120(s32 index);
extern void func_08141540(s32 sound);
extern void func_0808A604(s32 unit, s32 action);

/* 0x0804B7E8..0x0804B95A: 370 bytes, including literal pools. */
void func_0804B7E8(s32 index)
{
    switch (g_state_03002810->records[index].state) {
    case 0:
        g_state_03002810->pending[index] = 0;
        func_0804B95C(g_state_03002810->records[index].data,
                      g_state_03002810->records[index].selection);
        func_0804A4CC(index, g_state_03002810->records[index].selection);
        g_state_03002810->records[index].timer = 5;
        g_state_03002810->records[index].state = 3;
        break;
    case 1:
        {
            s32 result = func_08043120(index);

            if (result == 0xFF) {
                func_08141540(0x69);
                data_0201F53B = 6;
                data_030009E0[data_0201F53B].mode = 2;
                func_0808A604(6, 13);
                data_0201F53A = result;
                g_state_03002810->records[index].state = 2;
            } else if (result == 3) {
                func_0808A604(6, 2);
            }
        }
        break;
    case 2:
        if (data_030009E0[data_0201F53B].active == 0)
            g_state_03002810->records[index].state = data_0201F53A;
        break;
    case 3:
        func_08043120(index);
        if (g_state_03002810->records[index].mode == 3) {
            data_0201F53B = 6;
            data_030009E0[data_0201F53B].mode = 2;
            func_0808A604(6, 11);
            data_0201F53A = 1;
            g_state_03002810->records[index].state = 2;
        }
        break;
    case 0xFF:
        g_state_03002810->active[index] = 0;
        break;
    }
}
