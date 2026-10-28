/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct TaskStateView { u32 unknown00; u8 mode; };
extern u32 GetGameFlag(u16);
asm(".global GetGameFlag\n.thumb_set GetGameFlag,0x080c9541");

u32 IsBattleMode4WithOnlyFlag3(void)
{
    struct TaskStateView **root=(struct TaskStateView **)0x0200f438;
    if ((*root)->mode==4 && (u8)GetGameFlag(3) && !(u8)GetGameFlag(4))
        return 1;
    return 0;
}
