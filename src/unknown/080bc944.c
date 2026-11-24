extern void ReleaseGlobalPoolAllocation(void *allocation);
__asm__(".global ReleaseGlobalPoolAllocation\n.thumb_set ReleaseGlobalPoolAllocation,0x08022855");

void ReleaseBattlePhaseAllocation(void *allocation)
{
    ReleaseGlobalPoolAllocation(allocation);
}
