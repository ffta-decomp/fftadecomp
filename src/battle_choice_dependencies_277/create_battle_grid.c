typedef unsigned int u32;
extern void *AllocateGameBlock(u32 bytes);
extern void ResetBattleGrid(void *grid);
/* Preserve the allocation while reset executes; retail has no NULL branch. */
void *CreateBattleGrid(void)
{
    void *grid = AllocateGameBlock(0x4504);
    ResetBattleGrid(grid);
    return grid;
}
__asm__(".global AllocateGameBlock\n.thumb_set AllocateGameBlock,0x08022841\n"
        ".global ResetBattleGrid\n.thumb_set ResetBattleGrid,0x080BDBAD");
