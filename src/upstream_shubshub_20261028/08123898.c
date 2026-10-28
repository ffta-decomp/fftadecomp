/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08123898.c
 * Original SHA-256: 35659f899abb73410285a1495d733ec2108b9ce50ab57edf49cbe77efd1d1c9b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "script_entry.h"

typedef struct {
    u8 unknown_0000[0x3C24];
    u32 flags;
} ScriptFlagState;

extern ScriptFlagState g_state_02000000;

void func_08009C04(u16 value, u16 mode);
void func_0802292C(u32 value);

u32 func_08123898(void *context, const u8 *script)
{
    u32 identifier = script[1] | (script[2] << 8);
    int index = 255;
    const ScriptEntry *entries = g_table_08563A70;
    u8 *selected = (u8 *)0x02003C2A;

    do {
        if (entries[index].identifier == identifier) {
            *selected = index;
            func_08009C04(entries[index].value, 0);
            break;
        }
        index--;
    } while (index > 0);
    if (identifier != 1)
        func_0802292C(13);
    g_state_02000000.flags |= 0x10;
    return 0x110;
}
