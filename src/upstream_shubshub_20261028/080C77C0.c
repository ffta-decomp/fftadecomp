/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080C77C0.c
 * Original SHA-256: 7255664a19cbd7422581bee74d3780d6a21fb690b6bbec51f776165d101054ec
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u16 data_02015970;
extern void func_08029544(u32 operation);
extern u16 func_08011860(void);
extern void func_0802966C(void);

u8 func_080C77C0(void)
{
    switch (data_02015970) {
    case 0:
        func_08029544(11);
        data_02015970 = 1;
        break;
    case 1:
        if (func_08011860()) {
            func_0802966C();
            data_02015970 = 2;
        }
        break;
    case 2:
        return 0;
    }
    return 1;
}
