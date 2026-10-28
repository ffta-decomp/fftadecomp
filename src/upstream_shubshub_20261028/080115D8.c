/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080115D8.c
 * Original SHA-256: 8df2fd311334dbd9a55c6638c19743b9e582f45d7890db4ba9f9848106bbdf27
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080115D8..0x08011614: 60 bytes / 22 instructions. */
typedef struct {
    u8 active;
    u8 unknown_01[0x3f];
} Slot080115D8;

typedef struct {
    u16 count;
    u8 unknown_02[2];
    u32 unknown_04;
    u32 unknown_08;
    u32 unknown_0c;
    u32 unknown_10;
    Slot080115D8 *slots;
} SlotState080115D8;

typedef void (*BufferInitializer080115D8)(void *, u32);

extern void *data_02009168;
extern SlotState080115D8 data_02009170;
extern BufferInitializer080115D8 const g_callbacks_0836D4B8[];
extern void *func_08007138(void *, u32);

void func_080115D8(void *allocator, u16 count)
{
    SlotState080115D8 *state;

    data_02009168 = allocator;
    state = &data_02009170;
    state->count = count;
    state->slots = func_08007138(allocator, state->count * sizeof(Slot080115D8));
    g_callbacks_0836D4B8[0](state->slots, state->count * sizeof(Slot080115D8));
    state->unknown_04 = 0;
    state->unknown_08 = 0;
    state->unknown_0c = 0;
    state->unknown_10 = 0;
}
