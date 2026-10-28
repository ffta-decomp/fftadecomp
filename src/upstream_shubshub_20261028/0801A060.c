/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801A060.c
 * Original SHA-256: bf744045f342fae839028132c54a241b2728574d3991ff2fdfaa997d66f4f39f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 value;
    u8 unknown_01[0x2B];
} InitializationEntry0801A060;

typedef struct {
    u16 value;
    u8 unknown_02[2];
    InitializationEntry0801A060 entries[4];
} InitializationState0801A060;

typedef struct {
    u8 unknown_00[0x20];
    u16 value_20;
    u16 value_22;
    u16 value_24;
    u16 value_26;
    u8 unknown_28[4];
    u16 value_2C;
    u8 unknown_2E[6];
    u8 active;
    u8 unknown_35[5];
    u16 value_3A;
    u8 unknown_3C[0x64];
    u32 value_A0;
    InitializationState0801A060 initialization;
    u8 unknown_158[0x10];
    u32 value_168;
    u32 value_16C;
    u8 unknown_170[8];
    u32 value_178;
    u32 value_17C;
    u8 unknown_180[4];
    u8 value_184;
    u8 unknown_185[0x2CB];
} MapState0801A060;

typedef struct {
    u8 unknown_00[0x28];
    u8 value;
} SelectionState0801A060;

typedef void (*ClearBuffer0801A060)(void *destination, u32 size);

extern MapState0801A060 g_state_02007F40;
extern ClearBuffer0801A060 const g_callbacks_0836D4B8[];
extern SelectionState0801A060 data_02007F10;
extern u8 data_02009198;
extern void func_0801E204(void);
extern void func_08020F34(InitializationState0801A060 *state);

/* Complete [0x0801A060, 0x0801A100): 160 bytes, 68 instructions. */
void func_0801A060(void)
{
    MapState0801A060 *state = &g_state_02007F40;
    u16 value_24 = state->value_24;
    u16 value_26 = state->value_26;
    u16 value_20 = state->value_20;
    u16 value_22 = state->value_22;

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    state->value_24 = value_24;
    state->value_26 = value_26;
    state->value_20 = value_20;
    state->value_22 = value_22;
    func_0801E204();
    state->value_2C = 0;
    state->active = 0;
    state->value_3A = 0x10;
    state->value_A0 = 0;
    func_08020F34(&state->initialization);
    state->value_168 = 0;
    state->value_16C = 0;
    state->value_178 = 0;
    state->value_17C = 0;
    state->value_184 = 0;
    data_02007F10.value = 0;
    data_02009198 = 0;
}
