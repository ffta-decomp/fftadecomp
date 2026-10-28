typedef unsigned char u8;
typedef unsigned int u32;
extern void *gBattleQueryContext;
extern u32 QueryContextSelector(void *context, u32 selector);
u8 QueryBattleContextByte(u8 selector)
{
    return (u8)QueryContextSelector(gBattleQueryContext, selector);
}
asm(".global gBattleQueryContext\n.set gBattleQueryContext,0x020101F0\n.global QueryContextSelector\n.thumb_set QueryContextSelector,0x080bced1\n");
