/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08123320.c
 * Original SHA-256: 4f65090f8c80c01e375a5ca7e340cc138d933c2d99187fe6d2876cdafcb86fc9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 selector : 8;
    u32 mode : 8;
    s32 x : 16;
    s32 y : 16;
    u32 value : 16;
} ScriptArguments;

void func_08127B80(void *context, ScriptArguments arguments);

u32 func_08123320(void *context, const u8 *script)
{
    ScriptArguments arguments;

    arguments.selector = script[1];
    arguments.x = script[2] | script[3] << 8;
    arguments.y = script[4] | script[5] << 8;
    arguments.mode = script[6];
    arguments.value = script[7] | script[8] << 8;
    func_08127B80(context, arguments);
    return 0x115;
}
