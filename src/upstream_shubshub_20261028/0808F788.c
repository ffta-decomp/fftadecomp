/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0808F788.c
 * Original SHA-256: 12da3ecc947507355b773fd892567f226e7968d1f3dff049177e08e3acf728da
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u32 data_03005F2C;
extern u8 data_03005F28;

/* 0x0808F788..0x0808F79C: 20 bytes, 6 instructions. */
void func_0808F788(void)
{
    data_03005F2C = 0;
    data_03005F28 = 0;
}
