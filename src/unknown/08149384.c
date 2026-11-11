/* Observed ROM 0x00149384, Thumb 0x08149385, span 38 bytes. */
typedef unsigned char u8;
typedef unsigned int u32;

/* Grid cells are seven bytes in 16-column row-major order. */
u32 GetBattleCoordinateOccupant(void *grid, u32 x, u32 y)
{
    u8 *cell = (u8 *)grid;

    /* Match the retail x/y truncation order; compiler scheduling otherwise
     * changes five instruction bytes despite identical cell selection. */
    __asm__ __volatile__("lsl %0, %0, #24\n\t"
                         "lsl %1, %1, #24\n\t"
                         "lsr %1, %1, #20\n\t"
                         "lsr %0, %0, #24"
                         : "+r"(x), "+r"(y));
    cell += (y + x) * 7;
    if ((cell[2] & 128) != 0)
        return 1;
    return 0;
}
