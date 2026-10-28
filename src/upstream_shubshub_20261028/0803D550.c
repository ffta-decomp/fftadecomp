/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0803D550.c
 * Original SHA-256: 883e29ee91c7dd414cd3dbd10d279bccc03f0824490639d1c0797eb80630205e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00 : 5;
    u8 flag_20 : 1;
    u8 flag_40 : 1;
    u8 unknown_07 : 1;
} MenuWindow;

typedef struct {
    u16 unknown_00;
    u8 result;
    u8 state;
    u8 unknown_04[10];
    u16 buttons;
    u8 unknown_10[0x88];
    void *source;
    u8 unknown_9c[0x30];
} MenuSlot;

typedef struct {
    void *owner;
    MenuWindow *window;
    u8 unknown_08[0x4b8 - 8];
    u8 closed[6];
    u8 active[6];
    u8 unknown_4c4[0x685 - 0x4c4];
    u8 mode;
    u8 unknown_686[0x984 - 0x686];
    MenuSlot slots[1];
} MenuContext;

typedef struct {
    u8 busy;
    u8 unknown_01;
    u8 flags;
    u8 unknown_03[2];
    u8 status;
    u8 unknown_06[0x46];
} RenderObject;

extern MenuContext *g_state_03002810;
extern RenderObject data_030009E0[];
extern u8 data_0201F48A;
extern u8 data_0201F48B;
extern void func_08141540(u32 sound);
extern void func_08035844(u32 mode);
extern s32 func_0803D320(void *source);
extern void func_0803D3DC(void);
extern void func_08037C84(s32 slot, void *source, u32 mode, u32 a3,
                         u32 a4, u32 a5, u32 flags, u32 a7);
extern u32 func_08040F38(s32 slot, u16 mask);
extern void func_0808A604(u32 object, u32 command);

/* Complete target: [0x0803D550, 0x0803D820), 720 bytes. */
void func_0803D550(s32 slot)
{
    switch (g_state_03002810->slots[slot].state) {
    case 0: {
        s32 count;
        func_08141540(100);
        g_state_03002810->window->flag_20 = 0;
        g_state_03002810->window->flag_40 = 0;
        func_08035844(0);
        count = func_0803D320(g_state_03002810->slots[slot].source);
        func_0803D3DC();
        data_030009E0[4].flags &= 0x7f;
        g_state_03002810->active[slot] = 0;
        if (count <= 6)
            func_08037C84(slot, g_state_03002810->slots[slot].source,
                          4, 0, 0, 0, 0x83, 1);
        else
            func_08037C84(slot, g_state_03002810->slots[slot].source,
                          4, 0, 0, 0, 0x83, 0);
        g_state_03002810->slots[slot].state = 3;
        break;
    }
    case 3:
        if (func_08040F38(slot, 0) == 3) {
            g_state_03002810->mode = 5;
            data_0201F48A = 4;
            {
                RenderObject *object = data_030009E0;
                object += 4;
                object->status = 2;
            }
            func_0808A604(4, 11);
            data_0201F48B = 1;
            g_state_03002810->slots[slot].state = 2;
        }
        break;
    case 1:
        if (func_08040F38(slot, 0xffff) == 0xff) {
            data_030009E0[4].flags &= 0x7f;
            g_state_03002810->slots[slot].result = 6;
            g_state_03002810->slots[slot].state = 0xff;
        } else {
            if (g_state_03002810->slots[slot].buttons & 1) {
                func_08141540(100);
                g_state_03002810->mode = 0;
                data_0201F48A = 4;
                {
                    RenderObject *object = data_030009E0;
                    object += 4;
                    object->status = 1;
                }
                func_0808A604(4, 12);
                data_0201F48B = 0xff;
                g_state_03002810->slots[slot].state = 2;
            } else if (g_state_03002810->slots[slot].buttons & 2) {
                func_08141540(104);
                g_state_03002810->mode = 0;
                data_0201F48A = 4;
                {
                    RenderObject *object = data_030009E0;
                    object += 4;
                    object->status = 1;
                }
                func_0808A604(4, 12);
                data_0201F48B = 0xff;
                g_state_03002810->slots[slot].state = 2;
                break;
            }
            if (g_state_03002810->slots[slot].result == 3)
                func_0808A604(4, 2);
        }
        break;
    case 2:
        if (!data_030009E0[data_0201F48A].busy)
            g_state_03002810->slots[slot].state = data_0201F48B;
        break;
    case 0xfd:
        break;
    case 0xff:
        g_state_03002810->closed[slot] = 0xff;
        break;
    }
}
