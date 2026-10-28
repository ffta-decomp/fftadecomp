/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080110D8.c
 * Original SHA-256: 49d84d4f41926840de1e2657cc3fed935d3d93716180794e95f4fbe99afcfef9
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080110D8..0x080110F8: 32 bytes. */
typedef struct {
    u8 unknown_00[0x14];
    u16 flags;
    u8 unknown_16[7];
    u8 mode;
} Record080110D8;

u8 func_080110D8(const Record080110D8 *record)
{
    if (record->mode == 0)
        return 1;
    if (record->mode == 1)
        return 1;
    if ((record->flags & 0x80) == 0)
        return 0;
    return 1;
}
