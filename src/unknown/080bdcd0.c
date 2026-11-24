typedef unsigned char u8;
typedef unsigned int u32;
/* A set direction bit rejects this traversal; unsupported selectors allow it. */
u32 CheckBattleCellDirection(const void *grid, u8 x, u8 y, u8 direction)
{
    if (direction <= 3) {
        u32 index = x + y * 16;
        const u8 *direction_flags = (const u8 *)grid + 1024;
        int flags = direction_flags[index];
        if (((flags >> direction) & 1) == 0) return 1;
    } else return 1;
    return 0;
}
