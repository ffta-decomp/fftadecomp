/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08019E84.c
 * Original SHA-256: 5dea7f8a8f5600714eb93ebe45056b4e18609df9ebec55b52599fc8190514536
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u16 width;
    u16 height;
    u16 insetX;
    u16 insetY;
    u8 unknown_10[0x14];
    s16 focusX;
    s16 focusY;
    s16 originX;
    s16 originY;
} PrimaryViewport;

typedef struct {
    u8 unknown_00[0xA];
    s16 x;
    s16 y;
} SecondaryViewport;

typedef struct {
    PrimaryViewport primary;
    u8 unknown_2C[0x228 - 0x2C];
    SecondaryViewport secondary;
} ViewportState;

extern ViewportState g_state_02007F40;
extern void func_0801B878(void);
extern void func_08019B48(void);
extern u8 func_0801D8B8(void);
extern void func_0801D918(void);
extern void func_08019C74(void);

/* Complete target: [0x08019E84, 0x08019FC6), 322 bytes. */
void func_08019E84(void)
{
    u8 changed = 0;

    if (g_state_02007F40.primary.originX + 8 > g_state_02007F40.primary.focusX)
    {
        g_state_02007F40.primary.originX =
            (g_state_02007F40.primary.focusX - g_state_02007F40.primary.insetX) & ~7;
        changed = 1;
    }
    else if (g_state_02007F40.primary.originX + g_state_02007F40.primary.width - 8 <
             g_state_02007F40.primary.focusX + 240)
    {
        g_state_02007F40.primary.originX =
            (g_state_02007F40.primary.focusX - g_state_02007F40.primary.insetX) & ~7;
        changed = 1;
    }

    if (g_state_02007F40.primary.originY + 8 > g_state_02007F40.primary.focusY)
    {
        g_state_02007F40.primary.originY =
            (g_state_02007F40.primary.focusY - g_state_02007F40.primary.insetY) & ~7;
        changed = 1;
    }
    else if (g_state_02007F40.primary.originY + g_state_02007F40.primary.height - 8 <
             g_state_02007F40.primary.focusY + 160)
    {
        g_state_02007F40.primary.originY =
            (g_state_02007F40.primary.focusY - g_state_02007F40.primary.insetY) & ~7;
        changed = 1;
    }

    if (changed)
        func_0801B878();
    else
        func_08019B48();

    if (func_0801D8B8())
    {
        SecondaryViewport *secondary = &g_state_02007F40.secondary;
        changed = 0;
        if (secondary->x + 8 > g_state_02007F40.primary.focusX)
        {
            secondary->x =
                (g_state_02007F40.primary.focusX - 8) & ~7;
            changed = 1;
        }
        else if (secondary->x + 248 <
                 g_state_02007F40.primary.focusX + 240)
        {
            secondary->x =
                (g_state_02007F40.primary.focusX - 8) & ~7;
            changed = 1;
        }

        if (secondary->y + 8 > g_state_02007F40.primary.focusY)
        {
            secondary->y =
                (g_state_02007F40.primary.focusY - 48) & ~7;
            changed = 1;
        }
        else if (secondary->y + 248 <
                 g_state_02007F40.primary.focusY + 160)
        {
            secondary->y =
                (g_state_02007F40.primary.focusY - 48) & ~7;
            changed = 1;
        }

        if (changed)
            func_0801D918();
        else
            func_08019C74();
    }
}
