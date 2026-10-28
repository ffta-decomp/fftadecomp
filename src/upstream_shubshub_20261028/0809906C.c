/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0809906C.c
 * Original SHA-256: 942c86eff11dda37c9e795be8d5ad106ac54a7663886e83dd1fecfcdc27f9acb
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

/* 0x0809906C..0x0809915A: 238 bytes. */
typedef struct {
    u8 unknown_00[9];
    u8 value_09;
    u8 unknown_0A[0x16];
    u16 value_20;
    u16 value_22;
    u16 value_24;
    u16 value_26;
} ExpandedValues;

typedef struct {
    u8 unknown_00[5];
    u8 value_05;
    u8 unknown_06[4];
    u16 unknown_0A : 4;
    u16 value_20 : 11;
    u16 value_22 : 11;
    u16 value_24 : 11;
    u16 value_26 : 11;
} __attribute__((packed)) PackedValues;

void func_0809906C(ExpandedValues *expanded, PackedValues *packed)
{
    u32 value;

    value = expanded->value_09;
    expanded->value_09 = packed->value_05;
    packed->value_05 = value;

    value = expanded->value_20;
    expanded->value_20 = packed->value_20;
    packed->value_20 = value;

    value = expanded->value_24;
    expanded->value_24 = packed->value_24;
    packed->value_24 = value;

    value = expanded->value_22;
    expanded->value_22 = packed->value_22;
    packed->value_22 = value;

    value = expanded->value_26;
    expanded->value_26 = packed->value_26;
    packed->value_26 = value;
}
