/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08019814.c
 * Original SHA-256: d1aeceb90e942d8eb8ff1028ecc1d6f3579c870169c809ad694a899604ce8aaf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct TextSource08019814 TextSource08019814;

typedef struct {
    u32 unknown_00;
    const TextSource08019814 *selection;
} State08019814;

extern State08019814 g_state_020020D0;
extern const u8 *const g_table_08526680[];
extern const u8 *func_080CA1BC(const TextSource08019814 *source);
extern u16 func_08018C24(u8 *destination, const u8 *text);

/* Complete [0x08019814, 0x0801984A): 54 bytes, 20 instructions. */
u32 func_08019814(u8 *destination)
{
    const TextSource08019814 *selection = g_state_020020D0.selection;
    const u8 *text = func_080CA1BC(selection);

    if (selection == 0)
        func_08018C24(destination, g_table_08526680[0]);
    else
        func_08018C24(destination, text);
    return 0;
}
