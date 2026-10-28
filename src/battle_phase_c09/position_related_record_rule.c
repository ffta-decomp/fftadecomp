/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef signed int s32;
struct BattlePositionView { u8 *unit; u32 unknown04; s16 x; u8 unknown0a[2]; s16 y; };
extern void *RetailCall_08096d7c(void);
extern struct BattlePositionView *RetailCall_08099560(void *,const u8 *);
extern u32 RetailCall_08025f70(const u8 *);
extern u32 RetailCall_0801cd08(u8,u8);
extern s32 RetailCall_08099d08(void *,struct BattlePositionView **);
extern u32 RetailCall_080cdbcc(const u8 *);
asm(".global RetailCall_08096d7c\n.thumb_set RetailCall_08096d7c,0x08096d7d\n.global RetailCall_08099560\n.thumb_set RetailCall_08099560,0x08099561\n.global RetailCall_08025f70\n.thumb_set RetailCall_08025f70,0x08025f71\n.global RetailCall_0801cd08\n.thumb_set RetailCall_0801cd08,0x0801cd09\n.global RetailCall_08099d08\n.thumb_set RetailCall_08099d08,0x08099d09\n.global RetailCall_080cdbcc\n.thumb_set RetailCall_080cdbcc,0x080cdbcd");

u32 UnitPassesPositionAndRelatedRecordRule(const u8 *unit)
{
    struct BattlePositionView *records[13];
    s32 grid_x;
    s32 grid_y;
    s32 count;
    s32 index;
    records[0]=RetailCall_08099560(RetailCall_08096d7c(),unit);
    grid_x=records[0]->x>>5;
    grid_y=records[0]->y>>5;
    if ((u8)RetailCall_08025f70(unit) || (u8)RetailCall_0801cd08((u8)grid_x,(u8)grid_y)==2)
        return 1;
    count=RetailCall_08099d08(RetailCall_08096d7c(),records);
    for(index=0;index<count;index++) {
        const u8 *other=records[index]->unit;
        const u8 *category=unit+260;
        if (*category!=other[260] && (u8)RetailCall_080cdbcc(other) && other[230]==*category)
            return 1;
    }
    return 0;
}
