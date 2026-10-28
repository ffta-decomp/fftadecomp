/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DE488.c
 * Original SHA-256: a3c82cafd7ea7b6e240e79b4c9313c8e7e4dc800488ca88a8a48d5516db027fc
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080DE488..0x080DE49E: 22 bytes. */
extern u8 func_0809A3BC(void);

int func_080DE488(void)
{
    if (func_0809A3BC())
        return 1;
    return 0;
}
