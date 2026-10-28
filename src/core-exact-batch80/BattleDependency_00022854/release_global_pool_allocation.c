extern void ReleasePoolAllocation(void *storage, void *allocation);
__asm__(".global ReleasePoolAllocation\n.thumb_set ReleasePoolAllocation, 0x08007171");

void ReleaseGlobalPoolAllocation(void *allocation)
    __asm__("BattleDependency_00022854");
void ReleaseGlobalPoolAllocation(void *allocation)
{
    ReleasePoolAllocation(*(void **)0x0200f434, allocation);
}
