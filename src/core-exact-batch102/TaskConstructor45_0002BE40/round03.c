typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
struct UnitStatusFlagView;
struct DmaRequest;
extern void *gUnitTaskContext;
extern int UnitField27HasBit14(const struct UnitStatusFlagView *);
extern int UnitField27HasBit6(const struct UnitStatusFlagView *);
extern struct DmaRequest *TakeUnitTaskRingRecord(void);
extern void QueueDmaCopy32(struct DmaRequest *, u32, u32, u16);
extern void QueueDmaFixedSource32(struct DmaRequest *, u16, u32, u16);
/* Keep both live status queries and each post-allocation context reload. */
void UpdateUnitTaskStatusIndicators(const struct UnitStatusFlagView *unit)
{
    register struct DmaRequest *request asm("r0");
    register u32 source asm("r1");
    if ((u8)UnitField27HasBit14(unit) != 0) {
        request = TakeUnitTaskRingRecord();
        /* This live returned request occupies R0 until its queue constructor call. */
        asm("" : "+r" (request));
        source = (u32)((u8 *)gUnitTaskContext + 3836);
        asm("" : "+r" (source));
        QueueDmaCopy32(request, source, 0x060138c0, 16);
    }
    if ((u8)UnitField27HasBit6(unit) != 0) {
        request = TakeUnitTaskRingRecord();
        /* This live returned request occupies R0 until its queue constructor call. */
        asm("" : "+r" (request));
        source = (u32)((u8 *)gUnitTaskContext + 3900);
        asm("" : "+r" (source));
        QueueDmaCopy32(request, source, 0x06013d60, 8);
    } else {
        request = TakeUnitTaskRingRecord();
        /* This live returned request occupies R0 until its queue constructor call. */
        asm("" : "+r" (request));
        QueueDmaFixedSource32(request, 0, 0x06013d60, 8);
    }
}
asm(".global gUnitTaskContext\n.set gUnitTaskContext,0x0200F440\n"
    ".global UnitField27HasBit14\n.thumb_set UnitField27HasBit14,0x080C82B9\n"
    ".global UnitField27HasBit6\n.thumb_set UnitField27HasBit6,0x080C832D\n"
    ".global TakeUnitTaskRingRecord\n.thumb_set TakeUnitTaskRingRecord,0x0802BA09\n"
    ".global QueueDmaCopy32\n.thumb_set QueueDmaCopy32,0x08000ADD\n"
    ".global QueueDmaFixedSource32\n.thumb_set QueueDmaFixedSource32,0x08000B69\n");
