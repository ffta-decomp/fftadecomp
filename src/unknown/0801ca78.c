typedef short s16;
/* These products fit int; only the final halfword assignment wraps. */
void ProjectMapCellCoordinates(s16 column, s16 height, s16 row,
                               s16 *projected_x, s16 *projected_height,
                               s16 *projected_y)
{
    *projected_x = column * 32 + 16;
    *projected_height = height * 16;
    *projected_y = row * 32 + 16;
}
