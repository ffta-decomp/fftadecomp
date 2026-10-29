#include "_captured_06c0b7aa19a41601_interfaces.h"
static inline u32 WithinManhattanRange(u8 source_x,u8 source_y,u8 target_x,u8 target_y,int range)
{
    u32 within=0;
    int delta_x=target_x-source_x;
    int delta_y;
    if (delta_x<0) delta_x=-delta_x;
    delta_y=target_y-source_y;
    if (delta_y<0) delta_y=-delta_y;
    if (delta_x+delta_y<=range) within=1;
    return within;
}
u32 IsAbilityTargetWithinGeometry(const void *unit,u8 source_x,u8 source_y,u8 target_x,u8 target_y,u16 ability,u16 constraint,u8 mode) __asm__("CoreRegion30_000A0254");
u32 IsAbilityTargetWithinGeometry(const void *unit,u8 source_x,u8 source_y,u8 target_x,u8 target_y,u16 ability,u16 constraint,u8 mode)
{
    u16 shape,height_limit,range;
    u8 cell_flags;
    if (ReadValidatedGridHeight((s8)target_x,(s8)target_y)<=0) return 0;
    if (ReadValidatedGridHeight((s8)source_x,(s8)source_y)<=0) return 0;
    if (!(u8)IsGridCellPopulated(target_x,target_y)) return 0;
    cell_flags=ReadGridFlags(target_x,target_y);
    if (cell_flags&1) return 0;
    if (cell_flags&8) return 0;
    if (ability) {
        if (GetAbilityProperty(ability,4)&128) ability=0;
    }
    if (!ability)
        return CheckWeaponTargetRange(unit,(s8)source_x,(s8)source_y,(s8)target_x,(s8)target_y,constraint,mode);
    shape=ReadAbilityTargetShape(unit,ability,constraint,1);
    height_limit=GetAbilityProperty(ability,8);
    range=GetAbilityProperty(ability,7)&0xff3f;
    {
        register int allowed_height __asm__("r4")=(s16)height_limit;
        asm("" : "+r"(allowed_height));
        if (allowed_height!=0) {
            register u32 raw_height __asm__("r0")=ReadGridHeight(source_x,source_y);
            u32 source_height;
            register int difference __asm__("r0");
            raw_height <<= 24;
            asm("" : "+r"(raw_height));
            source_height=raw_height>>24;
            difference=source_height-(u8)ReadGridHeight(target_x,target_y);
            asm("" : "+r"(difference));
            if (difference<0) difference=-difference;
            if (difference>allowed_height) return 0;
        }
    }
    switch(shape&112) {
    case 0: case 16: case 48: {
        int difference=source_x-target_x;
        u16 delta_x,delta_y;
        if (difference<0) difference=-difference;
        delta_x=difference;
        difference=source_y-target_y;
        if (difference<0) difference=-difference;
        delta_y=difference;
        if (delta_x!=0 && delta_y!=0) return 0;
        {
            int signed_range=(s16)range;
            asm("" : "+r"(signed_range));
            if (signed_range==0) return 1;
            return WithinManhattanRange(source_x,source_y,target_x,target_y,signed_range);
        }
    }
    case 32: {
        int difference=source_x-target_x;
        u16 delta_x,maximum;
        register u32 delta_y __asm__("r2");
        register u32 shifted_x __asm__("r1");
        register u32 shifted_y __asm__("r3");
        register u32 shifted_producer __asm__("r0");
        if (difference<0) difference=-difference;
        delta_x=difference;
        difference=source_y-target_y;
        if (difference<0) difference=-difference;
        shifted_producer=(u32)difference<<16;
        asm("" : "+r"(shifted_producer));
        delta_y=shifted_producer>>16;
        asm("" : "+r"(delta_y));
        shifted_producer=(u32)delta_x<<16;
        asm("" : "+r"(shifted_producer));
        shifted_y=(u32)delta_y<<16;
        shifted_x=shifted_producer;
        asm("" : "+r"(shifted_x), "+r"(shifted_y));
        if ((int)shifted_x>=(int)shifted_y) maximum=shifted_x>>16;
        else maximum=shifted_y>>16;
        shifted_producer=(u32)delta_y<<16;
        asm("" : "+r"(shifted_producer));
        if (shifted_x==shifted_producer) return 0;
        if ((s16)maximum<=(s16)range) return 1;
        return 0;
    }
    case 64:
        {
            int signed_range=(s16)range;
            asm("" : "+r"(signed_range));
            if (signed_range==0) return 1;
            return WithinManhattanRange(source_x,source_y,target_x,target_y,signed_range);
        }
    default: return 1;
    }
}
