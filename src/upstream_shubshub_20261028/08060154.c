/* Imported from https://github.com/shubshub/fftadecomp
 * Upstream commit: ece7856b4816550174d46a7e6e9b246a5a70a54c
 * Original file: src/08060154.c
 * Original SHA-256: 40e92b548b37bdf08800e334b814fa21f47d4c4245c0c477f7bb0619e414bc9a
 * Authorship: upstream contributors; existing notices retained.
 * No additional license grant is inferred. Local verification recorded in data/upstream-imports.json.
 */
#include "ffta.h"

typedef struct {
    u8 type;
} MenuRecord;

typedef struct {
    u8 unknown_00[0x20];
    MenuRecord *records[1];
} MenuState;

typedef struct {
    u8 unknown_00[2];
    u8 category;
    u8 unknown_03[13];
} ItemCategory;

extern MenuState *data_0200F44C;
extern const ItemCategory g_table_08521214[];
extern u8 func_080CB99C(u16 id);

/* Complete target: [0x08060154, 0x080601A4), 80 bytes, 34 instructions. */
u32 func_08060154(u32 index, u8 offset)
{
    MenuRecord *record = data_0200F44C->records[index + offset];
    u32 categoryOffset;
    const ItemCategory *category;
    u16 id;

    if (!record)
        return 0;
    categoryOffset = record->type * sizeof(ItemCategory);
    category = (const ItemCategory *)((const u8 *)g_table_08521214 + categoryOffset);
    id = category->category ? 0x18A + category->category : 0;
    return func_080CB99C(id) + 13;
}
