/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D758C.c
 * Original SHA-256: 7910aaa53c3f21f32917594f25b486cad90bac1be50d1cd4bc76b7ace6ce6f0d
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

struct Entry080D758C {
    u8 kind;
    u8 unknown_01;
    u16 size;
    const void *data;
    u32 unknown_08;
};

struct Payload080D758C {
    u8 format;
    u8 flags;
    u16 unknown_02;
};

struct State080D758C {
    const struct Entry080D758C *entries;
    u8 unknown_04[3];
    u8 index;
    u8 unknown_08[8];
    u16 scale;
    u16 unknown_12;
    u32 size;
    const void *data;
    void *destination;
    void *buffer;
    void *output;
};

extern void func_08141890(const void *source, void *destination);

/* Complete [0x080D758C, 0x080D7674): 232 bytes, 113 instructions. */
u8 func_080D758C(struct State080D758C *state)
{
    u8 index = state->index;
    const struct Entry080D758C *entries = state->entries;
    u32 offset = index * sizeof(struct Entry080D758C);
    const struct Entry080D758C *entry =
        (const struct Entry080D758C *)(offset + (u32)entries);

    switch (entry->kind) {
    case 1:
        func_08141890(entry->data, state->output);
        break;
    case 3: {
        u8 needs_buffer = 1;
        const struct Payload080D758C *payload =
            *(const struct Payload080D758C *const *)entry->data;

        state->size = entry->size;
        state->scale = 0x400;
        state->destination = state->output;
        if (payload->flags & 1) {
            if (payload->format == 1) {
                state->size >>= 3;
                state->scale = 0x80;
            } else if (payload->format == 2) {
                state->size >>= 2;
                state->scale >>= 2;
            } else if (payload->format == 3) {
                state->size = (state->size >> 2) + (state->size >> 3);
                state->scale = (state->scale >> 2) + 0x80;
            } else if (payload->format == 4) {
                state->size >>= 1;
                state->scale >>= 1;
            } else if (payload->format == 8) {
                needs_buffer = 0;
            }
        } else {
            if (payload->format == 1) {
                state->size >>= 2;
                state->scale >>= 2;
            } else if (payload->format == 2) {
                state->size >>= 1;
                state->scale >>= 1;
            } else if (payload->format == 3) {
                state->size = (state->size >> 1) + (state->size >> 2);
                state->scale = (state->scale >> 1) + (state->scale >> 2);
            } else if (payload->format == 4) {
                needs_buffer = 0;
            }
        }
        if (payload->flags & 2) {
            if (needs_buffer) {
                func_08141890(payload + 1, state->buffer);
                state->data = state->buffer;
            } else {
                func_08141890(payload + 1, state->output);
            }
        } else {
            state->data = payload + 1;
            return 0;
        }
        break;
    }
    default:
        return 0;
    }
    return 1;
}
