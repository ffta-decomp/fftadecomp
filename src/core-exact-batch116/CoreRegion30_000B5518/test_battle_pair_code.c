typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct BattlePairRecord { u32 actor; u32 unknown4; u16 x; u16 unknown10; u16 y; };
extern u32 QueryBattlePairCode(u32,u32,u32,s32,s32,s32,s32);
__asm__(".global QueryBattlePairCode\n.thumb_set QueryBattlePairCode,0x0812eacd");
u32 TestBattlePairCode(struct BattlePairRecord *first,struct BattlePairRecord *second,u16 code) __asm__("CoreRegion30_000B5518");
u32 TestBattlePairCode(struct BattlePairRecord *first,struct BattlePairRecord *second,u16 code)
{
    if (code == 233) {
        u32 result = 0;
        s32 index;
        for (index=0;index<=7;index++) {
            if ((u16)QueryBattlePairCode(first->actor,second->actor,(u16)(index+68),
                (s8)(first->x>>5),(s8)(first->y>>5),
                (s8)(second->x>>5),(s8)(second->y>>5))) result |= 1;
        }
        {
            register u32 captured __asm__("r1") = result;
            /* Native R1 captures the full accumulator before LOW8 return. */
            __asm__("" : "+r"(captured));
            return (u8)captured;
        }
    }
    if (code == 329) code=313;
    return (u16)QueryBattlePairCode(first->actor,second->actor,code,
        (s8)(first->x>>5),(s8)(first->y>>5),
        (s8)(second->x>>5),(s8)(second->y>>5)) != 0;
}
