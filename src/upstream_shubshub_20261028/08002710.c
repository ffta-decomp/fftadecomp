/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08002710.c
 * Original SHA-256: 36caa01fb7433ace997b4f50a64263b35e29652794f419fd552499c113aa3ca7
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u32 data_03000930[2];
extern u32 data_030009C4;
extern void func_08002768(void);
extern void func_08003410(void);

/* Target: [0x08002710, 0x08002768), 88 bytes, 25 instructions. */
void func_08002710(void)
{
    if (data_03000930[0] == 0xa51d && data_03000930[1] == 0xc269)
        data_030009C4 = 1;
    else
        data_030009C4 = 0;

    func_08002768();
    func_08003410();

    data_03000930[0] = 0xa51d;
    data_03000930[1] = 0xc269;
}
