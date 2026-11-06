/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 11946243ba373da48154ed04cb3bb31e52dad97b
 * Original file: src/081443FC.c
 * Original SHA-256: 662500f65a109f0ac08f5c25fd78350e748d597f19fb044ec1369e1cd2e591be
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred.
 */
#include "ffta.h"

typedef union {
    const u8 *bytes;
    const u32 *words;
} SourceCursor081443FC;

/* Complete 0x081443FC..0x0814445E: forward byte and aligned word copy. */
void *func_081443FC(void *destination, const void *source, u32 byte_count)
{
    u8 *destination_bytes = destination;
    SourceCursor081443FC cursor;

    cursor.bytes = source;
    if (byte_count >= 16 && (((u32)cursor.bytes | (u32)destination_bytes) & 3) == 0) {
        u32 *destination_words = (u32 *)destination_bytes;

        while (byte_count >= 16) {
            *destination_words++ = *cursor.words++;
            *destination_words++ = *cursor.words++;
            *destination_words++ = *cursor.words++;
            *destination_words++ = *cursor.words++;
            byte_count -= 16;
        }
        while (byte_count >= 4) {
            *destination_words++ = *cursor.words++;
            byte_count -= 4;
        }
        destination_bytes = (u8 *)destination_words;
    }
    while (byte_count--) {
        *destination_bytes++ = *cursor.bytes++;
    }
    return destination;
}
