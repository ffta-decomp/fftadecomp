typedef unsigned char u8;
typedef signed short s16;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 ReadMapCellKind(u32,u32);
extern void ReadMapCellPosition(u32,u32,u32,s16*,s16*,s16*);
extern void ProjectBattlePoint(s16,s16,s16,u16*,u16*,u16*);
extern u32 ConfigurePositionTransition(int,int,u32,u32,u32);
__asm__(".global ReadMapCellKind\n.thumb_set ReadMapCellKind,0x0801cc19\n.global ReadMapCellPosition\n.thumb_set ReadMapCellPosition,0x0801ca79\n.global ProjectBattlePoint\n.thumb_set ProjectBattlePoint,0x0801c919\n.global ConfigurePositionTransition\n.thumb_set ConfigurePositionTransition,0x0801bb95");
u32 QueryTilePositionBoundary(u32 x_word,u32 y_word) __asm__("RemainingBand43_000D8510");
u32 QueryTilePositionBoundary(u32 x_word,u32 y_word)
{
    s16 current_x,current_height,current_y;
    u16 projected_x,projected_y,projected_depth;
    u32 x=(u8)x_word,y=(u8)y_word;
    u32 kind,low_result;
    int adjusted_y;
    kind=(u8)ReadMapCellKind(x,y);
    ReadMapCellPosition(x,kind,y,&current_x,&current_height,&current_y);
    ProjectBattlePoint(current_x,current_height,current_y,
                       &projected_x,&projected_y,&projected_depth);
    projected_x-=120;
    adjusted_y=projected_y-96;
    projected_y=adjusted_y;
    low_result=(u16)ConfigurePositionTransition((s16)projected_x,
                                                (s16)adjusted_y,4,16,4);
    return (0u-low_result)>>31;
}
