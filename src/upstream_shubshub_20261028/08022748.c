/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08022748.c
 * Original SHA-256: f98745c7f4b1b5ed101f445164e7cc33cf5b1671237b02ab3301d9b5d089ab18
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u8 *current;
    u32 unknown_08;
    u32 length;
    u8 *begin;
} Transfer08022748;

extern void (*data_0836D4BC)(u8 *destination, u32 offset, u32 length);

/* 0x08022748: 40 bytes; transfer the current span and advance the cursor. */
u32 func_08022748(Transfer08022748 *transfer)
{
    data_0836D4BC(transfer->current, transfer->current - transfer->begin,
                  transfer->length);
    transfer->current += transfer->length;
    return 0;
}
