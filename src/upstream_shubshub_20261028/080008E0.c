/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080008E0.c
 * Original SHA-256: 4114fd7478b06d420c0c792302f965ac732b49ce70e9d047b054bc002b521b7e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct DmaRequest080008E0 {
    const void *source;
    void *destination;
    u32 control;
    u8 state;
    u8 flags;
    u16 unknown_0E;
};

struct DmaRegisters080008E0 {
    const void *source;
    void *destination;
    u32 control;
};

extern u16 data_03000E10;
extern u16 data_03002BC0[4];
extern struct DmaRequest080008E0 data_03002BD0[4];
extern struct DmaRequest080008E0 data_03002C10[4];
extern struct DmaRegisters080008E0 *const data_0836D470[4];

/* Complete [0x080008E0, 0x080009AC): 204 bytes, 87 instructions. */
void func_080008E0(void)
{
    s32 i;

    for (i = 0; i < 4; i++) {
        if (data_03002BC0[i] != 0)
            continue;
        if (data_03000E10 == 1 && (data_03002BD0[i].flags & 0x80))
            continue;
        switch (data_03002BD0[i].state) {
        case 0:
            data_03002C10[i].state = 0;
            break;
        case 1:
            data_03002BD0[i].state = 3;
            data_03002C10[i] = data_03002BD0[i];
            break;
        case 2:
            data_03002BD0[i].state = 0;
            data_03002C10[i].state = 0;
            break;
        }
    }
    for (i = 0; i < 4; i++) {
        struct DmaRequest080008E0 *request = &data_03002C10[i];
        struct DmaRegisters080008E0 *registers;

        if (data_03002BC0[i] != 0 || request->state != 3)
            continue;
        registers = data_0836D470[i];
        registers->control = 0;
        registers->source = request->source;
        registers->destination = request->destination;
        registers->control = request->control;
    }
}
