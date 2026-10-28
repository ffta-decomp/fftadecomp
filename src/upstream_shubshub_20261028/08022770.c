/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08022770.c
 * Original SHA-256: d7ca8e37afcd6a589a909e04642c8b6241eec539a35c9d597a4fcecfead3cba3
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef void (*BufferInitializer)(void *destination, u32 size);

typedef struct {
    u32 unknown_00;
    u8 *cursor;
    u32 unknown_08;
    u32 size;
} BufferContext;

extern BufferInitializer const g_callbacks_0836D4B8[];

/* 08022770..08022794: 36 bytes. */
u32 func_08022770(BufferContext *context)
{
    g_callbacks_0836D4B8[0](context->cursor, context->size);
    context->cursor += context->size;
    return 0;
}
