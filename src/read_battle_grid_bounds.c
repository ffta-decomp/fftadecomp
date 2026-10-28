typedef unsigned char u8;
typedef unsigned int u32;

struct BattleGridContext {
    u32 unknown_00;
    u8 *cells;
    u8 grid_width;
    u8 reserved_09;
    u8 minimum_x;
    u8 reserved_0b;
    u8 minimum_y;
    u8 horizontal_extent;
    u8 reserved_0e;
    u8 vertical_extent;
};

#define BATTLE_GRID ((volatile struct BattleGridContext *)0x02007f10)

/* Copy the current grid bounds into caller-provided bytes. */
void ReadBattleGridBounds(u8 *horizontal_extent, u8 *vertical_extent,
                          u8 *minimum_x, u8 *minimum_y)
{
    volatile struct BattleGridContext *grid = BATTLE_GRID;
    *horizontal_extent = grid->horizontal_extent;
    *vertical_extent = grid->vertical_extent;
    *minimum_x = grid->minimum_x;
    *minimum_y = grid->minimum_y;
}
