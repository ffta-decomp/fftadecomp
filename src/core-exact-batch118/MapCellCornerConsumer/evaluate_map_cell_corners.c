typedef unsigned char u8;
typedef unsigned short u16;
typedef signed short s16;
typedef signed int s32;

typedef struct {
    s16 x;
    s16 y;
} MapCornerOffset;

#define MAP_PIXEL_CORNERS ((const MapCornerOffset *)0x08149904)
#define MAP_CLIPPING_CORNERS ((const MapCornerOffset *)0x081498f4)

extern u8 ReadMapCellPrimaryByte(u8 column, u8 row);
extern void ProjectMapCellCoordinates(s16 column, s16 primary, s16 row,
                                      s16 *projected_x, s16 *projected_height,
                                      s16 *projected_y);
extern void MapCellToScreenCoordinates(s16 projected_x, s16 projected_height,
                                       s16 projected_y, s16 *screen_x,
                                       s16 *screen_y, s16 *combined_position);
extern u8 CheckMapCornerState(s16 screen_x, s16 screen_y, s16 layer,
                              u8 primary, u8 enabled, u8 reserved);
extern u8 ReadMapCornerStateFlag(void);
extern u16 *SelectMapClippingBuffer(unsigned bank);
extern void ResolveMapCellCornerSelection(u8 column, u8 row, u8 screen_x,
                                          u8 screen_y, const u8 *available,
                                          u8 mode);

typedef struct { MapCornerOffset corners[4]; } MapCornerBlock;

void EvaluateMapCellCorners(u8 column, u8 row, u8 mode)
{
    u8 available[4];
    MapCornerBlock pixel_corners;
    s16 projected_x, projected_height, projected_y;
    s16 screen_x, screen_y, combined_position;
    u8 primary;
    u8 base_layer;
    u8 corner;

    /* Retail captures both four-corner blocks into distinct local objects. */
    pixel_corners = *(const MapCornerBlock *)MAP_PIXEL_CORNERS;
    primary = ReadMapCellPrimaryByte(column, row);
    ProjectMapCellCoordinates(column, primary, row, &projected_x,
                              &projected_height, &projected_y);
    MapCellToScreenCoordinates(projected_x, projected_height, projected_y,
                               &screen_x, &screen_y, &combined_position);
    screen_x = (s16)(screen_x - 16);
    screen_y = (s16)(screen_y - 8);
    base_layer = (u8)(column + row);

    for (corner=0; corner<4; corner++) {
        u8 observed;
        combined_position = base_layer;
        if (corner == 2) {
            if (row <= 14 &&
                primary == ReadMapCellPrimaryByte(column, (u8)(row+1)))
                ++combined_position;
        } else if (corner == 3) {
            if (column <= 14 &&
                primary == ReadMapCellPrimaryByte((u8)(column+1), row))
                ++combined_position;
        }
        available[corner] = 0;
        observed = CheckMapCornerState(
            (s16)(screen_x + pixel_corners.corners[corner].x),
            (s16)(screen_y + pixel_corners.corners[corner].y),
            combined_position, primary, 1, 0);
        if (observed == ReadMapCornerStateFlag())
            available[corner] = 1;
    }

    screen_x = (s16)(screen_x >> 3);
    screen_y = (s16)(screen_y >> 3);
    {
    MapCornerBlock clipping_corners;
    clipping_corners = *(const MapCornerBlock *)MAP_CLIPPING_CORNERS;
    for (corner=0; corner<4; corner++) {
        if (!available[corner]) {
            u16 *clipping = SelectMapClippingBuffer(0);
            /* The original advances to the row before reading the X pair. */
            clipping += (screen_y + clipping_corners.corners[corner].y) * 32;
            clipping += (screen_x + clipping_corners.corners[corner].x) >> 1;
            if (*clipping == 0)
                available[corner] = 1;
        }
    }
    }
    ResolveMapCellCornerSelection(column, row, (u8)screen_x,
                                  (u8)screen_y, available, mode);
}
