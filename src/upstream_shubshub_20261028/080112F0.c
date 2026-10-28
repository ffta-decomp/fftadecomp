/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080112F0.c
 * Original SHA-256: 2e11844a07874609858854cebcc57044d3696c9991ccc2eacc775b0624f1d5de
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* 0x080112F0 - 76 bytes: update two high attribute flags. */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x14];
    u16 attributes;
} Attributes080112F0;

void func_080112F0(void *record, u8 first, u8 second)
{
    Attributes080112F0 *object = record;

    if (first)
        object->attributes |= 0x2000;
    else
        object->attributes &= 0xDFFF;

    if (second)
        object->attributes |= 0x4000;
    else
        object->attributes &= 0xBFFF;
}
