/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081232C8.c
 * Original SHA-256: e733cbb7625e6d158dd38768a2f88008b4fc51a18b5e856ce78cb5de31d0c65d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 selector : 8;
    u32 mode : 8;
    s32 value : 16;
    u32 : 16;
    u32 amount : 16;
} ScriptParameters;

void func_08127C54(void *context, ScriptParameters parameters);

u32 func_081232C8(void *context, const u8 *script)
{
    ScriptParameters parameters;

    parameters.selector = script[1];
    parameters.value = script[2] | (script[3] << 8);
    parameters.mode = script[4];
    parameters.amount = script[5] | (script[6] << 8);
    func_08127C54(context, parameters);
    return 0x115;
}
