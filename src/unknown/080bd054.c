extern void ReleaseGlobalPoolAllocation(void *);
__asm__(".global ReleaseGlobalPoolAllocation\n.thumb_set ReleaseGlobalPoolAllocation, 0x08022855");
void ReleasePublishedBattleIndicator(void) __asm__("CoreDependency29_000BD054");
void ReleasePublishedBattleIndicator(void)
{
    void **context_cell = (void **)0x020101f0;
    ReleaseGlobalPoolAllocation(*context_cell);
    *context_cell = (void *)0;
}
