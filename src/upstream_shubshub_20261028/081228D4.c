/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081228D4.c
 * Original SHA-256: 1671caf18e9ed6e99df228b2a244421f97a6230e095b0706fdc6b9bf123882a5
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef unsigned int u32;

typedef struct {
    u32 unknown_00;
    u16 countdown;
} ScriptContext;

extern const u8 g_table_083A8190[];

u16 func_0801BB0C(s16 first, s16 second, u16 amount);
u16 func_0801BA20(s16 first, s16 second, u16 amount);
void func_08128898(ScriptContext *context, u16 first, u16 second, u8 amount);

u32 func_081228D4(ScriptContext *context, const u8 *script)
{
    u16 first = script[1] | (script[2] << 8);
    u16 second = script[3] | (script[4] << 8);

    switch (script[5]) {
    case 1:
        if (script[6] == 0) {
            func_0801BB0C(first, second, 1);
            return 0x110;
        }
        context->countdown = func_0801BB0C(first, second, script[6]);
        break;
    case 2:
        context->countdown = func_0801BA20(first, second, script[6]);
        break;
    case 0:
        context->countdown =
            func_0801BA20(first, second, g_table_083A8190[script[6] - 1]);
        break;
    case 3:
        func_08128898(context, first, second, script[6]);
        return 0x115;
    }

    if (context->countdown != 0)
        context->countdown--;
    return 0x114;
}
