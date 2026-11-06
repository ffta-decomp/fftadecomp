/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/080D7798.c
 * Original SHA-256: c924ccb52789fa6964f7606e36a4d262b2dd909d88bbe1c0e037a7b6028cc78f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef struct {
    u8 width;
    u8 height;
    u8 unknown_02[2];
    u8 mode;
    u8 flags;
    u8 data[1];
} TilePattern;

typedef struct {
    const TilePattern *pattern;
    u16 base;
    u8 mode;
} PatternDescriptor;

typedef struct {
    const TilePattern *pattern;
    u16 base;
} TileDescriptor;

typedef struct {
    u8 kind;
    u8 flags;
    u16 count;
    void *data;
    const u8 *source;
} TransferEntry;

typedef struct {
    const TransferEntry *entries;
    u8 unknown_04[3];
    u8 index;
    u8 unknown_08[8];
    u16 chunk;
    u8 unknown_12[2];
    u32 remaining;
    u8 *destination;
    const u8 *source;
    u8 unknown_20[4];
    u16 *buffer;
} Transfer;

extern u8 func_080D7674(Transfer *transfer);
extern void func_080D6A34(u16 *destination, const TilePattern *pattern,
                          u16 base, u8 mode);
extern void func_080D6D0C(u16 *destination, const TilePattern *pattern, u16 base);

/* Complete target 080D7798..080D7862: 202 bytes, 83 reached instructions. */
u8 func_080D7798(Transfer *transfer)
{
    u8 changed = 0;

    switch (transfer->entries[transfer->index].kind) {
    case 0:
        transfer->destination = transfer->entries[transfer->index].data;
        changed = 1;
        break;
    case 1:
        transfer->destination = (u8 *)transfer->buffer;
        changed = 1;
        break;
    case 2:
        return 1;
    case 3:
        if (func_080D7674(transfer)) {
            transfer->destination = (u8 *)transfer->buffer;
            changed = 1;
        }
        break;
    case 4: {
        const PatternDescriptor *descriptor = transfer->entries[transfer->index].data;
        const TilePattern *pattern = descriptor->pattern;
        func_080D6A34(transfer->buffer, pattern,
                      descriptor->base, descriptor->mode);
        transfer->destination = (u8 *)transfer->buffer;
        changed = 1;
        break;
    }
    case 5: {
        const TileDescriptor *descriptor = transfer->entries[transfer->index].data;
        const TilePattern *pattern = descriptor->pattern;
        func_080D6D0C(transfer->buffer, pattern, descriptor->base);
        transfer->destination = (u8 *)transfer->buffer;
        changed = 1;
        break;
    }
    }
    if (changed) {
        transfer->source = transfer->entries[transfer->index].source;
        transfer->remaining = transfer->entries[transfer->index].count;
    }
    return changed;
}
