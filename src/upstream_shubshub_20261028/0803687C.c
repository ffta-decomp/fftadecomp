/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0803687C.c
 * Original SHA-256: 9a59951bca9b0f06e941cd99d5a73100d90e9a5d1bc59ff4030ba1af8e95d178
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 shown : 1;
    u8 dirty : 1;
    u8 width : 6;
} __attribute__((packed)) HintFlags;

typedef struct {
    u8 unknown_00[6];
    s16 column;
    s16 row;
    u16 unknown_0A;
    u16 scroll;
    u8 unknown_0E[5];
    HintFlags flags;
    s16 x;
    s16 y;
    u8 unknown_18[2];
    u8 selector;
    u8 selected;
    u8 unknown_1C[0x70];
    u8 visible;
} HintCursor;

typedef struct {
    u8 unknown_00[3];
    u8 record;
    u8 unknown_04[8];
} HintEntry;

typedef struct {
    u8 unknown_00[0xA4];
    HintEntry entries[1];
} HintMap;

typedef struct {
    u8 x;
    u8 y;
    u8 unknown_02[18];
} HintRecord;

typedef struct {
    HintMap *map;
    HintCursor *cursor;
    u8 request[0x1C];
    u8 unknown_24[0x7A];
    u16 busy;
    u8 unknown_A0[0x5D4];
    u8 cached;
    u8 unknown_675[3];
    const void *graphic;
    HintRecord *records;
    u8 unknown_680[0x8BE];
    u8 blocked;
    u8 timer;
} HintState;

extern HintState *g_state_03002810;
extern u8 data_02003CB0[];
extern const u8 data_08391DE4[];
extern const void *const data_08391A48[];
extern const u8 data_083AB42C[];
extern const u16 data_08391E02[];
extern u8 data_06010980[];
extern u8 func_0803616C(s16 *column, s16 *row);
extern u8 func_080363C0(u8 selector, HintMap *map);
extern void func_08005318(const void *source, void *destination, u32 count, u32 offset);
extern void func_08000A98(void *request, const void *source, void *destination, u16 count);
extern void func_08001F34(const void *graphic, s32 x, s32 y, u32 a3, u32 a4,
                         u32 a5, u32 a6, u32 a7, u32 a8, u32 a9, u32 a10);
extern void func_080366BC(void);

/* Complete target: [0x0803687C, 0x08036B18), 668 bytes. */
void func_0803687C(u32 mode)
{
    u32 selector;
    if (g_state_03002810->busy || g_state_03002810->blocked)
        return;

    selector = g_state_03002810->cursor->selector =
        func_0803616C(&g_state_03002810->cursor->column,
                      &g_state_03002810->cursor->row);
    if (selector)
    {
        g_state_03002810->cursor->selected =
            func_080363C0(selector, g_state_03002810->map);
        if (g_state_03002810->cursor->selected)
        {
            u32 selected = g_state_03002810->cursor->selected;
            u32 entryOffset = selected * sizeof(HintEntry) + 0xA4;
            s32 record = ((HintEntry *)((u8 *)g_state_03002810->map + entryOffset))->record - 1;

            if (mode == 0)
            {
                s32 y;

                if (g_state_03002810->cached != g_state_03002810->cursor->selected)
                {
                    u8 *buffer = data_02003CB0;
                    s32 x;
                    s32 pixelX;
                    s32 inset;

                    g_state_03002810->timer = 0;
                    g_state_03002810->cached = g_state_03002810->cursor->selected;
                    g_state_03002810->cursor->flags.width =
                        data_08391DE4[g_state_03002810->cursor->selected - 1];
                    g_state_03002810->graphic = data_08391A48[g_state_03002810->cursor->flags.width];
                    func_08005318(data_083AB42C, buffer,
                                  data_08391E02[g_state_03002810->cursor->selected - 1] >> 1,
                                  g_state_03002810->cursor->flags.width + 5);
                    pixelX = g_state_03002810->records[record].x * 8;
                    inset = g_state_03002810->cursor->flags.width * 4 + 12;
                    x = pixelX - inset;
                    if (x < 0)
                        x = 0;
                    else
                    {
                        s32 width = g_state_03002810->cursor->flags.width * 8 + 40;
                        if (x + width > 240)
                            x = 200 - g_state_03002810->cursor->flags.width * 8;
                    }
                    g_state_03002810->cursor->x = x;
                    g_state_03002810->cursor->y = g_state_03002810->records[record].y * 8 + 10;
                    g_state_03002810->cursor->flags.shown = 1;
                    g_state_03002810->cursor->flags.dirty = 1;
                    func_08000A98(g_state_03002810->request, buffer, data_06010980,
                                  g_state_03002810->cursor->flags.width * 32 + 160);
                }

                y = g_state_03002810->cursor->y - g_state_03002810->cursor->scroll;
                if (y > 189 || g_state_03002810->timer <= 4)
                    y = 240;
                else if (y > 144)
                    y = 144;
                if (g_state_03002810->cursor->visible)
                    func_08001F34(g_state_03002810->graphic, g_state_03002810->cursor->x,
                                  y, 0, 0, 0, 0, 0, 0, 3, 3);
                else
                    func_08001F34(g_state_03002810->graphic, g_state_03002810->cursor->x,
                                  y, 0, 0, 0, 0, 0, 0, 3, 0);
                if (g_state_03002810->timer < 255)
                    g_state_03002810->timer++;
            }
            else if (g_state_03002810->cursor->visible)
                func_080366BC();
        }
        else if (g_state_03002810->cursor->visible)
            func_080366BC();
    }
    else
    {
        if (g_state_03002810->cursor->visible)
            func_080366BC();
        else
        {
            g_state_03002810->cursor->flags.shown = 0;
            g_state_03002810->cursor->flags.dirty = 0;
            g_state_03002810->cursor->selected = 0;
        }
    }
}
