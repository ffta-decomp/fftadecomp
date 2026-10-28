/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081464C4.c
 * Original SHA-256: 1cdc41501f314c18c012acefa3a442fcc6ed356811ead698ddfd0cde1232499a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x40];
    const u8 *cursor;
} CommandContext;

typedef void (*CommandHandler)(void *owner, CommandContext *context);

extern CommandHandler const data_0836D340[];

/* 081464C4..081464E4: 32 bytes. */
void func_081464C4(void *owner, CommandContext *context)
{
    u8 command = *context->cursor++;

    data_0836D340[command](owner, context);
}
