/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/0804EFD0.c
 * Original SHA-256: 92ccb2926077f040554074eb8118f003d8cc17ab3985c851d421c9802868e509
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

union LookupEntry0804EFD0 {
    u32 index;
    const u8 *value;
};

struct LookupData0804EFD0 {
    u8 unknown_000[0x424];
    union LookupEntry0804EFD0 entries[64];
    u32 secondary_indices[1];
};

struct Lookup0804EFD0 {
    struct LookupData0804EFD0 *data;
    u8 unknown_04[4];
    u8 type;
};

extern const u16 data_0852A13E[];
extern const u16 data_0852A212[];
extern u32 func_080CB53C(u32 value);

/* Complete [0x0804EFD0, 0x0804F05E): 142 bytes, 58 instructions. */
u16 func_0804EFD0(struct Lookup0804EFD0 *lookup, u16 index)
{
    u16 result = 0;

    switch (lookup->type) {
    case 1:
        result = data_0852A13E[lookup->data->secondary_indices[(s16)index]] + 1;
        break;
    case 4:
        result = func_080CB53C(lookup->data->entries[(s16)index].value[0]) + 1;
        break;
    case 5:
        return data_0852A212[lookup->data->entries[(s16)index].index] + 1;
    }
    return result;
}
