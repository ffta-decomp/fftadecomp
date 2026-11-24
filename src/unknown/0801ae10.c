/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801AE10.c
 * Original SHA-256: 095f097a6e7b0beb3f7a9571aa2ecc0f1cc442da9c8ee206069ea7d926814b8c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* Target: 16 bytes. Test the cleared high bit of the state halfword at 0x2C. */
extern unsigned short g_state_02007F40[];

unsigned int func_0801AE10(void)
{
    return (g_state_02007F40[0x16] >> 15) ^ 1;
}
