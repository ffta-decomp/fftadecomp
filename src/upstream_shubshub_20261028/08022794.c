/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08022794.c
 * Original SHA-256: 72da9fe51ddb40a5d2d18c825d3cd32c404adfb0157ba73c9f068f3c2f566c10
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef void (*BufferFiller)(void *destination, u32 value, u8 count);

typedef struct {
    u32 unknown_00;
    u8 *cursor;
    u32 unknown_08;
    u32 size;
} BufferContext;

extern BufferFiller const data_0836D4C0[];

/* 08022794..080227BC: 40 bytes. */
u32 func_08022794(BufferContext *context)
{
    data_0836D4C0[0](context->cursor, 0xFF, context->size);
    context->cursor += context->size;
    return 0;
}
