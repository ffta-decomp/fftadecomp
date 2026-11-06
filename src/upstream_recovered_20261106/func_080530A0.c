/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080530A0.c
 * Original SHA-256: 13776c5913d1179b09dcd15d2b88f1b136d6b858c8e98661637158319ccdd66b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    u8 position;
} ListState;

typedef struct {
    u8 unknown_00[0x0C];
    u16 *tiles;
    u8 unknown_10[5];
    u8 count;
    u8 unknown_16[6];
    u16 tile;
    u8 unknown_1E;
    u8 tag;
} TileMap;

typedef struct {
    u8 unknown_00[0x10];
    u8 x, y, width, height;
    u8 unknown_14[0x18];
    TileMap tilemap;
} Menu;

typedef struct {
    u8 unknown_00[0x11];
    u8 selected;
} SelectionCursor;

typedef struct {
    u8 unknown_0000[0x1D46];
    u8 item_index;
    u8 unknown_1D47;
    u8 active[20];
    u8 active_index;
} MenuState;

extern MenuState *data_0200F428;
typedef struct {
    u8 unknown_0000[0x1F3C];
    u16 entries[20];
    u8 unknown_1F64[0xF00];
    u8 item_types[0];
} GlobalState;

extern GlobalState g_state_02000000;

void func_08141540(u16 song);
u8 func_080543CC(ListState *state, u8 offset);
void func_08053E4C(ListState *state, void *context, u16 item,
                   u8 row, u8 enabled);
void func_08053568(u8 *count, u8 *total);
void func_08053C74(Menu *menu, void *context, u8 first, u8 second,
                   u8 rebuild);
u8 func_080CC218(u16 item);

/* Complete target: [0x080530A0, 0x080531F0), 336 bytes. */
void func_080530A0(u8 *command)
{
    SelectionCursor *cursor = (SelectionCursor *)((u8 *)data_0200F428 + 0xD3C);
    u8 row = cursor->selected;
    u8 count, total;

    if (data_0200F428->active[data_0200F428->active_index] == 1) {
        func_08141540(0x68);
        data_0200F428->active[data_0200F428->active_index] = 0;
        func_08053E4C((ListState *)((u8 *)data_0200F428 + 0xD1C),
                      (u8 *)data_0200F428 + 0x1A60,
                      g_state_02000000.entries[
                          func_080543CC((ListState *)((u8 *)data_0200F428 + 0xD1C), row)],
                      row, 0);
    } else {
        func_08141540(0x64);
        data_0200F428->active[data_0200F428->active_index] = 1;
        func_08053E4C((ListState *)((u8 *)data_0200F428 + 0xD1C),
                      (u8 *)data_0200F428 + 0x1A60,
                      g_state_02000000.entries[
                          func_080543CC((ListState *)((u8 *)data_0200F428 + 0xD1C), row)],
                      row, 1);
    }

    func_08053568(&count, &total);
    func_08053C74((Menu *)((u8 *)data_0200F428 + 0x1114),
                  (u8 *)data_0200F428 + 0x1A60, count, total, 0);
    if (func_080CC218(g_state_02000000.item_types[data_0200F428->item_index]) <= total)
        *command = 100;
}
