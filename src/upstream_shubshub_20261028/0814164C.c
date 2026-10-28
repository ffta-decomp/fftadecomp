/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0814164C.c
 * Original SHA-256: 235d56ddbc524d7fb60815023324ca206ccf48e4964f7a6085820b2a2a18261a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0814164C..0x0814168C: 64 bytes. */
extern u8 data_020084D8[];
extern u8 data_0200F2E0[];
extern u8 data_0200F320[];
extern void func_08145990(void *);

void func_0814164C(u16 channel)
{
    void *sound = 0;

    if (data_020084D8[0] & 2) {
        switch (channel) {
        case 1:
            sound = data_0200F2E0;
            break;
        case 2:
            sound = data_0200F320;
            break;
        }
        if (sound != 0)
            func_08145990(sound);
    }
}
