/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DBC2C.c
 * Original SHA-256: fd44b46c78736e402837e1bf99a17c05dfcc5373a85c1d3cd2027642e82acc90
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

extern u8 func_08099C10(const void *object);
extern u32 func_08099C14(void *object, u32 value);

/* 080DBC2C..080DBC58: 44 bytes. */
u8 func_080DBC2C(void *object, u8 change)
{
    u8 current = func_08099C10(object);
    u16 value = (s8)change + current;

    return func_08099C14(object, value);
}
