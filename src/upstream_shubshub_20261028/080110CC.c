/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080110CC.c
 * Original SHA-256: 7236cf91a2086625b891e68a1c2c3ff85b4a0b4ff8f4c18fa458f14b3ad57080
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080110CC..0x080110D6: 10 bytes. */
typedef struct {
    u8 unknown_00[0x30];
    s8 value;
} Record080110CC;

s8 func_080110CC(Record080110CC *record)
{
    return record->value;
}
