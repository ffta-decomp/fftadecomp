/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080356A0.c
 * Original SHA-256: a065e3e5bc5027357ac10c28d972de4a4acc31f365542e7b16b42db0c66813aa
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Record080356A0 {
    u8 unknown_00[0x98];
    u8 first[0x10];
    u8 current;
    u8 unknown_a9[3];
    u8 second[0x10];
    u8 option;
    u8 unknown_bd[0xf];
};

struct State080356A0 {
    u8 unknown_000[0x954];
    struct Record080356A0 records[1];
};

struct Options080356A0 {
    u8 unknown_00[0x10];
    u8 option;
    u8 unknown_11[0xbb];
};

extern struct State080356A0 *g_state_03002810;
extern void func_08017D18(u8 *, u32);
extern void func_08017E28(u8 *);

/* Target: [0x080356A0, 0x08035720), 128 bytes, 54 instructions. */
u8 func_080356A0(s32 index, u8 requested)
{
    u8 previous = g_state_03002810->records[index].current;
    s32 mode = requested;

    func_08017D18(g_state_03002810->records[index].first, mode);
    switch (mode) {
    case 0:
    case 1:
        func_08017D18(g_state_03002810->records[index].second, 0);
        break;
    case 3:
    {
        u32 option;
        u32 address;
        struct Options080356A0 *options;
        func_08017E28(g_state_03002810->records[index].second);
        address = index * sizeof(struct Record080356A0) + (u32)g_state_03002810;
        options = (struct Options080356A0 *)(address + 0xa00);
        option = options->option;
        func_08017D18(g_state_03002810->records[index].second,
                     option);
        break;
    }
    }
    return previous;
}
