/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080191B0.c
 * Original SHA-256: 50849da3067898c054359280d01816cb6c38074abb8788333cb6ce7ba5180d2a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct __attribute__((packed)) SelectedResource {
    u16 id : 10;
    u16 unknown_0a : 6;
} SelectedResource;

typedef struct ResourceSelection {
    const SelectedResource *current;
    u32 unknown_04;
    u32 unknown_08;
    u16 id;
    u8 unknown_0e[0xa4];
    u8 name_mode;
    u8 unknown_b3;
    u8 alternate_name;
} ResourceSelection;

extern ResourceSelection g_state_020020D0;
extern const u8 *const g_table_0855A64C[];
extern const u8 *func_080CEB34(u8 mode);
extern u16 func_08018C24(u8 *destination, const u8 *text);

#define CURRENT_RESOURCE_ID \
    (g_state_020020D0.current \
        ? g_state_020020D0.current->id : g_state_020020D0.id)

/* 080191B0..0801920A: 90 bytes, 38 instructions. */
u32 func_080191B0(u8 *destination)
{
    if (g_state_020020D0.alternate_name != 0) {
        func_08018C24(destination, func_080CEB34(g_state_020020D0.name_mode));
    } else {
        func_08018C24(destination, g_table_0855A64C[CURRENT_RESOURCE_ID]);
    }
    return 0;
}
