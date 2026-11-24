/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801D880.c
 * Original SHA-256: a16a871d943f52f4eb57fe4a6bb604f6f6276e6b8a7af7aefbe58ae534f1d398
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* 0801D880..0801D890: read the state byte at offset 0x228. */
typedef unsigned char u8;

typedef struct {
    u8 unknown_000[0x228];
    u8 value;
} State0801D880;

extern State0801D880 g_state_02007F40;

u8 func_0801D880(void)
{
    return g_state_02007F40.value;
}
