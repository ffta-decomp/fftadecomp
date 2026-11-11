typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int s32;
struct RangeContext { unsigned char pad[8]; void *list; };
union RangePacket { u32 words[2]; u16 half[4]; };
extern void ResetList(void *) __asm__("RetailCall_080c79e0");
extern s32 CountList(void *) __asm__("RetailCall_080c7b08");
extern void WalkBefore(void *, void *, void *) __asm__("RetailCall_080c7cc0");
extern void WalkRange(void *, void *, void *) __asm__("RetailCall_080c7d18");
__asm__(".global RetailCall_080c79e0\n.thumb_set RetailCall_080c79e0, 0x080c79e1\n"
        ".global RetailCall_080c7b08\n.thumb_set RetailCall_080c7b08, 0x080c7b09\n"
        ".global RetailCall_080c7cc0\n.thumb_set RetailCall_080c7cc0, 0x080c7cc1\n"
        ".global RetailCall_080c7d18\n.thumb_set RetailCall_080c7d18, 0x080c7d19\n");
s32 SelectRange(struct RangeContext *,s32,s32,s32) __asm__("CoreFrontier_000213DC");
s32 SelectRange(struct RangeContext *context,s32 width,s32 start,s32 limit)
{
    union RangePacket packet;
    ResetList(context->list);
    if (CountList(context->list)<=0) {
        if (start+width>=limit) return -1;
        return start;
    }
    WalkBefore(context->list,(void *)0x080220e9,context->list);
    {
        register u32 packed_start __asm__("r0");
        register u32 packed_limit __asm__("r1");
        register u32 old_word __asm__("r0");
        register u32 preserved_mask __asm__("r2");
        register u32 actual_width __asm__("r1");
        register u32 clear_upper_mask __asm__("r3");
        packed_start=(u32)start<<16;
        __asm__ volatile("" : "+l"(packed_start));
        preserved_mask=0xffff0000u;
        __asm__ volatile("" : "+l"(preserved_mask));
        packed_limit=(u32)limit<<16;
        __asm__ volatile("" : "+l"(packed_limit));
        clear_upper_mask=0xffffu;
        __asm__ volatile("" : "+l"(clear_upper_mask));
        packet.words[0]=(packed_start>>16)|packed_limit;
        actual_width=(u16)width;
        __asm__ volatile("ldr %0, %1\n\tand %0, %2\n\torr %0, %3\n\tand %0, %4\n\tstr %0, %1"
            : "=&l"(old_word), "+m"(packet.words[1])
            : "l"(preserved_mask), "l"(actual_width), "l"(clear_upper_mask) : "cc");
    }
    WalkRange(context->list,(void *)0x08021379,&packet);
    if ((packet.half[3]&2) || packet.half[1] < packet.half[0]+packet.half[2]) {
        ResetList(context->list);
        return -1;
    }
    ResetList(context->list);
    return packet.half[0];
}
