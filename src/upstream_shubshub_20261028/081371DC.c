/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081371DC.c
 * Original SHA-256: 6706edc83107c147ba73730afc8fe77e26f47c4fdbee7eeccf5f30e0755f800b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1C];
    u8 animation[0x4E];
    u16 brightness;
    u8 unknown_6C[4];
    u8 field_70;
    u8 field_71;
    u8 unknown_72;
    u8 active;
    u8 started;
    u8 unknown_75;
    u8 id;
    u8 unknown_77;
    u16 field_78;
    u16 lifetime;
    u16 interval;
    u16 speed;
    s16 offset;
    u16 x;
    u16 y;
    u8 unknown_86[2];
} Entry081371DC;

typedef struct {
    u8 phase;
    u8 unknown_01[3];
    Entry081371DC entries[6];
} State081371DC;

typedef struct {
    u8 unknown_00[0x2FC2];
    u8 variant : 2;
} Global081371DC;

extern u8 *data_0200F3B0;
extern u8 data_089A040C[];
extern u8 data_089A033C[];
extern u8 *data_083A8C54[];
extern Global081371DC g_state_02000000;

void func_08137774(void *animation);
void func_08135FFC(void *state, void *first, u8 *source, u16 index, u8 value);
void func_0813777C(void *animation, u8 id, void *first, void *second,
                   u32 duration, u32 direction);
void func_081374DC(Entry081371DC *entry, u8 enabled);
void func_08137A7C(u16 seed, void *state);
u16 func_08137A80(void *state);

/* 0x081371DC - 766 bytes, including literal pools. */
void func_081371DC(State081371DC *state)
{
    u16 value;
    u16 duration;
    u32 direction;
    u8 i;

    switch (state->phase) {
    case 0:
    case 0xFF:
        break;
    case 1:
        for (i = 0; i < 6; i++) {
            state->entries[i].active = 0;
            state->entries[i].started = 0;
            state->entries[i].field_78 = 0;
            state->entries[i].id = i + 10;
            func_08137774(state->entries[i].animation);
        }
        state->phase = 2;
        func_08137A7C(23, data_0200F3B0 + 0x8998);
        break;
    case 2:
        value = func_08137A80(data_0200F3B0 + 0x8998) % 60U;
        if (value == 0) {
            for (i = 0; i < 6; i++) {
                if (state->entries[i].active == 0) {
                    func_08135FFC(data_0200F3B0 + 0x8624 + i * 0x88,
                                   data_089A040C, data_089A033C, 1, 1);
                    duration = func_08137A80(data_0200F3B0 + 0x8998) % 30U + 30;
                    direction = (u16)func_08137A80(data_0200F3B0 + 0x8998);
                    direction &= 1;
                    func_0813777C(state->entries[i].animation, i + 10,
                                   data_083A8C54[g_state_02000000.variant * 2 + 1] + 0x40,
                                   data_083A8C54[g_state_02000000.variant * 2 + 1] + 0x1E0,
                                   duration, direction);
                    state->entries[i].active = 1;
                    state->entries[i].started = 1;
                    value = func_08137A80(data_0200F3B0 + 0x8998);
                    if ((value & 3) == 0) {
                        state->entries[i].x = 0x1000;
                        state->entries[i].y = (func_08137A80(data_0200F3B0 + 0x8998) % 56U) << 7;
                        state->entries[i].offset = -10;
                    } else {
                        value = func_08137A80(data_0200F3B0 + 0x8998);
                        if (value % 2) {
                            state->entries[i].x = 0x1800;
                            state->entries[i].y =
                                (func_08137A80(data_0200F3B0 + 0x8998) % 10U + 150) << 7;
                            state->entries[i].offset = -40;
                        } else {
                            state->entries[i].x =
                                (func_08137A80(data_0200F3B0 + 0x8998) % 25U + 48) << 7;
                            state->entries[i].y = 0x5800;
                            state->entries[i].offset = -70;
                        }
                    }
                    state->entries[i].field_71 = 0;
                    state->entries[i].brightness = 250;
                    state->entries[i].field_70 = 0;
                    state->entries[i].interval = func_08137A80(data_0200F3B0 + 0x8998) % 20U + 20;
                    state->entries[i].speed = func_08137A80(data_0200F3B0 + 0x8998) % 2 + 1;
                    state->entries[i].lifetime = 120;
                    break;
                }
            }
        }
    case 3:
        for (i = 0; i < 6; i++) {
            if (state->entries[i].active != 0) {
                if (state->phase == 2)
                    func_081374DC(&state->entries[i], 1);
                else
                    func_081374DC(&state->entries[i], 0);
            }
        }
        break;
    default:
        return;
    }
}
