typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SelectionCategoryRows { u8 unknown_00[148]; u32 *rows; };
extern u32 ReadManagedItemCategoryNibble(u32);
u32 GetManagedCategoryRowPalette(struct SelectionCategoryRows *state, u32 row)
{
    u16 row_id;
    u32 category;
    row_id = *(u16 *)&state->rows[row];
    category = 394;
    if (row_id <= 85)
        --category;
    return (u8)ReadManagedItemCategoryNibble(category) + 13;
}
asm(".thumb_set ReadManagedItemCategoryNibble, 0x080cb99d\n");
