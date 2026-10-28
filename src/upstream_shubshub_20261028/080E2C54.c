/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080E2C54.c
 * Original SHA-256: 6c7b27faa9b14aa537189bc6cb32103c0dcb4b745ee850c95babec09a8fb54a0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080E2C54..0x080E2CAC: 88 bytes. */
typedef struct {
    u16 state;
    u8 unknown_02[6];
    void *object;
} PolledEffectCommand;

typedef struct {
    void *object;
    u32 handle;
} PolledEffectState;

extern u32 func_080DF8E8(void *object, u32 first, u32 second, void *context);
extern u32 func_080DBA5C(u32 handle);

u32 func_080E2C54(void *context, PolledEffectCommand *command,
                  PolledEffectState *state)
{
    switch (command->state) {
    case 0:
        state->object = command->object;
        break;
    case 1:
        break;
    case 0x100:
        state->handle = func_080DF8E8(state->object, 0, 0, context);
        command->state++;
        break;
    case 0x101:
        state->handle = func_080DBA5C(state->handle);
        if (state->handle == 0)
            command->state = 2;
        break;
    }
    return 0;
}
