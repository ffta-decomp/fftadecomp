typedef unsigned int u32;
typedef void (*ClearRoutine)(void *, u32);
extern void InvokeClearRoutine(void *destination, u32 bytes, ClearRoutine routine);
/* Reset the game-owned grid and record pool through the existing IWRAM clear. */
void ResetBattleGrid(void *grid)
{
    register ClearRoutine volatile *callback_cell __asm__("r2") = (ClearRoutine volatile *)0x0836D4B8;
    /* Materialize the actual callback-cell address before the count argument. */
    __asm__("" : "+r"(callback_cell));
    InvokeClearRoutine(grid, 0x4504, *callback_cell);
}
__asm__(".global InvokeClearRoutine\n.thumb_set InvokeClearRoutine,0x0814224D");
