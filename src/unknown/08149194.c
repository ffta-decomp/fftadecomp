typedef unsigned char u8;
typedef unsigned int u32;

/* Set or clear observed attribute bit 6 in a seven-byte, 16-column grid cell. */
void SetBattleGridCellFlag(u8 *grid, u32 x, u32 y, int enabled)
{
    u8 *cell;

    /* Preserve the retail truncation order for the two ABI-width arguments. */
    __asm__ __volatile__("lsl %0, %0, #24\n\t"
                         "lsl %1, %1, #24\n\t"
                         "lsr %1, %1, #20\n\t"
                         "lsr %0, %0, #24"
                         : "+r"(x), "+r"(y));
    cell = grid + (y + x) * 7;
    if (enabled) {
        cell[1] |= 0x40;
    } else {
        /* The pinned compiler otherwise assigns the old byte to r0 and
         * reverses the retail mask calculation's register allocation. */
        register u8 attributes __asm__("r1") = cell[1];
        u32 clear_mask = 0x41;
        clear_mask = -clear_mask;
        cell[1] = attributes & clear_mask;
    }
}
