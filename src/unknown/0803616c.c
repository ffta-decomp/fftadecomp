typedef unsigned char u8;
typedef unsigned int u32;
typedef signed short s16;
struct MenuTarget {u8 x,y;u8 opaque[18];};
extern u8 *gTargetContext;
extern u8 gTargetFeatures;
__asm__(".global gTargetContext\n.set gTargetContext,0x03002810\n.global gTargetFeatures\n.set gTargetFeatures,0x02002e58");
unsigned SnapMenuTarget(s16 *,s16 *) asm("CoreRegion_0003616C");
unsigned SnapMenuTarget(s16 *x,s16 *y)
{
    int i;
    register u8 **root_cell __asm__("r10");
    register u8 *features __asm__("r9");
    unsigned ordinal;
    i=0;
    root_cell=&gTargetContext;
    __asm__("" : "+r"(root_cell));
    features=&gTargetFeatures;
    __asm__("" : "+r"(features));
    ordinal=1;
    for(;i<30;++ordinal,++i) {
        register u8 **working_root __asm__("r1")=root_cell;
        struct MenuTarget *target;
        int tx;
        int ty;
        /* Retained cell and actual low read base are separate values. */
        __asm__("" : "+r"(working_root));
        target=(struct MenuTarget *)((u32)i*sizeof(struct MenuTarget)
               +(u32)*(struct MenuTarget **)((*working_root)+0x67c));
        /* Both real address values survive through the indexed consumer. */
        __asm__("" : : "r"(working_root), "r"(target));
        tx=target->x*8;
        if(*x<tx-4 || *x>tx+20) continue;
        ty=target->y*8;
        if(*y<ty-8 || *y>ty+16) continue;
        if(!(*features&1) && i==8) return 0;
        {
            register u8 *working_features __asm__("r2")=features;
            __asm__("" : "+r"(working_features));
            if(!(*working_features&2) && i==27) return 0;
        }
        if(*x==tx+8 && *y==ty+8) {
            register u8 **counter_cell __asm__("r1")=root_cell;
            u8 *counter;
            __asm__("" : "+r"(counter_cell));
            counter=(*counter_cell)+0xf3c;
            if(*counter<=29) ++*counter;
        } else {
            register u8 **dwell_cell __asm__("r1")=root_cell;
            __asm__("" : "+r"(dwell_cell));
            if(*((*dwell_cell)+0xf3c)==0) {
                if(*x<tx+8) ++*x;else if(*x>tx+8) --*x;
                if(*y<ty+8) ++*y;else if(*y>ty+8) --*y;
            }
        }
        return ordinal;
    }
    return 0;
}
