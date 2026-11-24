/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0801E674.c
 * Original SHA-256: bd4d73072b0d5f0f86c9a45a0a40d3ba2af7927ca04b4542e82574a2db63b0cf
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* Target: 12 bytes. Read the state halfword at offset 8. */
extern unsigned short g_state_02007F40[];

unsigned int func_0801E674(void)
{
    return g_state_02007F40[4];
}
