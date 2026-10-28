/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0806144C.c
 * Original SHA-256: 9beb0865dce4f8a80638ea0969cfeb80862a8ee3ee81081dfbd98a14efe9931c
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* Target: 80 bytes / 31 instructions, 0x0806144C..0x0806149C. */
typedef unsigned char u8;
typedef unsigned short u16;

typedef struct {
    u8 unknown_00[0x14];
    u16 *tilemap;
} DisplayState;

extern DisplayState data_030008B0;
extern void func_08016A98(u16 *destination, u8 width, u8 height,
                           u16 value, u16 stride);

void func_0806144C(u8 enabled)
{
    u16 *destination;

    if (enabled) {
        destination = data_030008B0.tilemap + 0x58;
        func_08016A98(destination, 3, 2, 0, 32);
    } else {
        destination = data_030008B0.tilemap + 0x153;
        func_08016A98(destination, 5, 2, 0, 32);
    }
}
