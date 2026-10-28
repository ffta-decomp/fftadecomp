/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 CoreRule_0812C8DC(const u8 *,const u8 *,u8,u32);
extern u32 CoreRule_0812DBA8(const u8 *,const u8 *,u16,u32);
extern u32 UnitCheck_080CDA64(const u8 *);
asm(".global CoreRule_0812C8DC\n.thumb_set CoreRule_0812C8DC,0x0812c8dd\n.global CoreRule_0812DBA8\n.thumb_set CoreRule_0812DBA8,0x0812dba9\n.global UnitCheck_080CDA64\n.thumb_set UnitCheck_080CDA64,0x080cda65");

u32 CalculateTargetRuleValue(const u8 *source, const u8 *target, u16 item_id, u8 choice, u32 argument)
{
    u32 value;
    if (!item_id)
        value = CoreRule_0812C8DC(source,target,choice,0);
    else
        value = CoreRule_0812DBA8(source,target,item_id,argument);
    if (value != 0 && (u8)UnitCheck_080CDA64(target))
        value = 100;
    return value;
}
