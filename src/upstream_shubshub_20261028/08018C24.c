/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08018C24.c
 * Original SHA-256: 49a916cc17ec7dd54d4bcc11ece307d7cf88ed22ab65bd89d8f1e392397dbf79
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 08018C24..08018C92: 110 bytes, 55 instructions. */
u16 func_08018C24(u8 *destination, const u8 *source)
{
    u8 *output = destination;

    if (source == 0 || destination == 0)
        return 0;

    if (*source == 1) {
        source++;
        while (*source) {
            *output = 0x80;
            output++;
            *output = *source - 1;
            source++;
            output++;
        }
    } else if (*source) {
        u32 prefix_mask = 0x80;

        do {
            u32 value = *source;

            if (prefix_mask & value) {
                *output = value;
                source++;
                output++;
                *output = *source;
            } else {
                *output = value;
            }
            source++;
            output++;
        } while (*source);
    }
    *output = 0;
    return output - destination;
}
