typedef unsigned char u8;
typedef unsigned int u32;
struct BattleGridContext {
    u8 unknown_00_to_03[4];
    const volatile u8 *cell_bytes;
    u8 width;
};
#define BATTLE_GRID_CONTEXT \
    (*(volatile const struct BattleGridContext *)0x02007f10)

u8 ReadBattleGridCellHighByte(u32 x, u32 y)
{
    u32 shifted_cell_x = x << 24;
    u8 cell_y = (u8)y;
    register u32 row_byte_offset asm("r2") = BATTLE_GRID_CONTEXT.width;
    register const volatile u8 *row_bytes asm("r1");

    /* The loaded width is the actual destructive multiply carrier. */
    asm("" : "+r" (row_byte_offset));
    row_byte_offset *= cell_y;
    row_byte_offset <<= 1;
    asm("" : "+r" (row_byte_offset));
    /* y is consumed before R1 becomes the base plus row address. */
    row_bytes = BATTLE_GRID_CONTEXT.cell_bytes;
    row_bytes += row_byte_offset;
    asm("" : "+r" (row_bytes));
    row_bytes += shifted_cell_x >> 23;
    /* Consume the actual final cell address in R1 before the byte load. */
    asm("" : "+r" (row_bytes));
    return row_bytes[1];
}
