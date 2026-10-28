/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080227BC.c
 * Original SHA-256: 6a23e026214aee98635ddd27aef4faed14d7cb61eb6cdb54aa2a4fede0b7728b
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef void (*BufferCopier)(void *destination, const void *source, u32 size);

typedef struct {
    const u8 *source;
    u8 *destination;
    u32 unknown_08;
    u32 size;
} CopyContext;

extern BufferCopier const data_0836D4BC[];

/* 080227BC..080227E8: 44 bytes. */
u32 func_080227BC(CopyContext *context)
{
    data_0836D4BC[0](context->destination, context->source, context->size);
    context->destination += context->size;
    context->source += context->size;
    return 0;
}
