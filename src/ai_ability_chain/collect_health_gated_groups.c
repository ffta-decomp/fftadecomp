/* Method-local interface declarations from the frozen build. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern u32 RetailCall_080c7ea4(const u8 *,u32);
extern u32 RetailCall_08142ab0(u32,u32);
extern u32 RetailCall_08133f70(u32,const u8 *,u32);
asm(".global RetailCall_080c7ea4\n.thumb_set RetailCall_080c7ea4,0x080c7ea5\n.global RetailCall_08142ab0\n.thumb_set RetailCall_08142ab0,0x08142ab1\n.global RetailCall_08133f70\n.thumb_set RetailCall_08133f70,0x08133f71");

u32 CollectHealthGatedAbilityGroups(u32 output_address,const u8 *unit)
{
    u16 count=0;
    u32 current=RetailCall_080c7ea4(unit,19);
    u32 maximum=RetailCall_080c7ea4(unit,20);
    if (RetailCall_08142ab0(100*current,maximum)<=25)
        count=RetailCall_08133f70(output_address,unit,3);
    count+=RetailCall_08133f70(count*2+output_address,unit,2);
    count+=RetailCall_08133f70(count*2+output_address,unit,1);
    return count;
}
