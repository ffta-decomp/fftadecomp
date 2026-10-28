typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct SelectionItemRows { u8 unknown_00[148]; u32 *rows; };
extern u32 ReadManagedItemCategoryNibble(u16);
u32 GetManagedItemRowPalette(struct SelectionItemRows *state, u32 row)
{
    return (u8)ReadManagedItemCategoryNibble(*(u16 *)&state->rows[row]) + 13;
}
asm(".thumb_set ReadManagedItemCategoryNibble, 0x080cb99d\n");
