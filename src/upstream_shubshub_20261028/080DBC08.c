/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/080DBC08.c
 * Original SHA-256: 9c8fff2c5b9d27574a1360118f510317bec8967c69e49e95934a7aaedfdff12f
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x080DBC08..0x080DBC16: 14 bytes, 6 instructions. */
typedef struct ObjectStatus ObjectStatus;

extern u8 func_08099C10(const ObjectStatus *object);

u8 func_080DBC08(const ObjectStatus *object)
{
    return func_08099C10(object);
}
