typedef unsigned char u8;
typedef signed char s8;
extern unsigned int IsBattleCellPresent(u8 x, u8 y);
extern unsigned int ReadMapCellPrimaryByte(u8 x, u8 y);
asm(".global IsBattleCellPresent\n.thumb_set IsBattleCellPresent,0x0801cc7d\n.global ReadMapCellPrimaryByte\n.thumb_set ReadMapCellPrimaryByte,0x0801cc19");
int ReadAdmissibleBattleCell(int x, int y) asm("CoreRegion30_0009D79C");
int ReadAdmissibleBattleCell(int x, int y)
{
    y = (s8)y;
    if ((s8)x < 0 || (s8)y < 0 || (s8)x > 15 || (s8)y > 15 ||
        (u8)IsBattleCellPresent((u8)x, (u8)y) == 0)
        return -1;
    return (u8)ReadMapCellPrimaryByte((u8)x, (u8)y);
}
