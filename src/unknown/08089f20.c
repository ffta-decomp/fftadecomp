/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08089F20.c
 * Original SHA-256: e75135b9fe577760b2354ac3b1f735405aaea305ecb4c8a32dcc9ec5e05c1b75
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned short u16;

void func_08089F20(u16 *destination, u16 tile, u16 stride,
                   u16 width, u16 height, u16 flags)
{
    int row;

    for (row = 0; row < height; row++) {
        int column;

        for (column = 0; column < width; column++, tile += 2) {
            u16 *bottom = destination + stride;

            destination[column] = tile | flags;
            bottom[column] = (tile + 1) | flags;
        }

        destination += stride * 2;
    }
}
