/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08087078.c
 * Original SHA-256: ed111dd2f5bf9211bfcc676cf4d947759d827aad426f8fda17889d51ac2fa5fe
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_00[0x2A];
    u16 counts[5];
} CountRecord;

typedef struct {
    u8 unknown_000[0x1D0C];
    CountRecord *record;
} CountState;

extern CountState *data_03002818;

/* 0x08087078..0x080870A8: 48 bytes, 19 instructions. */
int func_08087078(void)
{
    int sum = 0;
    const u16 *counts = data_03002818->record->counts;
    int i;

    for (i = 0; i < 5; i++)
        sum += counts[i];
    return sum;
}
