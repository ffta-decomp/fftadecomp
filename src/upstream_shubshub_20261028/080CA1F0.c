/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080CA1F0.c
 * Original SHA-256: 614d799da12e6afd13411a62ce5fdfc9546733ea68f2ae85bbacad014999c3cd
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned int u32;

extern const u32 g_table_085680DC[];
extern const u32 g_table_085516D0[];

struct PackedKey {
    u32 value;
} __attribute__((packed));

/* Target: 080CA1F0..080CA22C, 60 bytes. */
u32 func_080CA1F0(const struct PackedKey *key)
{
    u32 index = key->value;

    if (index > 0x7FFF)
        return g_table_085516D0[index & 0x7FFF];
    return g_table_085680DC[index];
}
