/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0803890C.c
 * Original SHA-256: 4442e7ad27a47755f529b20c38a66c38302dc681779bd2d64148d6ce88e0f119
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Entry0803890C {
    u16 id;
    u16 kind;
    u8 quantity;
    u8 unknown_05[3];
};

struct State0803890C {
    u8 unknown_000[0x914];
    struct Entry0803890C entries[8];
};

extern struct State0803890C *g_state_03002810;
extern u8 data_02003CB0[];
extern u32 func_080388C8(u32);
extern u32 func_080C95A8(u32);
extern void func_080C95C0(u32, u32);
extern void func_080CA900(u32, u32);
extern void func_080C9574(u32, u32);
extern s32 func_080384F0(u32);
extern s32 func_08038628(u32);
extern void func_080CB27C(u8 *);

/* Target: [0x0803890C, 0x08038AFE), 498 bytes, 202 instructions. */
s32 func_0803890C(void)
{
    s32 i;

    for (i = 0; i < 8; i++) {
        if (g_state_03002810->entries[i].id) {
            switch (g_state_03002810->entries[i].kind) {
            case 0:
                if (g_state_03002810->entries[i].id == 0x33) {
                    if ((u8)func_080388C8(0x33)) {
                        u8 count = func_080C95A8(1);
                        if (count < 0xff)
                            count++;
                        else
                            count = 0xff;
                        func_080C95C0(1, count);
                    } else {
                        func_080CA900(g_state_03002810->entries[i].id,
                                     g_state_03002810->entries[i].quantity);
                    }
                } else if (g_state_03002810->entries[i].id == 0x94) {
                    if ((u8)func_080388C8(0x94)) {
                        u8 count = func_080C95A8(2);
                        if (count < 0xff)
                            count++;
                        else
                            count = 0xff;
                        func_080C95C0(2, count);
                    } else {
                        func_080CA900(g_state_03002810->entries[i].id,
                                     g_state_03002810->entries[i].quantity);
                    }
                } else if (g_state_03002810->entries[i].id == 0x12e) {
                    if ((u8)func_080388C8(0x12e)) {
                        u8 count = func_080C95A8(3);
                        if (count < 0xff)
                            count++;
                        else
                            count = 0xff;
                        func_080C95C0(3, count);
                    } else {
                        func_080CA900(g_state_03002810->entries[i].id,
                                     g_state_03002810->entries[i].quantity);
                    }
                } else if (g_state_03002810->entries[i].id == 0x11e) {
                    if ((u8)func_080388C8(0x11e)) {
                        u8 count = func_080C95A8(4);
                        if (count < 0xff)
                            count++;
                        else
                            count = 0xff;
                        func_080C95C0(4, count);
                    } else {
                        func_080CA900(g_state_03002810->entries[i].id,
                                     g_state_03002810->entries[i].quantity);
                    }
                } else {
                    func_080CA900(g_state_03002810->entries[i].id,
                                 g_state_03002810->entries[i].quantity);
                }
                g_state_03002810->entries[i].id = 0;
                break;
            case 1:
                func_080C9574(0x5aa, 1);
                if (func_080384F0(g_state_03002810->entries[i].id))
                    g_state_03002810->entries[i].id = 0;
                break;
            case 2:
                if (func_08038628(g_state_03002810->entries[i].id)) {
                    func_080CB27C(data_02003CB0);
                    g_state_03002810->entries[i].id = 0;
                }
                break;
            }
        }
    }
    for (i = 0; i < 8; i++) {
        if (g_state_03002810->entries[i].id)
            return 0;
    }
    return 1;
}
