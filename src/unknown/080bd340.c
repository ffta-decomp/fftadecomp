extern void ReleaseGlobalPoolAllocation(void *allocation);
asm(".global ReleaseGlobalPoolAllocation\n.thumb_set ReleaseGlobalPoolAllocation,0x08022855");

void ReleaseBattleChoiceRecord(void *allocation)
{
    ReleaseGlobalPoolAllocation(allocation);
}
