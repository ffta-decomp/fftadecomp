/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806707C.c
 * Original SHA-256: 00fb46164cd5a238f1a6498f880fc38caf38a9db715b22cfc142ac95834ae503
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[4];
    u16 rows;
    u8 unknown_06[8];
    u16 count;
} Rect;

typedef struct {
    u8 unknown_00[0x1A];
    u16 selection;
    u8 unknown_1C[4];
} MenuList;

typedef struct {
    u8 unknown_00[0x18];
    Rect rect;
    u8 renderer[0x2C];
    MenuList list;
    u8 unknown_74[0x48];
    const void *resource;
} Menu;

extern void func_08016210(void *renderer, const void *resource, u32 count, u32 rows);
extern void func_080670B4(Menu *menu);

/* Complete target: [0x0806707C, 0x080670B4), 56 bytes, 26 instructions. */
void func_0806707C(Menu *menu)
{
    u8 *renderer = menu->renderer;
    Rect *rect = &menu->rect;
    MenuList *list = &menu->list;

    func_08016210(renderer, menu->resource, (u16)(rect->count + 0x100), rect->rows);
    func_080670B4(menu);
    list->selection = 0;
}
