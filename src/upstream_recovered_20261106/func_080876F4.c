/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080876F4.c
 * Original SHA-256: 4a803e22485fda1ae52f2e584bc1b903c725f70b5ea820f6b79e1e7461d8781e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 unknown00[0x18];
    u16 *first_plane;
    u16 *second_plane;
    u8 unknown20[8];
    u8 stride;
    u8 unknown29[0x23];
} TileRenderer;

typedef struct {
    u8 unknown0000[0x1F64];
    u32 amount;
} ResourceState;

typedef struct {
    u8 unknown0000[0xC20];
    u8 alternate;
} DisplayState;

extern TileRenderer data_030009E0[];
extern ResourceState g_state_02000000;
extern DisplayState *data_03002818;
extern u16 *func_0808B8E4(u32 index, u32 plane, s32 x, s32 y);
extern s32 func_080CA7A4(u16 entry, u8 selector);
extern void func_080899AC(u16 *destination, u16 stride, u16 spacing,
                          u16 value, u16 digits, u16 alignment, u16 attributes);
extern void func_08035B64(u16 *destination, u16 digits, u32 value, u16 attributes);
extern u32 func_0808A604(u32 index, u16 command);

/* Complete [0x080876F4, 0x08087B30), 1084 bytes. */
u32 func_080876F4(u32 index, u16 entry, s32 mode)
{
    u32 value;

    if (mode != -1) {
        if (entry == 0xFFFF)
            entry = *(u16 *)0x0200F290;
        else if (entry != 0)
            *(u16 *)0x0200F290 = entry;

        if (mode == 4) {
            *(u32 *)func_0808B8E4(0, 1, 10, 14) = 0;
            *(u32 *)func_0808B8E4(0, 1, 10, 15) = 0;
            *(u32 *)func_0808B8E4(0, 1, 12, 14) = 0;
            *(u32 *)func_0808B8E4(0, 1, 12, 15) = 0;
            *(u32 *)func_0808B8E4(0, 1, 10, 17) = 0;
            *(u32 *)func_0808B8E4(0, 1, 10, 18) = 0;
            *(u32 *)func_0808B8E4(0, 1, 12, 17) = 0;
            *(u32 *)func_0808B8E4(0, 1, 12, 18) = 0;
            *(u32 *)func_0808B8E4(0, 1, 20, 12) = 0;
            *(u32 *)func_0808B8E4(0, 1, 20, 13) = 0;
            *(u32 *)func_0808B8E4(0, 1, 26, 12) = 0;
            *(u32 *)func_0808B8E4(0, 1, 26, 13) = 0;
            return 0;
        }

        if (mode <= 1) {
            value = func_080CA7A4(entry, 10);
            func_080899AC(func_0808B8E4(index, 1, 10, 0), data_030009E0[index].stride, 120, value, 3, 0, 0xD000);

            value = func_080CA7A4(entry, 11);
            func_080899AC(func_0808B8E4(index, 1, 10, 2), data_030009E0[index].stride, 100, value, 3, 0, 0xD000);

            value = func_080CA7A4(entry, 12);
            func_080899AC(func_0808B8E4(0, 1, 11, 14), 32, 120, value, 3, 0, 0xD000);

            value = func_080CA7A4(entry, 13);
            func_080899AC(func_0808B8E4(index, 1, 10, 5), data_030009E0[index].stride, 100, value, 3, 0, 0xD000);

            value = func_080CA7A4(entry, 14);
            func_080899AC(func_0808B8E4(0, 1, 11, 17), 32, 120, value, 3, 0, 0xD000);

            value = g_state_02000000.amount;
            func_08035B64(func_0808B8E4(9, 1, 1, 1), 8, value, 0x6000);
            if (data_03002818->alternate == 0) {
                value = func_080CA7A4(entry, 16);
                func_080899AC(func_0808B8E4(index, 1, 19, 0), data_030009E0[index].stride, 100, value, 2, 0, 0xD000);

                value = func_080CA7A4(entry, 17);
                func_080899AC(func_0808B8E4(0, 1, 20, 12), 32, 120, value, 2, 0, 0xD000);

                value = func_080CA7A4(entry, 15);
                func_080899AC(func_0808B8E4(0, 1, 26, 12), 32, 120, value, 2, 0, 0xD000);

            }
        } else {
            value = 0;
            func_080899AC(func_0808B8E4(index, 1, 11, 0), data_030009E0[index].stride, 120, value, 2, 0, 0xD000);

            func_080899AC(func_0808B8E4(index, 1, 11, 2), data_030009E0[index].stride, 100, value, 2, 0, 0xD000);

            func_080899AC(func_0808B8E4(0, 1, 12, 14), 32, 120, value, 2, 0, 0xD000);

            func_080899AC(func_0808B8E4(index, 1, 11, 5), data_030009E0[index].stride, 100, value, 2, 0, 0xD000);

            func_080899AC(func_0808B8E4(0, 1, 12, 17), 32, 120, value, 2, 0, 0xD000);

            value = g_state_02000000.amount;
            func_08035B64(func_0808B8E4(9, 1, 1, 1), 8, value, 0x6000);
            if (data_03002818->alternate == 0) {
                value = 0;
                func_080899AC(func_0808B8E4(index, 1, 20, 0), data_030009E0[index].stride, 100, value, 1, 0, 0xD000);

                func_080899AC(func_0808B8E4(0, 1, 20, 12), 32, 120, value, 2, 0, 0xD000);

                func_080899AC(func_0808B8E4(0, 1, 26, 12), 32, 120, value, 2, 0, 0xD000);

            }
        }
        if (mode == 1 || mode == 3 || mode == 5)
            func_0808A604(index, 2);
        if ((mode == 1 || mode == 5) && data_03002818->alternate == 0)
            func_0808A604(9, 2);
    }
    return *(u16 *)0x0200F290;
}
