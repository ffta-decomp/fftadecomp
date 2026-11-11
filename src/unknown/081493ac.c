/* Observed ROM 0x001493ac, Thumb 0x081493ad, span 20 bytes. */
typedef unsigned char u8;
typedef unsigned int u32;

/* Tactical grid cells are seven bytes in 16-column row-major order. */
u8 GetBattleCoordinateValue(void *grid, u32 x, u32 y)
{
    u8 *cell = (u8 *)grid;

    /* The ABI passes both coordinates in full registers. Preserve the retail
     * order of their 8-bit truncation; agbcc otherwise schedules x twice
     * before touching y and changes five instruction bytes. */
    __asm__ __volatile__("lsl %0, %0, #24\n\t"
                         "lsl %1, %1, #24\n\t"
                         "lsr %1, %1, #20\n\t"
                         "lsr %0, %0, #24"
                         : "+r"(x), "+r"(y));
    cell += (y + x) * 7;
    return cell[4];
}
