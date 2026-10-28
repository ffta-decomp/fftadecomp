/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801D494.c
 * Original SHA-256: 478b6308017348953afc52f09ca7d90c01d7ce54f1d85d5d619b958941c102f4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 primaryLayer;
    u8 secondaryLayer;
    u8 primaryMode;
    u8 secondaryMode;
    u8 format;
    u8 unknown_05[0xB];
    void *source;
    void *primaryDestination;
    void *secondaryDestination;
    u8 unknown_1C[8];
    s16 viewportX;
    s16 viewportY;
    s16 originX;
    s16 originY;
    u8 unknown_2C[0x228 - 0x2C];
    u8 refresh;
    u8 unknown_229[3];
    u8 pendingPrimaryLayer;
    u8 pendingSecondaryLayer;
    u8 unknown_22E[0x248 - 0x22E];
    void *primaryResource;
    void *secondaryResource;
} LayerState;

extern LayerState g_state_02007F40;
extern u16 g_control_flags_03000940;
extern u8 func_0801E648(void);
extern u8 func_0801E658(void);
extern void func_0801E458(u8 layer, u8 format, u8 mode, s16 x, s16 y,
                          void *source, void *destination);
extern u32 func_080035A8(u8 layer);
extern void func_08148498(void *resource);

/* Complete target: [0x0801D494, 0x0801D58C), 248 bytes. */
void func_0801D494(void)
{
    LayerState *state = &g_state_02007F40;
    u16 x = state->viewportX - state->originX;
    u16 y = state->viewportY - state->originY;

    state->primaryLayer = state->pendingPrimaryLayer;
    state->secondaryLayer = state->pendingSecondaryLayer;

    if (func_0801E648())
    {
        func_0801E458(state->primaryLayer, state->format, state->primaryMode,
                      (s16)x, (s16)y, state->source, state->primaryDestination);
        {
            u32 mask = func_080035A8(state->primaryLayer);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        {
            u32 mask = func_080035A8(3);
            u16 flags = g_control_flags_03000940;
            flags &= ~mask;
            g_control_flags_03000940 = flags;
        }
    }

    if (func_0801E658())
    {
        func_0801E458(state->secondaryLayer, state->format, state->secondaryMode,
                      (s16)x, (s16)y, state->source, state->secondaryDestination);
        {
            u32 mask = func_080035A8(state->secondaryLayer);
            u16 flags = g_control_flags_03000940;
            flags |= mask;
            g_control_flags_03000940 = flags;
        }
        {
            u32 mask = func_080035A8(2);
            u16 flags = g_control_flags_03000940;
            flags &= ~mask;
            g_control_flags_03000940 = flags;
        }
    }

    state->refresh = 0;
    func_08148498(state->primaryResource);
    state->primaryResource = 0;
    func_08148498(state->secondaryResource);
    state->secondaryResource = 0;
}
