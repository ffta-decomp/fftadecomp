/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804EC74.c
 * Original SHA-256: 9cbe3583022334df5d8152ae070297837f8cd8eb52758371f208d873a5682072
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00;
    s8 selected;
    s8 previous;
    u8 unknown_003[0x289];
    u8 text[1];
} MenuState;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} GraphicsState;

typedef struct {
    u8 unknown_00;
    u8 flags;
    u8 detail;
    u8 unknown_03[9];
} ResourceEntry;

typedef struct {
    u8 unknown_00[8];
    u8 *resource;
    u8 unknown_00C[0xC4];
    u8 work[0xB14];
    ResourceEntry entries[128];
} ResourceState;

extern MenuState *data_0201F54C;
extern GraphicsState data_03000990;
extern ResourceState g_state_020020D0;
extern const u8 data_084C3798[];
extern void func_08013A88(void *tiles, u16 count);
extern u8 *func_0804CA58(u32 bytes);
extern void func_0804CA6C(void *buffer);
extern u16 func_08013E9C(u8 *buffer, const u8 *table, u8 *workspace,
                         u32 index, u32 first, u32 second);
extern void func_0801539C(void *context, void *tiles, const void *text,
                         u32 style, u32 count);

/* Complete target: [0x0804EC74, 0x0804ED44), 208 bytes. */
void func_0804EC74(void)
{
    u32 format;
    u8 *destination;
    u8 *buffer;
    u8 *workspace;
    ResourceEntry *entry;

    if (data_0201F54C->previous != data_0201F54C->selected) {
        destination = data_03000990.tiles + 0x2800;

        data_0201F54C->previous = data_0201F54C->selected;
        if (data_0201F54C->selected <= 0) {
            func_08013A88(destination, 44);
        } else {
            entry = &g_state_020020D0.entries[data_0201F54C->selected];
            format = 5;

            if ((entry->flags & 3) == 3) {
                format = entry->detail ? 7 : 6;
                g_state_020020D0.resource = g_state_020020D0.work;
            }
            buffer = func_0804CA58(0x200);
            workspace = buffer + 0x100;
            func_08013E9C(buffer, data_084C3798, workspace, format, 0, 0);
            func_08013A88(destination, 44);
            func_0801539C(data_0201F54C->text, destination, buffer, 0, 22);
            func_0804CA6C(buffer);
        }
    }
}
