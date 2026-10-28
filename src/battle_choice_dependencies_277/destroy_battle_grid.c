extern void ResetBattleGrid(void *grid);
extern void ReleaseGameBlock(void *allocation);
/* Retail resets the owned grid before releasing the same allocation. */
void DestroyBattleGrid(void *grid)
{
    ResetBattleGrid(grid);
    ReleaseGameBlock(grid);
}
__asm__(".global ResetBattleGrid\n.thumb_set ResetBattleGrid,0x080BDBAD\n"
        ".global ReleaseGameBlock\n.thumb_set ReleaseGameBlock,0x08022855");
