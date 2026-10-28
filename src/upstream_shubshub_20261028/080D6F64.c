/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080D6F64.c
 * Original SHA-256: 9f70304bf84120884cbe1a6bb6897dee14eb34860ce4e87a6299d270a0322362
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;

/* 0x080D6F64: 86 bytes. Expand four packed two-bit values into nibbles. */
void func_080D6F64(const u8 *source, u16 count, u8 *destination)
{
    u8 value;
    u16 i;
    u16 j;

    for (i = 0; i < count; i++) {
        value = source[i];
        *destination = 0;
        for (j = 0; j < 4; j++) {
            u8 bits = value & 3;

            if (j & 1) {
                bits <<= 4;
                *destination |= bits;
                destination++;
                *destination = 0;
            } else {
                *destination |= bits;
            }
            value >>= 2;
        }
    }
}
