/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/0801D980.c
 * Original SHA-256: 97966ec7b71957902a8c624f796a28ddc995cfc8be3ecb163ce0145ff6566a83
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "abi/interfaces/080008e0_bindings.h"

typedef struct ParameterState0801D980 {
    u16 unknown_00;
    u16 selector;
    u16 first;
    u8 enabled;
    u8 unknown_07;
    const u16 *source;
    u16 second;
    u16 third;
    const u16 *payload;
    const u16 *derived;
} ParameterState0801D980;

typedef struct ParameterHeader0801D980 {
    u16 first;
    u16 start;
    u16 count;
    u16 values[1];
} ParameterHeader0801D980;

extern ParameterState0801D980 data_02007F20;
extern const u16 data_08425104[];
extern u16 data_02008390[];
extern void func_0814186C(const void *source, void *destination, u32 control);

/* Complete target 0801D980..0801DA10, 144 bytes. */
u16 func_0801D980(u16 index, u8 mode)
{
    ParameterState0801D980 *state = &data_02007F20;
    const u16 *offsets;
    const ParameterHeader0801D980 *header;
    const u16 *payload;

    if (state->selector == 0xFF)
        return 0;

    offsets = data_08425104;
    header = (const ParameterHeader0801D980 *)((const u8 *)offsets + offsets[index]);
    payload = header->values;
    if (mode != 0) {
        state->enabled = 1;
        state->source = payload;
    } else {
        u16 *buffer = data_02008390;
        u16 first;

        func_0814186C(payload, buffer, 0xA1);
        first = *buffer;
        buffer += 160;
        *buffer = first;
    }
    state->first = header->first;
    state->second = header->count;
    state->third = header->count + header->start - 1;
    state->payload = payload;
    state->derived = payload + state->first - 160;
    state->selector = index;
    return payload[0];
}
