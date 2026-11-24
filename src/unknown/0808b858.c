/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808B858.c
 * Original SHA-256: 25485da82210aafaf77c70ae0fc6ec5f83665b2f3b0f8c9c18335d4d53945641
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned char u8;
typedef unsigned short u16;

struct Window {
    u8 unknown_00[0x28];
    u8 width;
    u8 unknown_29[0x23];
};

extern struct Window data_030009E0[];

void func_0808B858(int index, u16 *destination, u16 tile, u16 count)
{
    int stride = data_030009E0[index].width;
    int column;

    for (column = 0; column < count; column++, destination++) {
        *destination = tile;
        destination[stride] = tile;
    }
}
