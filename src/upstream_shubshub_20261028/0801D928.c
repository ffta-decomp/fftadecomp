/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801D928.c
 * Original SHA-256: d85c2e02bf3b535ce26d54a4e3235167e3f8db1c9ed33cc490d9c9d4fe4a0be0
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* Target: 16 bytes. Read bit 1 of the state halfword at 0x2C. */
extern unsigned short g_state_02007F40[];

unsigned int func_0801D928(void)
{
    return (g_state_02007F40[0x16] >> 1) & 1;
}
