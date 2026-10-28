/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08019120.c
 * Original SHA-256: 533e4dc9b43076875544ae2a53955c584cd3c76253f53b9f81e5b8c50eac78cf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct __attribute__((packed)) SelectedResource {
    u16 id : 10;
    u16 unknown_0a : 6;
    u8 flags;
} SelectedResource;

typedef struct ResourceSelection {
    const SelectedResource *current;
} ResourceSelection;

extern ResourceSelection g_state_020020D0;
extern const u8 *const g_table_085567F0[];
extern u8 func_08036350(u8 value);
extern u8 func_080CECF4(void);
extern u32 func_080CEC78(u16 id, u8 index, u8 count);
extern u16 func_08018ABC(u8 *destination, u32 value);
extern u16 func_08018C24(u8 *destination, const u8 *source);

/* 08019120..080191B0: 144 bytes, 57 instructions. */
u32 func_08019120(u8 *destination)
{
    ResourceSelection *selection = &g_state_020020D0;
    const SelectedResource *resource = selection->current;
    u8 *output = destination;

    if (!(resource->flags & 0x1C)) {
        func_08018C24(output, g_table_085567F0[0x44]);
    } else {
        u16 id = resource->id;
        u8 index = func_08036350(((u8 *)selection)[-0x167]);
        u8 count = func_080CECF4();
        u16 value = func_080CEC78(id, index, count);
        u16 length = func_08018ABC(output, value);

        output += length;
        func_08018C24(output, g_table_085567F0[0x2DC]);
    }
    return 0;
}
