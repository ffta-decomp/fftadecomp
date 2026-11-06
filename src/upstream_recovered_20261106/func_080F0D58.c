/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080F0D58.c
 * Original SHA-256: 759b2e5e752afcd0b887df0432ec712a0615939a2430a19fac1584093b5ea16b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
/* Complete target [0x080F0D58, 0x080F0EF2), 410 bytes including pools. */
#include "ffta.h"

typedef struct {
    void *sprite;
} SpriteOwner;

typedef struct {
    u16 phase;
    u16 unknown_02;
    SpriteOwner *owner;
    u32 unknown_08[3];
    u16 index;
} SpriteCommand;

typedef struct {
    u8 index;
    u8 timer;
    u16 unknown_02;
    SpriteOwner *owner;
    void *children[4];
    void *script;
} SpritePayload;

extern const void *const data_0839A3C0[];
extern s16 data_0839A4EC[];
extern const u8 data_0839A4DC[];
extern const u8 data_0839A4E4[];
extern const u8 data_0839A4E8[];

extern u16 func_08011010(const void *);
extern u16 func_08011030(const void *);
extern u8 func_08011040(Struct08011040 *, u16 *, u16 *, u16 *);
extern void *func_080D5CC0(const void *, u16, s16, s16, s16, u8, u8, u8);
extern void func_080111A8(void *, u8);
extern void func_08011204(void *);
extern void func_08011034(void *, u16);
extern void func_08011058(void *, s16);
extern void func_0801115C(void *, u8);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080D5F74(void **, u16);

u32 func_080F0D58(void *task, SpriteCommand *command, SpritePayload *payload)
{
    u16 x, y, z;

    switch (command->phase) {
    case 0:
        payload->index = command->index;
        payload->owner = command->owner;
        break;
    case 0x100: {
        u8 value;
        u8 index;

        func_08011010(payload->owner->sprite);
        value = func_08011030(payload->owner->sprite);
        func_08011040(payload->owner->sprite, &x, &y, &z);
        for (index = 0; index < 4; index++) {
            payload->children[index] = func_080D5CC0(
                data_0839A3C0[payload->index], 1, (s16)x,
                data_0839A4EC[index], 0x280, 6, 0, 0);
            func_080111A8(payload->children[index], 1);
            if (index & 1)
                func_08011204(payload->children[index]);
            func_08011034(payload->children[index], value);
            func_08011058(payload->children[index], data_0839A4EC[index]);
            if (index != 0)
                func_0801115C(payload->children[index], 0);
        }
        func_0801115C(payload->owner->sprite, 0);
        payload->script = func_080DFD8C(data_0839A4DC, 1, 4, 0, task);
        command->phase++;
        break;
    }
    case 0x101: {
        u8 index;
        for (index = 0; index < 4; index++) {
            u8 visible = 1;
            if (payload->timer < data_0839A4E4[index] ||
                payload->timer >= data_0839A4E8[index])
                visible = 0;
            func_0801115C(payload->children[index], visible);
        }
        payload->timer++;
        if (payload->timer >= data_0839A4E8[3])
            command->phase++;
        break;
    }
    case 0x102:
        func_080D5F74(payload->children, 4);
        command->phase = 2;
        break;
    }
    return 0;
}
