/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08135750.c
 * Original SHA-256: 0f54dbe0060fb9cd051bd0203f881e2f357e6c7b06295f2a448308edbdb5e0cb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x08135750..0x081357E8: 152 bytes. */
typedef struct {
    u8 unknown_0000[0x3C33];
    u8 count;
    u16 entries[1];
} RecordList;

typedef struct {
    u8 unknown_00[16];
} RecordConfig;

extern RecordList g_state_02000000;
extern RecordConfig g_table_08528F34[];
extern u8 func_081343C8(void *first, void *second, u16 value, u8 mode,
                         u32 flags, s16 amount, void *data,
                         RecordConfig *config);

u8 func_08135750(void *first, void *second, u16 value, u8 mode,
                u16 amount, void *data)
{
    s32 index;
    for (index = 0; index < g_state_02000000.count; index++) {
        if (func_081343C8(first, second, value, mode, 0, amount, data,
                         &g_table_08528F34[g_state_02000000.entries[index]]))
            return index + 1;
    }
    return 0;
}
