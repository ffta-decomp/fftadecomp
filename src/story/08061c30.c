typedef unsigned char u8;
typedef unsigned int u32;
typedef signed int s32;
typedef struct Slot { u8 unknown[21]; u8 rank; } Slot;
extern void *RetailCall_08022840(u32);
extern void RetailCall_08022854(void *);
extern void RetailCall_080028c8(void *, void *, u32, u32, void *);
void RemainingCore48_00061C30(void)
{
    void *scratch=RetailCall_08022840(100);
    Slot **slots=RetailCall_08022840(64);
    register u32 base asm("r0")=0x02002948;
    s32 cursor;
    register s32 index asm("r1");
    asm("" : "+r"(base));
    base += 420;
    cursor=(s32)slots+60;
    do {
        *(Slot **)cursor=(Slot *)base;
        base-=28;
        cursor-=4;
    } while (cursor >= (s32)slots);
    RetailCall_080028c8(scratch,slots,16,4,(void *)0x08061c25);
    index=0;
    do {
        register Slot *slot asm("r2");
        u32 old_rank;
        asm volatile("lsl r0, %1, #2\n\tadd r0, r0, %2\n\tldr %0, [r0]"
                     : "=l"(slot) : "l"(index), "l"(slots) : "r0", "cc", "memory");
        old_rank=slot->rank;
        index++;
        if (old_rank != 0) slot->rank=index;
    } while (index<=15);
    RetailCall_08022854(slots);
    RetailCall_08022854(scratch);
}
asm(".global RetailCall_08022840\n.thumb_set RetailCall_08022840,0x08022841\n");
asm(".global RetailCall_08022854\n.thumb_set RetailCall_08022854,0x08022855\n");
asm(".global RetailCall_080028c8\n.thumb_set RetailCall_080028c8,0x080028c9\n");
