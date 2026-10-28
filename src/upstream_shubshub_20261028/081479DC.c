/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081479DC.c
 * Original SHA-256: 9fb02f345fcb135bb89a2bdc9175740792a2cc4b17586b676c883afd199639a4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    void *context;
    u32 count;
} RegionState081479DC;

extern void (*g_callbacks_0836D4B8[])(void *region, u32 size);
extern u8 data_03003860[];
extern u8 data_03003E68[];
extern u8 data_03003C68[];
extern RegionState081479DC data_03003C60;
extern u8 data_03005668;
extern void *func_080070C8(void *region, u32 size);

/* 0x081479DC: 80 bytes; initialize the regions and reset their state. */
void func_081479DC(void)
{
    g_callbacks_0836D4B8[0](data_03003860, 0x400);
    g_callbacks_0836D4B8[0](data_03003E68, 0x1800);
    data_03003C60.context = func_080070C8(data_03003C68, 0x200);
    data_03003C60.count = 0;
    data_03005668 = 0;
}
