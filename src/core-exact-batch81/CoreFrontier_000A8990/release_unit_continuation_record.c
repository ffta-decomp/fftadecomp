extern void ReleaseGlobalPoolAllocation(void *allocation);
__asm__(".global ReleaseGlobalPoolAllocation\n.thumb_set ReleaseGlobalPoolAllocation, 0x08022855");

void ReleaseUnitContinuationRecord(void *record)
    __asm__("CoreFrontier_000A8990");
void ReleaseUnitContinuationRecord(void *record)
{
    ReleaseGlobalPoolAllocation(record);
}
