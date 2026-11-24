typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
struct BattleRecordView { u8 *unit; };
extern struct BattleRecordView **RetailCall_08022840(u32);
extern void RetailCall_08022854(void *);
extern void RetailCall_0814224c(void *,u32,u32);
extern s32 RetailCall_08099d34(void *,struct BattleRecordView **);
extern u32 RetailCall_080c82b8(const u8 *);
asm(".global RetailCall_08022840\n.thumb_set RetailCall_08022840,0x08022841\n.global RetailCall_08022854\n.thumb_set RetailCall_08022854,0x08022855\n.global RetailCall_0814224c\n.thumb_set RetailCall_0814224c,0x0814224d\n.global RetailCall_08099d34\n.thumb_set RetailCall_08099d34,0x08099d35\n.global RetailCall_080c82b8\n.thumb_set RetailCall_080c82b8,0x080c82b9");

struct BattleRecordView *SelectFirstStatus14Actor(void *context)
    __asm__("CoreClosure31_0009966C");

struct BattleRecordView *SelectFirstStatus14Actor(void *context)
{
    register struct BattleRecordView **records asm("r5")=RetailCall_08022840(52);
    s32 count;
    struct BattleRecordView *selected;
    s32 index;
    struct BattleRecordView **cursor;
    /* Keep the actual allocated array root across collection/selection/free. */
    asm("" : "+r"(records));
    RetailCall_0814224c(records,52,*(const u32 *)0x0836d4b8);
    count=RetailCall_08099d34(context,records);
    selected=records[0];
    index=0;
    cursor=records;
    while(index<count) {
        if ((u8)RetailCall_080c82b8((*cursor)->unit)) {
            selected=*cursor;
            break;
        }
        cursor++;
        index++;
    }
    RetailCall_08022854(records);
    return selected;
}
