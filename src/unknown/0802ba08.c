typedef unsigned char u8;
typedef unsigned int u32;
struct UnitTaskRingView { u8 unknown0[912]; u8 next_slot; };
struct UnitTaskRecord { u8 bytes[28]; };
extern struct UnitTaskRingView *gUnitTaskContext;
__asm__(".global gUnitTaskContext\n.set gUnitTaskContext,0x0200f440");
/* Return the old byte index before masking the newly stored live cursor. */
struct UnitTaskRecord *TakeUnitTaskRingRecord(void)
{
    u8 previous;
    struct UnitTaskRecord *record;
    previous = gUnitTaskContext->next_slot++;
    record = (struct UnitTaskRecord *)((u8 *)gUnitTaskContext + 16 + 28 * previous);
    gUnitTaskContext->next_slot &= 31;
    return record;
}
