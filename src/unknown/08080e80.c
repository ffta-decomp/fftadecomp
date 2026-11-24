/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: 43f7f78cfe893ab4d99d2004e0740459589bfb5c (PR #20)
 * Original file: src/08080E80.c
 * Original SHA-256: 3d34c609b1dd31f396b32cb665b8d58a671d011a41265c67627c9aa6e492c830
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Validation: data/upstream-imports-20261030.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_000[0xC1C];
    u8 mode;
    u8 unknown_c1d[0x3F];
    u16 entries[6];
} MenuState;

extern MenuState *data_03002818;

/* 0x08080E80..0x08080EB8: 56 bytes, 21 instructions. */
void func_08080E80(u8 mode)
{
    int i;

    data_03002818->mode = mode;
    for (i = 0; i < 6; i++)
        data_03002818->entries[i] = 0;
}
