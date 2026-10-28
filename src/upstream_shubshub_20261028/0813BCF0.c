/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0813BCF0.c
 * Original SHA-256: 6097eb1c6c31d8c0cf277c51f8b35238801243b45094708c0b009e8ea85ad24f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
} Transfer0813BCF0;

typedef struct {
    u16 timer;
    u8 image[0x800];
    u16 unknown_802;
    Transfer0813BCF0 transfer;
} State0813BCF0;

typedef struct {
    u8 unknown_00[0x14];
    void *destination;
} Display0813BCF0;

typedef void (*BufferInitializer0813BCF0)(void *, u32);

extern u8 data_0300284C;
extern State0813BCF0 *data_0200F3B4;
extern Display0813BCF0 data_03000E60;
extern BufferInitializer0813BCF0 g_callbacks_0836D4B8[];

extern void func_08137A9C(void);
extern void *func_08137AEC(u32 bytes);
extern void func_08137B00(u8 *object);
extern void func_08137AD0(void);
extern void func_0813BDD0(void);
extern void func_0813BEEC(void);
extern void func_08000A98(void *transfer, const void *source,
                          void *destination, u32 bytes);
extern void func_08147A7C(u32 first, u32 second, u32 duration);
extern void func_080038C8(u32 scene);

/* 0x0813BCF0..0x0813BDD0: 224 bytes. */
void func_0813BCF0(void *context, u8 *phase)
{
    switch (*phase) {
    case 0:
        data_0300284C = 0;
        func_08137A9C();
        data_0200F3B4 = func_08137AEC(sizeof(State0813BCF0));
        g_callbacks_0836D4B8[0](data_0200F3B4, sizeof(State0813BCF0));
        func_0813BDD0();
        func_0813BEEC();
        *phase = 1;
        break;
    case 1:
        ++data_0200F3B4->timer;
        if (data_0200F3B4->timer == 20) {
            func_08000A98(&data_0200F3B4->transfer, data_0200F3B4->image,
                          data_03000E60.destination, 0x400);
        } else if (data_0200F3B4->timer == 200) {
            func_08147A7C(0, 0x100, 30);
            data_0200F3B4->timer = 0;
            *phase = 2;
        }
        break;
    case 2:
        if (++data_0200F3B4->timer > 30)
            *phase = 0xFF;
        break;
    case 0xFF:
        func_08137B00((u8 *)data_0200F3B4);
        func_08137AD0();
        func_080038C8(9);
        break;
    }
}
