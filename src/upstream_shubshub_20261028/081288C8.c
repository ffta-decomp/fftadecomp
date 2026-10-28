/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081288C8.c
 * Original SHA-256: 73a8a50e5d104884a603978cbf67a5f154a27ccd7dbeee5046fea606cdbbfeb6
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* Target: complete [0x081288C8, 0x08128968), 160 bytes including literals. */
typedef struct Transfer081288C8 {
    u8 status;
    u8 kind;
    u16 unknown_02;
    const void *source;
    void *destination;
    u32 control;
    u8 unknown_10[8];
    struct Transfer081288C8 *next;
} Transfer081288C8;

typedef struct {
    u8 unknown_00[0x2c4];
    Transfer081288C8 transfers[4];
    u8 unknown_334[0x70];
    u8 next_transfer;
} State081288C8;

typedef struct {
    u8 unknown_00[0x10];
    u8 *destination;
} Destination081288C8;

extern u8 data_02003CB0[];
extern const u8 data_083C3954[];
extern Destination081288C8 data_03000990;
extern Destination081288C8 data_030008B0;
extern void func_0800543C(void *, const void *);
extern void func_080CB9B0(void *, u32);
extern void func_08000ADC(Transfer081288C8 *, const void *, void *, u16);

static inline Transfer081288C8 *next_transfer(State081288C8 *state)
{
    Transfer081288C8 *transfer = &state->transfers[state->next_transfer++];

    state->next_transfer &= 3;
    return transfer;
}

void func_081288C8(State081288C8 *state)
{
    u8 *buffer = data_02003CB0;
    u8 *palette;
    Transfer081288C8 *transfer;

    func_0800543C(buffer, data_083C3954);
    palette = buffer + 0x1340;
    func_080CB9B0(palette, 30);

    transfer = next_transfer(state);
    func_08000ADC(transfer, buffer, data_03000990.destination + 0x1c00, 0x4d0);

    transfer = next_transfer(state);
    func_08000ADC(transfer, palette, data_030008B0.destination + 0x2f40, 32);
}
