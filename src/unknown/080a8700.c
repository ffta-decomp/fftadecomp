typedef unsigned char u8;
typedef signed char s8;
typedef unsigned int u32;
struct Unit {u8 unknown[246];u8 grid_x,grid_y;};
struct Context {struct Unit *unit;};
/* The unused upper half of the second word is not initialized by this caller. */
struct TargetPoint {unsigned x:16;unsigned height:16;unsigned y:16;unsigned unused:16;};
typedef char PointSize[sizeof(struct TargetPoint)==8?1:-1];
extern u32 QuerySourceHeight(struct Context*,int,int);
extern u32 QueryTargetHeight(u32,u32);
extern struct Context *SelectContext(struct Context*,const struct TargetPoint*,const struct TargetPoint*,void*);
struct Context *SelectBattleContextFromGridPoints(struct Context*,struct Context*,s8,s8,void*) __asm__("CoreRegion30_000A8700");
struct Context *SelectBattleContextFromGridPoints(struct Context *source,struct Context *target,s8 x,s8 y,void *output)
{
    struct TargetPoint start,end;
    struct Unit *unit;
    start.x=x*32+16;
    start.y=y*32+16;
    start.height=(QuerySourceHeight(source,x,y)<<4)+24;
    unit=target->unit;
    end.x=unit->grid_x*32+16;
    end.y=unit->grid_y*32+16;
    end.height=((u8)QueryTargetHeight(unit->grid_x,unit->grid_y)*16)+24;
    return SelectContext(source,&start,&end,output);
}
__asm__(".global QuerySourceHeight\n.thumb_set QuerySourceHeight,0x08099c1d\n.global QueryTargetHeight\n.thumb_set QueryTargetHeight,0x0801cc19\n.global SelectContext\n.thumb_set SelectContext,0x080a05c5");
