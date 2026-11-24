/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/081477DC.c
 * Original SHA-256: 16308746a642c4f755e4ce9aa47dca00dce4fead3efa590ad8829293c92d5a5f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
/* Convert a packed RGB555 color to weighted grayscale. Target: 82 bytes. */
typedef unsigned short u16;

u16 func_081477DC(u16 color)
{
    u16 red = color & 0x1f;
    u16 green = (color & 0x3e0) >> 5;
    u16 blue = (color & 0x7c00) >> 10;
    u16 gray;
    int weighted_blue;

    red *= 30;
    green *= 59;
    weighted_blue = blue * 11;
    gray = (red + green + weighted_blue) / 100;
    return gray | (gray << 5) | (gray << 10);
}
