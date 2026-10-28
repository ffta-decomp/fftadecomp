typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct UnitPositionView { u8 unknown00[246]; s8 x; s8 y; s8 z; };
extern u32 RetailCall_0812f0d8(const struct UnitPositionView *,u16 *);
extern u32 RetailCall_0812c7f4(const struct UnitPositionView *,const struct UnitPositionView *,u32,s32,s32,s32,s32,s32,u32,u32);
extern u32 RetailCall_080cda64(const struct UnitPositionView *);
asm(".global RetailCall_0812f0d8\n.thumb_set RetailCall_0812f0d8,0x0812f0d9\n.global RetailCall_0812c7f4\n.thumb_set RetailCall_0812c7f4,0x0812c7f5\n.global RetailCall_080cda64\n.thumb_set RetailCall_080cda64,0x080cda65");

u32 CoreContinuation_0012C8DC(const struct UnitPositionView *source,const struct UnitPositionView *target,u8 choice)
{
    u16 item_ids[2];
    u32 value;
    u32 selected_item;
    register u32 choice_flag __asm__("r2");
    u32 enabled;
    RetailCall_0812f0d8(source,item_ids);
    selected_item=item_ids[0];
    /* Consume the initialized equipment snapshot before forming the choice flag. */
    asm("" : "+r"(selected_item));
    choice_flag=0;
    if (choice==1) choice_flag=1;
    /* The initialized choice flag is consumed as outgoing stack argument eight. */
    asm("" : "+r"(choice_flag));
    enabled=1;
    value=RetailCall_0812c7f4(source,target,selected_item,source->x,source->y,target->x,target->y,target->z,choice_flag,enabled);
    if (value != 0 && (u8)RetailCall_080cda64(target))
        value=100;
    return value;
}
