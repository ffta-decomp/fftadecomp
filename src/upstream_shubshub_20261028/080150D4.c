/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080150D4.c
 * Original SHA-256: b890d0e69bba53d0aacfc872887018bbc7ef195fc98d2a45e789a1764912799e
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 080150D4..0801510E: 58 bytes. */
u8 func_080150D4(const u8 *text)
{
    if (text[0] == '@') {
        switch (text[1]) {
        case '!':
        case '%':
        case 'g':
        case 'l':
        case 'r':
        case 't':
            return text[2];
        }
    }
    return 0xFF;
}
