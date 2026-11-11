/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08089600.c
 * Original SHA-256: e46a4611d7da05fba1bd99565744151484f3869433c7f544fceb5954514fc394
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
typedef unsigned short u16;

void func_08089600(u16 *destination, u16 tile, u16 count, u16 flags)
{
    int column;

    for (column = 0; column < count; column++, destination++, tile += 2) {
        *destination = tile | flags;
        destination[count] = (tile + 1) | flags;
    }
}
