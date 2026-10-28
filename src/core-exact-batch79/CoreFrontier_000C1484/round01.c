typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
struct BattleRawTagView { u8 prefix[0x54e4]; u8 tags[4]; u8 count; };
typedef char TagOffset[(u32)&((struct BattleRawTagView *)0)->tags == 0x54e4 ? 1 : -1];
typedef char CountOffset[(u32)&((struct BattleRawTagView *)0)->count == 0x54e8 ? 1 : -1];
extern struct BattleRawTagView gBattleRawTagView;
__asm__(".global gBattleRawTagView\n.set gBattleRawTagView,0x020101f8");
s32 ReadBattleRawTag(s32 index)
{
    s32 tag;
    /* Retail has only a signed upper bound; preserve ARM32 address wrapping. */
    if (index < gBattleRawTagView.count)
        tag = *(u8 *)((u32)gBattleRawTagView.tags + (u32)index);
    else
        tag = -1;
    return tag;
}
