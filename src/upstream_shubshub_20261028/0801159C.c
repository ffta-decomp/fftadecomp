/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801159C.c
 * Original SHA-256: 7069c5071e971aaf4e94c7bc1bc98dcf61910f3e840b9277192393551923a8e4
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0801159C..0x080115D8: 60 bytes / 22 instructions. */
typedef struct {
    u8 active;
    u8 unknown_01[0x3F];
} Slot;

typedef struct {
    u16 count;
    u8 unknown_02[2];
    u32 unknown_04;
    u32 unknown_08;
    u32 unknown_0C;
    u32 unknown_10;
    Slot *slots;
} SlotState;

typedef void (*BufferInitializer)(void *destination, u32 size);
extern void *data_02009168;
extern SlotState data_02009170;
extern BufferInitializer const g_callbacks_0836D4B8[];
extern void *func_08007138(void *owner, u32 bytes);

void func_0801159C(void *allocator)
{
    SlotState *state;

    data_02009168 = allocator;
    state = &data_02009170;
    state->count = 40;
    state->slots = func_08007138(allocator, state->count * sizeof(Slot));
    g_callbacks_0836D4B8[0](state->slots, state->count * sizeof(Slot));
    state->unknown_04 = 0;
    state->unknown_08 = 0;
    state->unknown_0C = 0;
    state->unknown_10 = 0;
}
